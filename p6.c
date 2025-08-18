#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    
    int A, B, C = 0;
    
    console("Input Three Numbers : ");
    input("%i, %i, %i", &A, &B, &C);

    if(A > B) {
        if(A > C) {
            console("A=%i\n", A);
        } else {
            console("C=%i\n", C);
        }
    } else {
        if(B > C) {
            console("B=%i\n", B);
        } else {
            console("C=%i\n", C);
        }
    }

    return 0;
}