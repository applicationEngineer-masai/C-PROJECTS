#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

// FAT32 Boot Sector Structure (512 bytes)
typedef struct {
    uint8_t  jmp_boot[3];           // 0-2: Jump instruction to boot code
    uint8_t  oem_name[8];           // 3-10: OEM name string
    uint16_t bytes_per_sector;      // 11-12: Bytes per sector (usually 512)
    uint8_t  sectors_per_cluster;   // 13: Sectors per cluster (power of 2)
    uint16_t reserved_sectors;      // 14-15: Reserved sectors (usually 32)
    uint8_t  num_fats;              // 16: Number of FATs (usually 2)
    uint16_t root_entries;          // 17-18: Root entries (0 for FAT32)
    uint16_t total_sectors_16;      // 19-20: Total sectors if < 65536 (0 for FAT32)
    uint8_t  media_type;            // 21: Media type (0xF8 for hard disk)
    uint16_t fat_size_16;           // 22-23: FAT size in sectors (0 for FAT32)
    uint16_t sectors_per_track;     // 24-25: Sectors per track
    uint16_t num_heads;             // 26-27: Number of heads
    uint32_t hidden_sectors;        // 28-31: Hidden sectors
    uint32_t total_sectors_32;      // 32-35: Total sectors (used in FAT32)
    
    // FAT32 Extended Boot Record (36-89)
    uint32_t fat_size_32;           // 36-39: FAT size in sectors
    uint16_t ext_flags;             // 40-41: Extended flags
    uint16_t fs_version;            // 42-43: File system version (0)
    uint32_t root_cluster;          // 44-47: Root directory first cluster (usually 2)
    uint16_t fs_info;               // 48-49: FS info sector number (usually 1)
    uint16_t backup_boot_sector;    // 50-51: Backup boot sector (usually 6)
    uint8_t  reserved[12];          // 52-63: Reserved bytes
    uint8_t  drive_number;          // 64: Drive number
    uint8_t  reserved1;             // 65: Reserved
    uint8_t  boot_signature;        // 66: Extended boot signature (0x29)
    uint32_t volume_serial;         // 67-70: Volume serial number
    uint8_t  volume_label[11];      // 71-81: Volume label
    uint8_t  fs_type[8];           // 82-89: File system type ("FAT32   ")
    uint8_t  boot_code[420];       // 90-509: Boot code
    uint16_t signature;            // 510-511: Boot signature (0xAA55)
} __attribute__((packed)) fat32_boot_sector_t;

// FS Info Sector Structure (512 bytes)
typedef struct {
    uint32_t signature1;            // 0-3: Signature 0x41615252
    uint8_t  reserved1[480];        // 4-483: Reserved
    uint32_t signature2;            // 484-487: Signature 0x61417272
    uint32_t free_clusters;         // 488-491: Free cluster count
    uint32_t next_cluster;          // 492-495: Next free cluster hint
    uint8_t  reserved2[12];         // 496-507: Reserved
    uint32_t signature3;            // 508-511: Signature 0xAA550000
} __attribute__((packed)) fs_info_sector_t;

// Directory Entry Structure (32 bytes)
typedef struct {
    uint8_t  name[11];              // 0-10: 8.3 filename
    uint8_t  attributes;            // 11: File attributes
    uint8_t  reserved;              // 12: Reserved for Windows NT
    uint8_t  create_time_tenth;     // 13: Creation time in tenths of second
    uint16_t create_time;           // 14-15: Creation time
    uint16_t create_date;           // 16-17: Creation date
    uint16_t last_access_date;      // 18-19: Last access date
    uint16_t first_cluster_high;    // 20-21: High 16 bits of first cluster
    uint16_t write_time;            // 22-23: Last write time
    uint16_t write_date;            // 24-25: Last write date
    uint16_t first_cluster_low;     // 26-27: Low 16 bits of first cluster
    uint32_t file_size;             // 28-31: File size in bytes
} __attribute__((packed)) fat32_dir_entry_t;

