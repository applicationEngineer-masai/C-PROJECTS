// Simple Audio Processor with SIMD - Works with WAV files
// This version doesn't require MP3 libraries for testing
// Compile with: gcc -msse -O2 -lm -o audioProc slowReverb.c


#define M_PI 3.14159265358979323846   // Define M_PI if not available

#include <stdio.h>      // For file operations and printf functions
#include <stdlib.h>     // For memory allocation (malloc, free) and exit functions
#include <string.h>     // For string operations like memset and strcmp
#include <math.h>       // For mathematical functions like sinf and M_PI
#include <immintrin.h>  // For SIMD instructions (SSE/AVX) - makes audio processing faster
#include <stdbool.h>    // For boolean data type (true/false)
#include <errno.h>      // For error handling and strerror function

// Structure to hold audio data in memory with aligned memory for SIMD operations
typedef struct {
    float *left_channel;    // Pointer to left audio samples (aligned memory for SIMD)
    float *right_channel;   // Pointer to right audio samples (for stereo audio)
    int sample_rate;        // How many samples per second (44100Hz is CD quality)
    int buffer_size;        // Total number of samples in the audio
    int channels;           // 1 for mono, 2 for stereo audio
} AudioBuffer;

// Structure for reverb effect parameters - creates echo/hall effect
typedef struct {
    float *delay_buffer_left;   // Memory to store delayed audio samples (left channel)
    float *delay_buffer_right;  // Memory to store delayed audio samples (right channel)
    int delay_samples;          // How many samples to delay (creates the reverb timing)
    float feedback;             // How much of the delayed signal to feed back (0.0-0.9)
    float wet_mix;             // How much reverb effect to mix in (0.0-1.0)
    float dry_mix;             // How much original signal to keep (0.0-1.0)
    int delay_index;           // Current position in the delay buffer (circular buffer)
} ReverbEffect;

// Forward function declarations
void free_audio_buffer(AudioBuffer *buffer);
void free_reverb_effect(ReverbEffect *reverb);
AudioBuffer* generate_test_audio(int sample_rate, float duration_seconds, float frequency);

// Function to create an audio buffer with aligned memory for SIMD operations
AudioBuffer* create_audio_buffer(int sample_rate, int buffer_size, int channels) {
    // Allocate memory for the AudioBuffer structure itself
    AudioBuffer *buf = malloc(sizeof(AudioBuffer));
    if (!buf) {
        printf("Failed to allocate AudioBuffer structure\n");
        return NULL;
    }
    
    // Allocate 16-byte aligned memory for left channel
    // Why 16-byte alignment? SSE instructions process 4 floats (4*4=16 bytes) at once
    buf->left_channel = aligned_alloc(16, buffer_size * sizeof(float));
    
    // For stereo audio, allocate right channel too
    if (channels == 2) {
        buf->right_channel = aligned_alloc(16, buffer_size * sizeof(float));
    } else {
        buf->right_channel = NULL; // Mono audio doesn't need right channel
    }
    
    // Check if memory allocation was successful
    if (!buf->left_channel || (channels == 2 && !buf->right_channel)) {
        printf("Failed to allocate aligned audio buffers: %s\n", strerror(errno));
        free(buf);
        return NULL;
    }
    
    // Store audio parameters in the structure
    buf->sample_rate = sample_rate;
    buf->buffer_size = buffer_size;
    buf->channels = channels;
    
    // Initialize audio buffers with silence (all zeros)
    memset(buf->left_channel, 0, buffer_size * sizeof(float));
    if (buf->right_channel) {
        memset(buf->right_channel, 0, buffer_size * sizeof(float));
    }
    
    printf("✓ Audio buffer created: %d samples, %dHz, %s\n", 
           buffer_size, sample_rate, channels == 2 ? "stereo" : "mono");
    
    return buf;
}

