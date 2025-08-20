#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    
    int* ptr = (int*) malloc(3*sizeof(int));
    int* ptr2 =(int*) calloc(3, sizeof(int));

    ptr[0] = 44;
    ptr[1] = 55;
    ptr[2] = 66;

    ptr2[0] = 88;
    ptr2[1] = 99;
    ptr2[2] = 109;

    printf("%i\n", ptr[0]);
    printf("%i\n", ptr[1]);
    printf("%i\n", ptr[2]);
    printf("%i\n", ptr2[0]);
    printf("%i\n", ptr2[1]);
    printf("%i\n", ptr2[2]);

    int *temp = (int*) realloc(ptr, 6*sizeof(int));
    if(temp == NULL) {
        free(ptr);
    } else {
        ptr = temp;
    }

    for (int i = 3; i < 6; i++) {
        ptr[i] = (i + 1) * 10;
    }

    for (int i = 0; i < 6; i++) {
        printf("ptr[%d] = %d\n", i, ptr[i]);
    }
    
    return 0;
}