#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 300
char STACK[MAX];
int top = -1;

void push(char data) {
    if(top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    STACK[++top] = data;
}

char pop() {
    if(top == -1) {
        return '\0';
    }
    char val = STACK[top--];
    return val;
}

bool is_matching(char opener, char closer) {
    return (opener == '(' && closer == ')') ||
           (opener == '{' && closer == '}') ||
           (opener == '[' && closer == ']');
}

bool is_opener(char ch) {
    return (ch == '(' || ch == '{' || ch == '[');
}

bool is_closer(char ch) {
    return (ch == ')' || ch == '}' || ch == ']');
}

int main(int argc, char const *argv[])
{
    char *str = "{[([{}])]}";

    for(int i=0; i<strlen(str); i++) {
        
        if(is_opener(str[i])) {
            push(str[i]);
        } else if(is_closer(str[i])) {
            if(top == -1) {
                printf("Unbalanced");
                return 0;
            }
            char last = pop();
            if (!is_matching(last, str[i])) {
                printf("Unbalanced\n");
                return 0;
            }
        }
    }

    if (top == -1) {
        printf("Balanced\n");
    } else {
        printf("Unbalanced\n");
    }
    
    return 0;
}