// Function to create reverb effect with delay buffers
ReverbEffect* create_reverb_effect(int sample_rate, float reverb_time_seconds) {
    ReverbEffect *reverb = malloc(sizeof(ReverbEffect));
    if (!reverb) {
        printf("Failed to allocate ReverbEffect\n");
        return NULL;
    }
    
    // Calculate delay buffer size
    reverb->delay_samples = (int)(reverb_time_seconds * sample_rate);
    
    // Allocate aligned memory for delay buffers
    reverb->delay_buffer_left = aligned_alloc(16, reverb->delay_samples * sizeof(float));
    reverb->delay_buffer_right = aligned_alloc(16, reverb->delay_samples * sizeof(float));
    
    if (!reverb->delay_buffer_left || !reverb->delay_buffer_right) {
        printf("Failed to allocate reverb delay buffers\n");
        free(reverb);
        return NULL;
    }
    
    // Initialize delay buffers with silence
    memset(reverb->delay_buffer_left, 0, reverb->delay_samples * sizeof(float));
    memset(reverb->delay_buffer_right, 0, reverb->delay_samples * sizeof(float));
    
    // Set reverb parameters
    reverb->feedback = 0.6f;
    reverb->wet_mix = 0.4f;
    reverb->dry_mix = 0.8f;
    reverb->delay_index = 0;
    
    printf("✓ Reverb effect created: %.2fs delay, %.1f%% wet mix\n", 
           reverb_time_seconds, reverb->wet_mix * 100);
    
    return reverb;
}

// Apply slowdown effect using SIMD
void apply_slowdown_simd(AudioBuffer *input, AudioBuffer *output, float speed_factor) {
    printf("Applying %.2fx slowdown with SIMD acceleration...\n", 1.0f / speed_factor);
    
    int simd_limit = (output->buffer_size / 4) * 4;
    
    for (int i = 0; i < simd_limit; i += 4) {
        float src_pos[4];
        for (int j = 0; j < 4; j++) {
            src_pos[j] = (float)(i + j) * speed_factor;
        }
        
        __m128 output_samples = _mm_setzero_ps();
        
        for (int j = 0; j < 4; j++) {
            int src_idx = (int)src_pos[j];
            float fraction = src_pos[j] - src_idx;
            
            if (src_idx < input->buffer_size - 1) {
                float sample1 = input->left_channel[src_idx];
                float sample2 = input->left_channel[src_idx + 1];
                float interpolated = sample1 + fraction * (sample2 - sample1);
                ((float*)&output_samples)[j] = interpolated;
            }
        }
        
        _mm_store_ps(&output->left_channel[i], output_samples);
        
        // Process right channel if stereo
        if (input->channels == 2 && output->channels == 2) {
            __m128 output_samples_r = _mm_setzero_ps();
            for (int j = 0; j < 4; j++) {
                int src_idx = (int)src_pos[j];
                float fraction = src_pos[j] - src_idx;
                
                if (src_idx < input->buffer_size - 1) {
                    float sample1 = input->right_channel[src_idx];
                    float sample2 = input->right_channel[src_idx + 1];
                    float interpolated = sample1 + fraction * (sample2 - sample1);
                    ((float*)&output_samples_r)[j] = interpolated;
                }
            }
            _mm_store_ps(&output->right_channel[i], output_samples_r);
        }
    }
    
    // Handle remaining samples
    for (int i = simd_limit; i < output->buffer_size; i++) {
        float src_pos = (float)i * speed_factor;
        int src_idx = (int)src_pos;
        float fraction = src_pos - src_idx;
        
        if (src_idx < input->buffer_size - 1) {
            float sample1 = input->left_channel[src_idx];
            float sample2 = input->left_channel[src_idx + 1];
            output->left_channel[i] = sample1 + fraction * (sample2 - sample1);
            
            if (input->channels == 2 && output->channels == 2) {
                float sample1_r = input->right_channel[src_idx];
                float sample2_r = input->right_channel[src_idx + 1];
                output->right_channel[i] = sample1_r + fraction * (sample2_r - sample1_r);
            }
        }
    }
}

