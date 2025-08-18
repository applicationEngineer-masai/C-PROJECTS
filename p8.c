#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    int x, y = 0;

    console("Enter Two Numbers : ");
    input("%i, %i", &x, &y);

    (x > y) ? console("x is greater\n") : console("y is greater\n");
    return 0;
}