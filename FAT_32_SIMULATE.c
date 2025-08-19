
/*

    EXAMPLE TO VISUALIZE FAT_32 and (claude will help to write actual FAT_32 fs, after teaching me the theory)
    but we focus on theory first, because if theory is understand then code is pice of cake


    */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


typedef struct {
    char data[512]; // 1 sector = 512 bytes
} sector_t;

typedef struct {
    sector_t sectors[4]; // 1 cluster = 4 sectors
} cluster_t;



int main() {
    
    console("SIZE of 1 sector %li\n", sizeof(sector_t));
    console("SIZE of 1 cluster %li\n", sizeof(cluster_t));

    // assume i have 1 file and size of file is 1000 bytes
    int file_size = 1000;
    int sector_needed = (file_size + 511) / 512; // Round up division
    int cluster_needed = (file_size + 2047) / 2048; // Round up cluster

    console("I I HAVE TO STORE 1 FILE THAT SIZE IS 1000 bytes, WE NEED:\n");
    console("WE NEED %i sectors\t|OR|\t", sector_needed);
    console("WE NEED %i clusters\n", cluster_needed);

    return 0;
}

/*

    CLAUDE Q1 : Table: "File 'photo.jpg' uses clusters 5, 6, 7, then ends"
    Data Area: Actually stores the file content in those clusters

    *DANISHK's Answer to claude:
        so the boot sector start with 0 - 0
        and reserved from 1 to 31  
        both are 32, and 1 sector = 512bytes
        which means inside 1st sector we can fit boot-record and reserved spaces
        and we have extra 480 bytes in 1st sector, ok

        now the question is a photo.jpg takes 5, 6, 7 cluster then the
        space required by photo is 
        1 cluster = 2048 bytes
        so three custer 5, 6, 7 can take 2048*3 = 6144 bytes
        so 6144 bytes in 6.144 around,
        so 6.144 kb disk space we need ! thank!!
        give me my understanding feedback 

*/