// Apply reverb effect using SIMD
void apply_reverb_simd(AudioBuffer *buffer, ReverbEffect *reverb) {
    printf("Applying reverb effect with SIMD acceleration...\n");
    
    int simd_limit = (buffer->buffer_size / 4) * 4;
    
    for (int i = 0; i < simd_limit; i += 4) {
        __m128 input_left = _mm_load_ps(&buffer->left_channel[i]);
        
        int delay_pos = reverb->delay_index;
        __m128 delayed_left = _mm_setzero_ps();
        
        for (int j = 0; j < 4; j++) {
            int pos = (delay_pos + j) % reverb->delay_samples;
            ((float*)&delayed_left)[j] = reverb->delay_buffer_left[pos];
        }
        
        __m128 wet_mix = _mm_set1_ps(reverb->wet_mix);
        __m128 dry_mix = _mm_set1_ps(reverb->dry_mix);
        __m128 feedback = _mm_set1_ps(reverb->feedback);
        
        __m128 wet_signal = _mm_mul_ps(delayed_left, wet_mix);
        __m128 dry_signal = _mm_mul_ps(input_left, dry_mix);
        __m128 output_left = _mm_add_ps(dry_signal, wet_signal);
        
        __m128 feedback_signal = _mm_mul_ps(output_left, feedback);
        __m128 delay_input = _mm_add_ps(input_left, feedback_signal);
        
        _mm_store_ps(&buffer->left_channel[i], output_left);
        
        for (int j = 0; j < 4; j++) {
            int pos = (delay_pos + j) % reverb->delay_samples;
            reverb->delay_buffer_left[pos] = ((float*)&delay_input)[j];
        }
        
        // Process right channel if stereo
        if (buffer->channels == 2) {
            __m128 input_right = _mm_load_ps(&buffer->right_channel[i]);
            
            __m128 delayed_right = _mm_setzero_ps();
            for (int j = 0; j < 4; j++) {
                int pos = (delay_pos + j) % reverb->delay_samples;
                ((float*)&delayed_right)[j] = reverb->delay_buffer_right[pos];
            }
            
            __m128 wet_signal_r = _mm_mul_ps(delayed_right, wet_mix);
            __m128 dry_signal_r = _mm_mul_ps(input_right, dry_mix);
            __m128 output_right = _mm_add_ps(dry_signal_r, wet_signal_r);
            
            __m128 feedback_signal_r = _mm_mul_ps(output_right, feedback);
            __m128 delay_input_r = _mm_add_ps(input_right, feedback_signal_r);
            
            _mm_store_ps(&buffer->right_channel[i], output_right);
            
            for (int j = 0; j < 4; j++) {
                int pos = (delay_pos + j) % reverb->delay_samples;
                reverb->delay_buffer_right[pos] = ((float*)&delay_input_r)[j];
            }
        }
        
        reverb->delay_index = (reverb->delay_index + 4) % reverb->delay_samples;
    }
    
    // Handle remaining samples
    for (int i = simd_limit; i < buffer->buffer_size; i++) {
        float input_sample = buffer->left_channel[i];
        float delayed_sample = reverb->delay_buffer_left[reverb->delay_index];
        
        float output_sample = reverb->dry_mix * input_sample + 
                             reverb->wet_mix * delayed_sample;
        
        buffer->left_channel[i] = output_sample;
        
        reverb->delay_buffer_left[reverb->delay_index] = 
            input_sample + reverb->feedback * output_sample;
        
        if (buffer->channels == 2) {
            float input_sample_r = buffer->right_channel[i];
            float delayed_sample_r = reverb->delay_buffer_right[reverb->delay_index];
            
            float output_sample_r = reverb->dry_mix * input_sample_r + 
                                   reverb->wet_mix * delayed_sample_r;
            
            buffer->right_channel[i] = output_sample_r;
            
            reverb->delay_buffer_right[reverb->delay_index] = 
                input_sample_r + reverb->feedback * output_sample_r;
        }
        
        reverb->delay_index = (reverb->delay_index + 1) % reverb->delay_samples;
    }
}