// File Attributes
#define ATTR_READ_ONLY  0x01
#define ATTR_HIDDEN     0x02
#define ATTR_SYSTEM     0x04
#define ATTR_VOLUME_ID  0x08
#define ATTR_DIRECTORY  0x10
#define ATTR_ARCHIVE    0x20
#define ATTR_LONG_NAME  0x0F

// FAT32 Special Values
#define FAT32_FREE_CLUSTER    0x00000000
#define FAT32_BAD_CLUSTER     0x0FFFFFF7
#define FAT32_EOF_CLUSTER     0x0FFFFFF8
#define FAT32_EOF_CLUSTER_MAX 0x0FFFFFFF

// FAT32 File System Structure
typedef struct {
    int fd;                         // File descriptor for disk image
    fat32_boot_sector_t boot_sector; // Boot sector data
    fs_info_sector_t fs_info;       // FS info sector data
    uint32_t *fat_table;            // FAT table in memory
    uint32_t fat_start_sector;      // First sector of FAT
    uint32_t data_start_sector;     // First sector of data area
    uint32_t root_dir_cluster;      // Root directory cluster number
} fat32_fs_t;

// Helper function to create boot sector
int create_boot_sector(fat32_boot_sector_t *boot, uint32_t total_sectors) {
    // Clear the entire structure
    memset(boot, 0, sizeof(fat32_boot_sector_t));
    
    // Jump instruction (standard for x86)
    boot->jmp_boot[0] = 0xEB;
    boot->jmp_boot[1] = 0x58;
    boot->jmp_boot[2] = 0x90;
    
    // OEM name
    memcpy(boot->oem_name, "MYFAT32 ", 8);
    
    // Basic disk geometry
    boot->bytes_per_sector = 512;
    boot->sectors_per_cluster = 8;      // 8 sectors = 4KB clusters
    boot->reserved_sectors = 32;        // Standard for FAT32
    boot->num_fats = 2;                 // Always 2 FAT tables
    boot->media_type = 0xF8;            // Hard disk
    
    // FAT32 specific values
    boot->total_sectors_32 = total_sectors;
    
    // Calculate FAT size (this is the tricky part!)
    uint32_t data_sectors = total_sectors - boot->reserved_sectors;
    uint32_t clusters = data_sectors / boot->sectors_per_cluster;
    boot->fat_size_32 = (clusters * 4 + boot->bytes_per_sector - 1) / boot->bytes_per_sector;
    
    // Adjust for 2 FAT tables
    data_sectors -= (boot->fat_size_32 * 2);
    clusters = data_sectors / boot->sectors_per_cluster;
    
    // FAT32 specific
    boot->root_cluster = 2;             // Root directory starts at cluster 2
    boot->fs_info = 1;                  // FS info at sector 1
    boot->backup_boot_sector = 6;       // Backup at sector 6
    boot->boot_signature = 0x29;        // Extended boot signature
    boot->volume_serial = (uint32_t)time(NULL);  // Random serial number
    
    memcpy(boot->volume_label, "MY VOLUME  ", 11);
    memcpy(boot->fs_type, "FAT32   ", 8);
    
    // Boot sector signature
    boot->signature = 0xAA55;
    
    return 0;
}

// Helper function to create FS Info sector
int create_fs_info(fs_info_sector_t *fs_info, uint32_t total_clusters) {
    memset(fs_info, 0, sizeof(fs_info_sector_t));
    
    fs_info->signature1 = 0x41615252;
    fs_info->signature2 = 0x61417272;
    fs_info->free_clusters = total_clusters - 1;  // -1 because root dir uses cluster 2
    fs_info->next_cluster = 3;                    // Start searching from cluster 3
    fs_info->signature3 = 0xAA550000;
    
    return 0;
}

