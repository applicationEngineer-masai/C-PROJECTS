#include <stdio.h>
#include <stdlib.h>

#define MAX 7

int main(int argc, char const **argv[])
{
    int *array = calloc(MAX, sizeof(int));

    for(int i=0; i<MAX; i++) array[i] = i+1;
    for(int i=0; i<MAX; i++) printf("%d\n", array[i]);

    array = realloc(array, 3*sizeof(int));
    printf("REALLOC -----\n");
    
    array[7] = 8;
    array[8] = 9;
    array[9] = 10;

    for(int i=0; i<10; i++) printf("%d\n", array[i]);

    return 0;
}
