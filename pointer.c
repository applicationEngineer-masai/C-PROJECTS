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
    
    int i = 3;

    console("%i\n", i);
    console("Address of i = %p\n", &i);
    console("Value of i = %i\n", i);
    console("(get value at address ->(get address and pass)) of i = %i\n", *(&i));
    
    return 0;
}