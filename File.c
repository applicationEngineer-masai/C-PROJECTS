#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)

#define MAX_LEN 1024

int main() {
    
    FILE *fp;
    char buff[MAX_LEN];
    char i[MAX_LEN];

    fp = fopen("/home/daani/Documents/PROJECTS/C-PROJECTS/Test.txt", "r");

    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(buff, sizeof(buff), fp) != NULL) {
        printf("%s", buff);
    }

    fflush(fp);
    fclose(fp);

    printf("Writing Mode....\n");

    fp = fopen("/home/daani/Documents/PROJECTS/C-PROJECTS/Test.txt", "a+");

    if(fp == NULL) {
        perror("Opening File to Write is Failed\n");
        return -1;
    }

    printf("Enter : ");
    fgets(i, sizeof(i), stdin);
    getchar();

    fprintf(fp, "%s", i);
    fflush(fp);
    fclose(fp);

    return 0;
}