// Load WAV file (simpler than MP3)
AudioBuffer* load_wav_file(const char *filename) {
    printf("Loading WAV file: %s\n", filename);
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file: %s\n", strerror(errno));
        return NULL;
    }
    
    // Get file size first
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    printf("File size: %ld bytes\n", file_size);
    
    if (file_size < 44) {
        printf("ERROR: File too small to be a valid WAV file (minimum 44 bytes)\n");
        fclose(file);
        return NULL;
    }
    
    // Read WAV header (44 bytes)
    char header[44];
    if (fread(header, 1, 44, file) != 44) {
        printf("Invalid WAV file header\n");
        fclose(file);
        return NULL;
    }
    
    // Validate WAV format
    if (strncmp(header, "RIFF", 4) != 0) {
        printf("ERROR: Not a RIFF file\n");
        fclose(file);
        return NULL;
    }
    
    if (strncmp(header + 8, "WAVE", 4) != 0) {
        printf("ERROR: Not a WAVE file\n");
        fclose(file);
        return NULL;
    }
    
    // Extract audio format information
    int chunk_size = *(int*)(header + 4);
    int sample_rate = *(int*)(header + 24);
    int channels = *(short*)(header + 22);
    int bits_per_sample = *(short*)(header + 34);
    int data_size = *(int*)(header + 40);
    
    printf("Chunk size: %d, Data size: %d\n", chunk_size, data_size);
    
    if (bits_per_sample != 16) {
        printf("Only 16-bit WAV files are supported (got %d-bit)\n", bits_per_sample);
        fclose(file);
        return NULL;
    }
    
    if (channels < 1 || channels > 2) {
        printf("Only mono or stereo files supported (got %d channels)\n", channels);
        fclose(file);
        return NULL;
    }
    
    if (data_size <= 0 || data_size > file_size) {
        printf("ERROR: Invalid data size %d (file size: %ld)\n", data_size, file_size);
        fclose(file);
        return NULL;
    }
    
    int num_samples = data_size / (channels * 2);
    float duration = (float)num_samples / sample_rate;
    
    printf("WAV info: %dHz, %d channels, %d samples (%.3f seconds)\n", 
           sample_rate, channels, num_samples, duration);
    
    if (num_samples < 100) {
        printf("WARNING: Very short audio file (%d samples, %.3f seconds)\n", 
               num_samples, duration);
        printf("This might be a corrupted or empty file.\n");
    }
    
    AudioBuffer *buffer = create_audio_buffer(sample_rate, num_samples, channels);
    if (!buffer) {
        fclose(file);
        return NULL;
    }
    
    // Read and convert samples
    short *temp_buffer = malloc(num_samples * channels * sizeof(short));
    if (!temp_buffer) {
        printf("Memory allocation failed\n");
        fclose(file);
        free_audio_buffer(buffer);
        return NULL;
    }
    
    // Read audio data with error checking
    size_t samples_read = fread(temp_buffer, sizeof(short), num_samples * channels, file);
    fclose(file);
    
    // Check if we read the expected amount
    if (samples_read != (size_t)(num_samples * channels)) {
        printf("Warning: Expected %d samples, read %zu samples\n", 
               num_samples * channels, samples_read);
        // Adjust num_samples to actual data read
        num_samples = samples_read / channels;
        buffer->buffer_size = num_samples;
    }
    
    // Convert to float and separate channels
    int non_zero_samples = 0;
    float max_amplitude = 0.0f;
    
    for (int i = 0; i < num_samples; i++) {
        if (channels == 1) {
            // Mono: duplicate to stereo
            float sample = (float)temp_buffer[i] / 32768.0f;
            buffer->left_channel[i] = sample;
            buffer->right_channel[i] = sample;
            
            float amp = fabs(sample);
            if (amp > 0.001f) non_zero_samples++;
            if (amp > max_amplitude) max_amplitude = amp;
        } else {
            // Stereo: separate channels
            float left = (float)temp_buffer[i * 2] / 32768.0f;
            float right = (float)temp_buffer[i * 2 + 1] / 32768.0f;
            
            buffer->left_channel[i] = left;
            buffer->right_channel[i] = right;
            
            float amp = fabs(left) + fabs(right);
            if (amp > 0.001f) non_zero_samples++;
            if (fabs(left) > max_amplitude) max_amplitude = fabs(left);
            if (fabs(right) > max_amplitude) max_amplitude = fabs(right);
        }
    }
    
    printf("Audio stats: %d non-zero samples (%.1f%%), max amplitude: %.3f\n",
           non_zero_samples, 
           (float)non_zero_samples * 100.0f / num_samples,
           max_amplitude);
    
    if (non_zero_samples == 0) {
        printf("ERROR: Audio file appears to be completely silent!\n");
        free(temp_buffer);
        free_audio_buffer(buffer);
        return NULL;
    }
    
    free(temp_buffer);
    return buffer;
}

