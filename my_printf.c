#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)

void kernel_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while(*format) {
        if(*format == '%') {
            format++; // Move past the '%' character
            switch(*format) {
                case 'i':
                case 'd': { // Handle both %i and %d
                    int val = va_arg(args, int);
                    printf("%d", val); // Remove \n to match normal printf behavior
                    break;
                }
                case 'u': {
                    unsigned int val = va_arg(args, unsigned int);
                    printf("%u", val);
                    break;
                }
                case 's': {
                    char *buff = va_arg(args, char*);
                    printf("%s", buff); // Remove \n
                    break;
                }
                case 'c': {
                    int val = va_arg(args, int);
                    printf("%c", val);
                    break;
                }
                case '%': {
                    printf("%%"); // Handle literal %
                    break;
                }
                default:
                    printf("%%"); 
                    printf("%c", *format);
                    break;
            }
        } else {
            printf("%c", *format); 
        }
        format++;
    }
    
    va_end(args);
}

int main() {
    
    kernel_printf("%d %u %s", 454, 354, "Hello danishk sinha\n");
    return 0;
}