#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    
    __uint8_t x = 222;
    __uint32_t sum = 0;

    for(__uint8_t i=1; i<=x; i++) {
        if(i % 2 != 0) {
            sum += i;
        }
    }

    console("SUM=%u\n", sum);

    return 0;
}