// 1. CREATE A NEW FAT32 FILESYSTEM (FIXED VERSION)
int fat32_create_filesystem(const char *filename, uint32_t size_mb) {
    printf("Creating FAT32 filesystem: %s (%u MB)\n", filename, size_mb);
    
    // Calculate total sectors
    uint32_t total_sectors = (size_mb * 1024 * 1024) / 512;
    printf("Total sectors: %u\n", total_sectors);
    
    // Create the file
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Cannot create filesystem file");
        return -1;
    }
    
    // Create boot sector
    fat32_boot_sector_t boot;
    if (create_boot_sector(&boot, total_sectors) < 0) {
        close(fd);
        return -1;
    }
    
    printf("FAT size: %u sectors\n", boot.fat_size_32);
    printf("Sectors per cluster: %u\n", boot.sectors_per_cluster);
    
    // Write boot sector (sector 0)
    if (write(fd, &boot, sizeof(boot)) != sizeof(boot)) {
        perror("Cannot write boot sector");
        close(fd);
        return -1;
    }
    
    // Create and write FS Info sector (sector 1)
    uint32_t total_clusters = (total_sectors - boot.reserved_sectors - (boot.fat_size_32 * 2)) / boot.sectors_per_cluster;
    fs_info_sector_t fs_info;
    create_fs_info(&fs_info, total_clusters);
    
    lseek(fd, 512, SEEK_SET);  // Go to sector 1
    if (write(fd, &fs_info, sizeof(fs_info)) != sizeof(fs_info)) {
        perror("Cannot write FS info sector");
        close(fd);
        return -1;
    }
    
    // Write backup boot sector (sector 6)
    lseek(fd, 6 * 512, SEEK_SET);
    if (write(fd, &boot, sizeof(boot)) != sizeof(boot)) {
        perror("Cannot write backup boot sector");
        close(fd);
        return -1;
    }
    
    // Initialize FAT tables with zeros - FIXED ALLOCATION
    uint32_t fat_size_bytes = boot.fat_size_32 * 512;
    printf("Allocating FAT buffer: %u bytes\n", fat_size_bytes);
    
    uint8_t *fat_buffer = calloc(1, fat_size_bytes);
    if (!fat_buffer) {
        printf("Cannot allocate FAT buffer of size %u bytes: %s\n", 
               fat_size_bytes, strerror(errno));
        close(fd);
        return -1;
    }
    printf("FAT buffer allocated successfully\n");
    
    // Set special FAT entries
    uint32_t *fat = (uint32_t *)fat_buffer;
    fat[0] = 0x0FFFFFF8;  // Media type + EOF
    fat[1] = 0x0FFFFFFF;  // EOF
    fat[2] = 0x0FFFFFFF;  // Root directory EOF
    
    // Write FAT 1
    lseek(fd, boot.reserved_sectors * 512, SEEK_SET);
    if (write(fd, fat_buffer, fat_size_bytes) != (ssize_t)fat_size_bytes) {
        perror("Cannot write FAT 1");
        free(fat_buffer);
        close(fd);
        return -1;
    }
    
    // Write FAT 2 (backup)
    if (write(fd, fat_buffer, fat_size_bytes) != (ssize_t)fat_size_bytes) {
        perror("Cannot write FAT 2");
        free(fat_buffer);
        close(fd);
        return -1;
    }
    
    free(fat_buffer);
    printf("FAT tables written successfully\n");
    
    // Initialize root directory (cluster 2) with zeros - FIXED ALLOCATION
    uint32_t root_sector = boot.reserved_sectors + (boot.fat_size_32 * 2);
    uint32_t cluster_size_bytes = boot.sectors_per_cluster * 512;
    
    printf("Initializing root directory at sector %u, cluster size: %u bytes\n", 
           root_sector, cluster_size_bytes);
    
    lseek(fd, root_sector * 512, SEEK_SET);
    
    // Allocate and zero-initialize cluster buffer - FIXED
    uint8_t *cluster_buffer = calloc(1, cluster_size_bytes);
    if (!cluster_buffer) {
        printf("Cannot allocate cluster buffer of size %u bytes: %s\n", 
               cluster_size_bytes, strerror(errno));
        close(fd);
        return -1;
    }
    printf("Cluster buffer allocated successfully\n");
    
    // Write the root directory cluster
    if (write(fd, cluster_buffer, cluster_size_bytes) != (ssize_t)cluster_size_bytes) {
        perror("Cannot write root directory");
        free(cluster_buffer);
        close(fd);
        return -1;
    }
    
    free(cluster_buffer);
    printf("Root directory initialized successfully\n");
    
    close(fd);
    
    printf("FAT32 filesystem created successfully!\n");
    return 0;
}

