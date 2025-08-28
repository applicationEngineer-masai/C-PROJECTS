#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define MAX 256
#define INITIAL -1
#define OVERFLOW MAX-1


int stack[MAX], top=INITIAL;

void push(int value) {
    if(top == OVERFLOW) {
        fprintf(stderr, "Stack overflow %s\n", strerror(errno));
        return;
    }
    stack[++top]=value;
}

int pop(void) {
    if(top == INITIAL) {
        fprintf(stderr, "Stack Underflow %s\n", strerror(errno));
        return -1;
    }
    return stack[top--];
}

int peek(void) {
    if (top == INITIAL) {
        fprintf(stderr, "Stack Empty %s\n", strerror(errno));
        return -1;
    }
    return stack[top];
}

bool isEmpty(void) {
    if(top == INITIAL) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char const *argv[])
{
    push(10);
    push(20);
    push(30);

    printf("Top element: %d\n", peek());
    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());
    printf("Top element: %d\n", peek());

    return 0;
}
