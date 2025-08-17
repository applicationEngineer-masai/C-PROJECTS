#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// use fmod for '%'

#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)

int main() {
    
    int x=0;
    float y=0.0;
    console("input a integer\n");
    input("%i", &x);
    y = (float)x;
    console("int x = %i and float y=%f\n", x, y);
    return 0;
}