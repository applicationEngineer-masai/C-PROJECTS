#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <immintrin.h>
#include <errno.h>

bool process_image_fast_from_file(const char *source, const char *dest) {
    // Opening File
    FILE *fp = fopen(source, "rb");
    if(fp == NULL) {
        printf("Error says %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Read pgm image header with format ppm P5
    char format[3];
    int width, height, max_val;

    fscanf(fp, "%s", format);
    fscanf(fp, "%d %d", &width, &height);
    fscanf(fp, "%d", &max_val);
    fgetc(fp);

    if(strcmp(format, "P5") != 0) {
        printf("Unsupported format: %s\n", format);  // Fixed error message
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // calculate total pixel
    int total_pixel = width * height;
    printf("--> %d\n", total_pixel);

    // Now allocated input memory buffer to store total pixels
    unsigned char *input_image = malloc(total_pixel);

    // if memory allocation failed then throw error
    if(input_image == NULL) {
        printf("error says %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // read binary data from file into memory
    fread(input_image, 1, total_pixel, fp);
    fclose(fp);

    // Allocate 32-byte aligned buffers for AVX operations
    unsigned char *aligned_input = aligned_alloc(32, total_pixel);
    unsigned char *aligned_output = aligned_alloc(32, total_pixel);

    if (!aligned_input || !aligned_output) {
        perror("Failed to allocate aligned memory");
        free(input_image);
        if (aligned_input) free(aligned_input);
        if (aligned_output) free(aligned_output);
        exit(EXIT_FAILURE);
    }

    // copy input to aligned buffer
    memcpy(aligned_input, input_image, total_pixel);

    // Process image with SIMD (Single input multiple data)
    printf("Processing %dx%d image...\n", width, height);

    for(int i = 0; i < total_pixel; i += 32) {
        if(i + 32 <= total_pixel) {
            // SIMD function calls with proper underscores
            __m256i pixels = _mm256_load_si256((__m256i*)(aligned_input + i));
            __m256i result = _mm256_adds_epu8(pixels, _mm256_set1_epi8(50));
            _mm256_store_si256((__m256i*)(aligned_output + i), result);  // store to output, not input
        } else {
            // handle remaining pixels
            for (int j = i; j < total_pixel; j++) {
                aligned_output[j] = (aligned_input[j] + 50 > 255) ? 255 : aligned_input[j] + 50;
            }
        }
    }

    // Write output file
    FILE *output_file = fopen(dest, "wb");
    if (!output_file) {
        perror("Cannot create output file");
        free(input_image);
        free(aligned_input);
        free(aligned_output);
        return false;  // FIXED: return false instead of 0
    }

    // Write header
    fprintf(output_file, "P5\n%d %d\n%d\n", width, height, max_val);

    // Write processed image data
    fwrite(aligned_output, 1, total_pixel, output_file);
    fclose(output_file);

    // Cleanup
    free(input_image);
    free(aligned_input);
    free(aligned_output);

    printf("Image processed and saved to: %s\n", dest);
    return true;
}

int main(int argc, char *argv[]) {
    if(argc == 3) {
        if(process_image_fast_from_file(argv[1], argv[2])) {
            printf("Image Processing complete\n");
        } else {
            printf("Image Processing Failed\n");  // FIXED: removed perror for string
            return 1;
        }
    } else {
        printf("Unexpected Arguments, Use: %s input_image.pgm output_image.pgm\n", argv[0]);
        return -1;
    }
    
    return 0;  // Added missing return
}