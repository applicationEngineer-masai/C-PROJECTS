#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top=NULL;

void push(int V) {
    
    struct Node *N = (struct Node *)malloc(sizeof *N);

    if(N == NULL) {
        fprintf(stderr, "Memory allocation failed for new node, %s\n", strerror(errno));
        exit(1);
    }

    N->data = V;
    N->next = top;
    top=N;
}

int pop() {
    if(top == NULL) {
        fprintf(stderr,"Stack underflow %s\n", strerror(errno));
        exit(1);
    }

    int val = top->data;
    struct Node *temp = top;
    top = top->next;
    free(temp);
    return val;
}

int peek() {
    return (top != NULL) ? top->data : -1;
}

void free_all() {
    while (top)
    {
        pop();
    }
}

int main() {

    push(10);
    push(20);
    push(30);

    printf("Top: %d\n", peek());    // 30
    printf("Popped: %d\n", pop());  // 30
    printf("Top: %d\n", peek());    // 20

    free_all();

}