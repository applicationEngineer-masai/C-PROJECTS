#include <stdio.h>
#include <stdlib.h>

#define MAX 7

int main(int argc, char const *argv[])
{
    
    int *array = malloc(MAX * sizeof(int));

    for(int i=0; i<MAX; i++) array[i] = i+1;
    for(int i=0; i<MAX; i++) printf("%d\n", array[i]);
    
    return 0;
}