// Save as WAV file
bool save_wav_file(const char *filename, AudioBuffer *buffer) {
    printf("Saving WAV file: %s\n", filename);
    printf("Buffer info: %d samples, %d channels, %dHz\n", 
           buffer->buffer_size, buffer->channels, buffer->sample_rate);
    
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Cannot create output file: %s\n", strerror(errno));
        return false;
    }
    
    // Calculate WAV parameters
    int data_size = buffer->buffer_size * buffer->channels * 2;
    int file_size = data_size + 36;
    
    printf("WAV file will be %d bytes (%d data + 44 header)\n", 
           file_size + 8, data_size);
    
    // Write WAV header
    fwrite("RIFF", 1, 4, file);
    fwrite(&file_size, 4, 1, file);
    fwrite("WAVE", 1, 4, file);
    fwrite("fmt ", 1, 4, file);
    int fmt_size = 16;
    fwrite(&fmt_size, 4, 1, file);
    short audio_format = 1;
    fwrite(&audio_format, 2, 1, file);
    fwrite(&buffer->channels, 2, 1, file);
    fwrite(&buffer->sample_rate, 4, 1, file);
    int byte_rate = buffer->sample_rate * buffer->channels * 2;
    fwrite(&byte_rate, 4, 1, file);
    short block_align = buffer->channels * 2;
    fwrite(&block_align, 2, 1, file);
    short bits_per_sample = 16;
    fwrite(&bits_per_sample, 2, 1, file);
    fwrite("data", 1, 4, file);
    fwrite(&data_size, 4, 1, file);
    
    // Check for silent audio (debugging)
    int non_zero_samples = 0;
    float max_amplitude = 0.0f;
    
    // Write audio data and collect stats
    for (int i = 0; i < buffer->buffer_size; i++) {
        // Check amplitude
        float left_amp = fabs(buffer->left_channel[i]);
        if (left_amp > max_amplitude) max_amplitude = left_amp;
        if (left_amp > 0.001f) non_zero_samples++;
        
        short left_sample = (short)(buffer->left_channel[i] * 32767.0f);
        fwrite(&left_sample, sizeof(short), 1, file);
        
        if (buffer->channels == 2) {
            float right_amp = fabs(buffer->right_channel[i]);
            if (right_amp > max_amplitude) max_amplitude = right_amp;
            
            short right_sample = (short)(buffer->right_channel[i] * 32767.0f);
            fwrite(&right_sample, sizeof(short), 1, file);
        }
    }
    
    fclose(file);
    
    // Report audio statistics
    printf("✓ WAV file saved successfully\n");
    printf("Audio stats: %d non-zero samples (%.1f%%), max amplitude: %.3f\n",
           non_zero_samples, 
           (float)non_zero_samples * 100.0f / buffer->buffer_size,
           max_amplitude);
    
    if (max_amplitude < 0.001f) {
        printf("⚠️  WARNING: Audio appears to be silent or very quiet!\n");
    }
    
    return true;
}

// Generate test audio
AudioBuffer* generate_test_audio(int sample_rate, float duration_seconds, float frequency) {
    int num_samples = (int)(duration_seconds * sample_rate);
    AudioBuffer *buffer = create_audio_buffer(sample_rate, num_samples, 2);
    
    if (!buffer) return NULL;
    
    printf("Generating test audio: %.1fHz sine wave, %.1fs duration\n", 
           frequency, duration_seconds);
    
    for (int i = 0; i < num_samples; i++) {
        float t = (float)i / sample_rate;
        float sample = 0.3f * sinf(2.0f * M_PI * frequency * t);
        
        buffer->left_channel[i] = sample;
        buffer->right_channel[i] = sample;
    }
    
    return buffer;
}

