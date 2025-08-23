#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#define INITIAL_SIZE 10
#define GROW_FACTOR 2

int *STACK=NULL;
int capacity = 0;
int top = -1;

bool init_stack() {
    STACK = (int *) malloc(INITIAL_SIZE*sizeof(int));
    if(STACK == NULL) {
        fprintf(stderr, "memory allocation failed %s\n", strerror(errno));
        return false;
    }
    capacity=INITIAL_SIZE;
    top=-1;
    return true;
}

bool increase_size() {
    int new_scale = capacity * GROW_FACTOR;
    int *temp_mem = (int *) realloc(STACK, new_scale*sizeof(int));
    if (temp_mem == NULL) {
        fprintf(stderr, "Memory reallocation failed! %s\n", strerror(errno));
        return false;
    }
    STACK = temp_mem;
    capacity= new_scale;
    return true;
}

bool isFull() {
    if(top == capacity-1) return true;
    else return false;
}

bool isEmpty() {
    if(top == -1) return true;
    else return false; 
}

int peek() {
    if(!isEmpty()) {
        return STACK[top];
    } else {
        return -1;
    }
}

int push(int value) {
    if(isFull()) {
        if(!increase_size()) {
            return -1;
        }
    }
    return STACK[++top] = value;
}

int pop() {
    if(isEmpty()) {
        return -1;
    } else {
        return STACK[top--];
    }
}

void print_stack() {
    for(int i=0; i<=top; i++) {
        printf("%d\n", STACK[i]);
    }
}

int main() {

    printf("PRESS : e to Exit\n");
    init_stack();
    int temp=0;
    char ch='\0';

    for(int i=0; i<capacity; i++) {

        if(i == capacity-1) {
            increase_size();
        }
        
        printf("Enter elements : ");
        scanf("%d", &temp);
        getchar();
        push(temp);

        printf("Pop [y/n/e/p] : ");
        scanf("%c", &ch);
        getchar();

        if(ch == 'e') {
            exit(0);
        }
        else if(ch == 'y') {
            pop();

        } else if(ch == 'p') {
            print_stack();
        } else {
            continue;   
        }
    }

    return 0;
}