// 2. MOUNT AN EXISTING FAT32 FILESYSTEM - IMPROVED ERROR HANDLING
int fat32_mount(fat32_fs_t *fs, const char *filename) {
    printf("Mounting FAT32 filesystem: %s\n", filename);
    
    // Initialize the structure
    memset(fs, 0, sizeof(fat32_fs_t));
    fs->fd = -1;
    
    // Open the filesystem file
    fs->fd = open(filename, O_RDWR);
    if (fs->fd < 0) {
        perror("Cannot open filesystem file");
        return -1;
    }
    
    // Read boot sector
    if (read(fs->fd, &fs->boot_sector, sizeof(fs->boot_sector)) != sizeof(fs->boot_sector)) {
        perror("Cannot read boot sector");
        close(fs->fd);
        fs->fd = -1;
        return -1;
    }
    
    // Verify it's a valid FAT32 filesystem
    if (fs->boot_sector.signature != 0xAA55) {
        printf("Invalid boot sector signature: 0x%X\n", fs->boot_sector.signature);
        close(fs->fd);
        fs->fd = -1;
        return -1;
    }
    
    if (strncmp((char*)fs->boot_sector.fs_type, "FAT32", 5) != 0) {
        printf("Not a FAT32 filesystem: %.8s\n", fs->boot_sector.fs_type);
        close(fs->fd);
        fs->fd = -1;
        return -1;
    }
    
    // Read FS Info sector
    lseek(fs->fd, fs->boot_sector.fs_info * 512, SEEK_SET);
    if (read(fs->fd, &fs->fs_info, sizeof(fs->fs_info)) != sizeof(fs->fs_info)) {
        perror("Cannot read FS info sector");
        close(fs->fd);
        fs->fd = -1;
        return -1;
    }
    
    // Calculate important values
    fs->fat_start_sector = fs->boot_sector.reserved_sectors;
    fs->data_start_sector = fs->fat_start_sector + (fs->boot_sector.num_fats * fs->boot_sector.fat_size_32);
    fs->root_dir_cluster = fs->boot_sector.root_cluster;
    
    // Load FAT table into memory - IMPROVED ALLOCATION
    uint32_t fat_size_bytes = fs->boot_sector.fat_size_32 * 512;
    printf("Loading FAT table: %u bytes\n", fat_size_bytes);
    
    fs->fat_table = malloc(fat_size_bytes);
    if (!fs->fat_table) {
        printf("Cannot allocate FAT table memory of size %u bytes: %s\n", 
               fat_size_bytes, strerror(errno));
        close(fs->fd);
        fs->fd = -1;
        return -1;
    }
    
    lseek(fs->fd, fs->fat_start_sector * 512, SEEK_SET);
    if (read(fs->fd, fs->fat_table, fat_size_bytes) != (ssize_t)fat_size_bytes) {
        perror("Cannot read FAT table");
        free(fs->fat_table);
        fs->fat_table = NULL;
        close(fs->fd);
        fs->fd = -1;
        return -1;
    }
    
    printf("FAT32 filesystem mounted successfully!\n");
    printf("- FAT starts at sector: %u\n", fs->fat_start_sector);
    printf("- Data starts at sector: %u\n", fs->data_start_sector);
    printf("- Root directory cluster: %u\n", fs->root_dir_cluster);
    printf("- Free clusters: %u\n", fs->fs_info.free_clusters);
    
    return 0;
}

