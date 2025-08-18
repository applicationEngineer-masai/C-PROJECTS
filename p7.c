#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    console("Enter Year : ");
    int year = 0;
    input("%i", &year);

    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        console("Year=%i is Leap Year\n", year);
    } else {
        console("Year=%i is Not Leap Year\n", year);
    }
    return 0;       
}