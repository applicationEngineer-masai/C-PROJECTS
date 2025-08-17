#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

char* string_input(char *msg) {
 
    int INIT_SIZE = 5;
    const int NEW_SIZE = 5;
    int current_size = INIT_SIZE;
    int index=0;

    printf("%s\n", msg);

    char *name = (char *)malloc(current_size * sizeof(char));

    if (name == NULL) {
        free(name);
        perror("memory allocation failed");
        exit(EXIT_FAILURE);

    } else {
        while(1) {
            char ch = getchar();
            if(ch == '\n' || ch == EOF) {
                break;
            }

            if(index >= current_size -1) {
                current_size+=NEW_SIZE;
                char *tmp = realloc(name, current_size * sizeof(char));
                if (tmp == NULL) {
                    free(name);
                    perror("memory allocation failed");
                    exit(EXIT_FAILURE);
                }
                name = tmp;
            }
            name[index++]=ch;
        }
    }
    name[index]='\0';
    return name;
}


int main() {

    char *input = string_input("Hello, Enter You Name : ");
    printf("%s\n", input);
    return 0;
}