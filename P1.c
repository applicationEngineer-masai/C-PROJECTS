#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


int main() {
    
    float x=0.0;
    float y=0.0;

    console("Enter First Numbers : ");
    input("%f", &x);
    console("Enter Second Numbers : ");
    input("%f", &y);

    console("addition : %f\n", x+y);
    console("subtraction : %f\n", x-y);
    console("multiplication : %f\n", x*y);
    console("division : %f\n", x/y);
    console("modulo : %f\n", fmod(x, y));

    return 0;
}