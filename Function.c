#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)

int swap(int N, ...) {
    va_list args; // declare variable type of va_list that is pass by function call
    va_start(args, N); // initialize all variables and points to the first arg

    if(N == 2) {
        int x = va_arg(args, int); // Retrieve next arg of its type
        int y = va_arg(args, int);

        int z = x;
        x = y;
        y = z;

        console("X=%i and Y=%i\n", x, y);
    }
}

// use fmod() place of %

int main() {
    
    int x=5;
    int y=6;

    console("X=%i and Y=%i\n", x, y);
    swap(2, x, y);
    return 0;
}