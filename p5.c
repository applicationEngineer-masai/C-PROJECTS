
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    
    int user = 0;
    console("Enter number : ");
    input("%i", &user);

    if(user % 2 == 0) {
        console("Even\n");
    } else {
        console("Odd\n");
    }
    return 0;
}