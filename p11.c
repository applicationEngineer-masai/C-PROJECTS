#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)


// use fmod() place of %

int main() {
    
    // console input game

    char ch='c';
    console("Enter characters\n");

    do {

        ch = getchar();
        console("%c", ch);

    } while (ch != '\t' && ch != EOF);

    return 0;
}