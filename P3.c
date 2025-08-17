#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// use fmod for '%'

#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)

int main() {
    float L1, L2, B1, B2 = 0.0;
    double perimeter=0.0;

    console("supply rect_L1, react_L2, rect_B1, rect_B2 : ");
    input("%f, %f, %f, %f", &L1, &L2, &B1, &B2);

    perimeter=(double)L1+L2+B1+B2;
    console("PERIMETER : %f\n", perimeter);

    return 0;
}