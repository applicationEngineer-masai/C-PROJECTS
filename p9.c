#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    
    console("Enter a Table No.\t");
    int table=0;
    input("%i", &table);

    if(table == 0) {
        perror("table initial value is zero, why ?");
        exit(EXIT_FAILURE);
    }

    for(__uint8_t i=1; i<=10; i++) {
        console("%i X %i = %i\n", i, table, i*table);
    }
    return 0;
}