// Cleanup functions
void free_audio_buffer(AudioBuffer *buffer) {
    if (buffer) {
        free(buffer->left_channel);
        free(buffer->right_channel);
        free(buffer);
    }
}

void free_reverb_effect(ReverbEffect *reverb) {
    if (reverb) {
        free(reverb->delay_buffer_left);
        free(reverb->delay_buffer_right);
        free(reverb);
    }
}

// Main function
int main(int argc, const char *argv[]) {
    printf("🎵 Audio Slow Reverb Maker with SIMD Acceleration 🎵\n");
    printf("====================================================\n\n");
    
    AudioBuffer *input_audio = NULL;
    AudioBuffer *slowed_audio = NULL;
    ReverbEffect *reverb = NULL;
    float speed_factor = 0.75f; // Default 75% speed
    float reverb_size = 0.3f;   // Default 0.3s reverb
    
    if (argc == 5) {
        // Load from WAV file
        input_audio = load_wav_file(argv[1]);
        if (!input_audio) {
            return 1;
        }
        
        speed_factor = atof(argv[3]);
        reverb_size = atof(argv[4]);
        
        if (speed_factor <= 0.0f || speed_factor > 2.0f) {
            printf("Speed factor must be between 0.1 and 2.0\n");
            free_audio_buffer(input_audio);
            return 1;
        }
    } else if (argc == 2 && strcmp(argv[1], "--test") == 0) {
        // Generate test audio
        input_audio = generate_test_audio(44100, 5.0f, 440.0f);
        if (!input_audio) {
            return 1;
        }
    } else {
        printf("Usage:\n");
        printf("  %s input.wav output.wav speed_factor reverb_time\n", argv[0]);
        printf("  %s --test (generates test audio)\n", argv[0]);
        printf("\nExample:\n");
        printf("  %s song.wav slow_song.wav 0.75 0.3\n", argv[0]);
        printf("  %s --test\n", argv[0]);
        return 1;
    }
    
    // Calculate output size
    int output_size = (int)(input_audio->buffer_size / speed_factor);
    
    // Create output buffer
    slowed_audio = create_audio_buffer(input_audio->sample_rate, output_size, input_audio->channels);
    if (!slowed_audio) {
        free_audio_buffer(input_audio);
        return 1;
    }
    
    // Apply slowdown
    printf("\n--- Applying Slowdown Effect ---\n");
    apply_slowdown_simd(input_audio, slowed_audio, speed_factor);
    
    // Create and apply reverb
    printf("\n--- Creating Reverb Effect ---\n");
    reverb = create_reverb_effect(slowed_audio->sample_rate, reverb_size);
    if (!reverb) {
        free_audio_buffer(input_audio);
        free_audio_buffer(slowed_audio);
        return 1;
    }
    
    printf("\n--- Applying Reverb Effect ---\n");
    apply_reverb_simd(slowed_audio, reverb);
    
    // Save output
    printf("\n--- Saving Processed Audio ---\n");
    const char *output_filename = (argc >= 3) ? argv[2] : "output.wav";
    
    if (!save_wav_file(output_filename, slowed_audio)) {
        printf("Failed to save output file\n");
        free_audio_buffer(input_audio);
        free_audio_buffer(slowed_audio);
        free_reverb_effect(reverb);
        return 1;
    }
    
    // Show results
    printf("\n--- Processing Complete ---\n");
    printf("✓ Input:  %.2f seconds, %dHz, %s\n", 
           (float)input_audio->buffer_size / input_audio->sample_rate,
           input_audio->sample_rate,
           input_audio->channels == 2 ? "stereo" : "mono");
    printf("✓ Output: %.2f seconds, %.1f%% speed, reverb applied\n",
           (float)slowed_audio->buffer_size / slowed_audio->sample_rate,
           speed_factor * 100);
    printf("✓ SIMD acceleration used for optimal performance\n");
    
    // Cleanup
    free_audio_buffer(input_audio);
    free_audio_buffer(slowed_audio);
    free_reverb_effect(reverb);
    
    return 0;
}