// 3. UNMOUNT FILESYSTEM - IMPROVED
void fat32_unmount(fat32_fs_t *fs) {
    if (fs->fd >= 0) {
        // Write back FAT table
        lseek(fs->fd, fs->fat_start_sector * 512, SEEK_SET);
        uint32_t fat_size_bytes = fs->boot_sector.fat_size_32 * 512;
        write(fs->fd, fs->fat_table, fat_size_bytes);
        
        // Write back FS info
        lseek(fs->fd, fs->boot_sector.fs_info * 512, SEEK_SET);
        write(fs->fd, &fs->fs_info, sizeof(fs->fs_info));
        
        close(fs->fd);
        fs->fd = -1;
    }
    
    if (fs->fat_table) {
        free(fs->fat_table);
        fs->fat_table = NULL;
    }
    
    printf("FAT32 filesystem unmounted\n");
}

// 4. CONVERT CLUSTER NUMBER TO SECTOR NUMBER
uint32_t fat32_cluster_to_sector(fat32_fs_t *fs, uint32_t cluster) {
    // Cluster 2 is the first data cluster
    if (cluster < 2) {
        return 0;  // Invalid cluster
    }
    
    // Formula: data_start + (cluster - 2) * sectors_per_cluster
    return fs->data_start_sector + ((cluster - 2) * fs->boot_sector.sectors_per_cluster);
}

// 5. GET FAT ENTRY (WHAT CLUSTER POINTS TO)
uint32_t fat32_get_fat_entry(fat32_fs_t *fs, uint32_t cluster) {
    if (cluster >= (fs->boot_sector.fat_size_32 * 512) / 4) {
        return FAT32_EOF_CLUSTER;  // Out of range
    }
    
    // FAT32 uses 32-bit entries, but only 28 bits are used
    return fs->fat_table[cluster] & 0x0FFFFFFF;
}

// 6. SET FAT ENTRY (MAKE CLUSTER POINT TO SOMETHING)
int fat32_set_fat_entry(fat32_fs_t *fs, uint32_t cluster, uint32_t value) {
    if (cluster >= (fs->boot_sector.fat_size_32 * 512) / 4) {
        return -1;  // Out of range
    }
    
    // Preserve upper 4 bits, set lower 28 bits
    fs->fat_table[cluster] = (fs->fat_table[cluster] & 0xF0000000) | (value & 0x0FFFFFFF);
    
    return 0;
}

// 7. READ DIRECTORY ENTRIES FROM A CLUSTER
int fat32_read_directory(fat32_fs_t *fs, uint32_t cluster, fat32_dir_entry_t **entries, uint32_t *count) {
    if (!fs || !entries || !count) {
        return -1;
    }
    
    *entries = NULL;
    *count = 0;
    
    // Calculate cluster size in bytes
    uint32_t cluster_size = fs->boot_sector.sectors_per_cluster * 512;
    uint32_t entries_per_cluster = cluster_size / sizeof(fat32_dir_entry_t);
    
    printf("Reading directory cluster %u (size: %u bytes, %u entries max)\n", 
           cluster, cluster_size, entries_per_cluster);
    
    // Allocate buffer for directory entries - FIXED ALLOCATION
    fat32_dir_entry_t *dir_buffer = malloc(cluster_size);
    if (!dir_buffer) {
        printf("Cannot allocate directory buffer of size %u bytes: %s\n", 
               cluster_size, strerror(errno));
        return -1;
    }
    
    // Read the directory cluster
    uint32_t sector = fat32_cluster_to_sector(fs, cluster);
    lseek(fs->fd, sector * 512, SEEK_SET);
    
    if (read(fs->fd, dir_buffer, cluster_size) != (ssize_t)cluster_size) {
        perror("Cannot read directory cluster");
        free(dir_buffer);
        return -1;
    }
    
    // Count valid entries (non-zero first byte)
    uint32_t valid_count = 0;
    for (uint32_t i = 0; i < entries_per_cluster; i++) {
        if (dir_buffer[i].name[0] != 0x00 && dir_buffer[i].name[0] != 0xE5) {
            valid_count++;
        } else if (dir_buffer[i].name[0] == 0x00) {
            break; // End of directory
        }
    }
    
    printf("Found %u valid directory entries\n", valid_count);
    
    *entries = dir_buffer;
    *count = entries_per_cluster; // Return total capacity, not just valid entries
    return 0;
}

