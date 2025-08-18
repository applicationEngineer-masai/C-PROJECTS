#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    int user=0;

    console("Enter a number : ");
    input("%i", &user);
    if(user > 0) {
        console("Positive\n");
    }
    if(user < 0) {
        console("Negative\n");
    } else {
        console("Zero\n");
    }
    return 0;
}