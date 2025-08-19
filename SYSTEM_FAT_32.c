#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)

// FAT32 Boot Sector Structure (512 bytes)

typedef struct {
    uint8_t jmp_boot[3]; // 0-2 jmp instruction to boot code
    uint8_t oem_name[8]; // 3-10 OEM String name
    uint16_t bytes_per_sector; // 11-12 Bytes per cluster (usually 512) 
    uint8_t sector_per_cluster; // 13 : Sector Per Cluster (power 2) 
    uint16_t reserved_sectors; // 14-15: RESERVED sector (usually 32)
    uint8_t num_fats; // 16 Numbers of FAT (usually 2)
    uint16_t root_entries; // 17-18: Root Entries (0 for fat 32)
    uint16_t total_sectors_16; // 19-20: Total sectors if < 65536 (0 for FAT32)
    uint8_t media_type; // 21: Media Typed (0xF8 for hard disk)
    uint16_t fat_size_16; // 22-23: FAT size in sector (0 for FAT32)
    uint16_t sectors_per_track; // 24-25: Sectors per Track
    uint16_t nums_of_head; // 26-27: numbers of heads
    uint32_t hidden_sectors; // 27-28: Hidden sectors
    uint32_t total_sectors_32; // 32-35: Total sectors (used in FAT32)

    // FAT32 Extended boot record
    uint32_t fat_size_32; // 36-39: fat size in sectors
    uint16_t ext_flags; // 40-41: Extended flags
    uint16_t fs_version; // 42-43: File system version (0)
    uint32_t root_cluster; // 44-47: Root Dir First Cluster
    uint16_t fs_info; // 48-49: FS info sector name (usually 1)
    uint16_t backup_boot_sector; // 50-51: backup boot sector (usually 6)
    uint8_t reserved[12]; // 52-63: Reserved-bytes
    uint8_t drive_number; // 64: Drive number
    uint8_t reserved1; // 65: Reserved
    uint8_t boot_signature; // 66: Extended boot signature (0x29)
    uint32_t volume_serial; // 67-70: Volume serial number
    uint8_t volume_label[11]; // 71-81: Volume label
    uint8_t fs_type[8]; // 82-89: FILE_SYSTEM TYPE ("FAT32   ")
    uint8_t boot_code[420]; // 90-509: Boot code
    uint16_t signature; // 510-511: boot signature

} __attribute__((packed)) fat32_boot_sector_t;


// FS Info Sector Structure (512 bytes)
typedef struct
{
    uint32_t signature; // 0-3: Signature 0x41615252
    uint8_t reserved1[480]; // 4-483: reserved
    uint32_t signature2; // 484-487: Signature 0x61417272
    uint32_t free_clusters; // 488-491: Free cluster count
    uint32_t next_cluster; // 492-495: Next free cluster hint
    uint8_t reserved2[12]; // 496-507: Reserved
    uint32_t signature3; // 508-511: Signature 0xAA550000

}__attribute__((packed)) fs_info_sector_t;

// Directory Entry structure (32)
typedef struct
{
    uint8_t name[11]; // 0-10: 8.3 filename
    uint8_t attributes; // 11: File attributes
    uint8_t reserved; // 12: Reserved for Windows NT
    uint8_t create_time_tenth; // 13: Create Time in tenth of seconds
    uint16_t create_time;           // 14-15: Creation time
    uint16_t create_date;           // 16-17: Creation date
    uint16_t last_access_date;      // 18-19: Last access date
    uint16_t first_cluster_high;    // 20-21: High 16 bits of first cluster
    uint16_t write_time;            // 22-23: Last write time
    uint16_t write_date;            // 24-25: Last write date
    uint16_t first_cluster_low;     // 26-27: Low 16 bits of first cluster
    uint32_t file_size;             // 28-31: File size in bytes

}__attribute__((packed)) fat32_dir_entry_t;

// FILE ATTRIBUTE
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

// FAT File system Structure
typedef struct
{
    int fd; // // File descriptor for disk image
    fat32_boot_sector_t boot_sector; // Boot sector data
    fs_info_sector_t fs_info; // FS info sector data
    uint32_t *fat_table; // FAT table in memory
    uint32_t fat_start_section; // First sector of FAT
    uint32_t data_start_sector; // First sector of data area
    uint32_t root_dir_cluster; // Root directory cluster number

} fat32_fs_t;

// Functions Prototypes
int fat32_create_filesystem(const char *filename, uint32_t size_mb);
int fat32_mount(fat32_fs_t *fs, const char *filename);
void fat32_unmount(fat32_fs_t *fs);
uint32_t fat32_cluster_to_sector(fat32_fs_t *fs, uint32_t cluster);
uint32_t fat32_get_fat_entry(fat32_fs_t *fs, uint32_t cluster);
int fat32_set_fat_entry(fat32_fs_t *fs, uint32_t cluster, uint32_t value);

// utils
void print_boot_sector_info(fat32_boot_sector_t *boot);
void print_fs_info(fs_info_sector_t *fs_info);

int main(int *argc, char *argv[]) {
    
    printf("=== FAT32 File System Implementation ===\n");
    return 0;
}