// Utility functions
void print_boot_sector_info(fat32_boot_sector_t *boot) {
    printf("\n=== Boot Sector Information ===\n");
    printf("OEM Name: %.8s\n", boot->oem_name);
    printf("Bytes per sector: %u\n", boot->bytes_per_sector);
    printf("Sectors per cluster: %u\n", boot->sectors_per_cluster);
    printf("Reserved sectors: %u\n", boot->reserved_sectors);
    printf("Number of FATs: %u\n", boot->num_fats);
    printf("FAT size: %u sectors\n", boot->fat_size_32);
    printf("Total sectors: %u\n", boot->total_sectors_32);
    printf("Root cluster: %u\n", boot->root_cluster);
    printf("FS Info sector: %u\n", boot->fs_info);
    printf("Volume label: %.11s\n", boot->volume_label);
    printf("FS type: %.8s\n", boot->fs_type);
}

void print_fs_info(fs_info_sector_t *fs_info) {
    printf("\n=== FS Info ===\n");
    printf("Free clusters: %u\n", fs_info->free_clusters);
    printf("Next free cluster hint: %u\n", fs_info->next_cluster);
}

int main() {
    printf("=== FAT32 File System Implementation (FIXED) ===\n");
    
    // Test our implementation
    fat32_fs_t fs;
    
    // Create a 10MB filesystem
    printf("\n1. Creating filesystem...\n");
    if (fat32_create_filesystem("SINHX.img", 100) < 0) {
        return 1;
    }
    
    // Mount the filesystem
    printf("\n2. Mounting filesystem...\n");
    if (fat32_mount(&fs, "SINHX.img") < 0) {
        return 1;
    }
    
    // Print information
    print_boot_sector_info(&fs.boot_sector);
    print_fs_info(&fs.fs_info);
    
    // Test cluster-to-sector conversion
    printf("\n3. Testing cluster conversion...\n");
    for (uint32_t cluster = 2; cluster <= 5; cluster++) {
        uint32_t sector = fat32_cluster_to_sector(&fs, cluster);
        printf("Cluster %u -> Sector %u\n", cluster, sector);
    }
    
    // Test FAT operations
    printf("\n4. Testing FAT operations...\n");
    printf("FAT[2] = 0x%08X (should be EOF for root dir)\n", fat32_get_fat_entry(&fs, 2));
    printf("FAT[3] = 0x%08X (should be free)\n", fat32_get_fat_entry(&fs, 3));
    
    // Test setting a FAT entry
    fat32_set_fat_entry(&fs, 3, 4);
    fat32_set_fat_entry(&fs, 4, FAT32_EOF_CLUSTER);
    printf("After setting: FAT[3] = 0x%08X, FAT[4] = 0x%08X\n", 
           fat32_get_fat_entry(&fs, 3), fat32_get_fat_entry(&fs, 4));
    
    // Test directory reading - NEW TEST
    printf("\n5. Testing directory operations...\n");
    fat32_dir_entry_t *dir_entries;
    uint32_t dir_count;
    
    if (fat32_read_directory(&fs, fs.root_dir_cluster, &dir_entries, &dir_count) == 0) {
        printf("Root directory read successfully (%u entries capacity)\n", dir_count);
        free(dir_entries);
    } else {
        printf("Failed to read root directory\n");
    }
    
    // Unmount
    // printf("\n6. Unmounting filesystem...\n");
    // fat32_unmount(&fs);
    
    printf("\nAll tests completed successfully!\n");
    return 0;
}