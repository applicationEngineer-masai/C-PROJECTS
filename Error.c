#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#define ERR_SUCCESS 0
#define ERR_STACK_OVERFLOW 1001
#define ERR_STACK_UNDERFLOW 1002
#define STACK_MAX 3

#define STACK_STATUS() \
            handle_custom_errno(ERR_SUCCESS) \


// stander error
void handle_error(const char* op) {
    switch(errno) {
        case ENOENT:
            printf("no such file or dir named as %s\n", op);
            break;
        case EACCES:
            printf("Permission denied to open %s\n", op);
            break;
        case ENOMEM:
            printf("Out of memory %s\n", op);
            break;
        
        default:
            printf("Error in %s: Unknown error (errno = %d): %s\n", 
                   op, errno, strerror(errno));
            break;

    }
}

// custom error
void handle_custom_errno(int err_code) {
    switch(err_code) {
        case ERR_SUCCESS:
            printf("success\n");
            return;
        case ERR_STACK_OVERFLOW:
            printf("stack overflow\n");
            exit(-1);
        case ERR_STACK_UNDERFLOW:
            printf("stack underflow\n");
            exit(-1);
        default:
            printf("Unknown Error Code %d\n", err_code);
            return;
    }
}

// custom error handler
int STACK_ARR[STACK_MAX];
int top = -1;

void push(int value) {
    if (top == STACK_MAX-1) {
        handle_custom_errno(ERR_STACK_OVERFLOW);
    }
    STACK_ARR[++top];
}

int pop(void) {
    if (top == -1) {
        handle_custom_errno(ERR_STACK_UNDERFLOW);
    }
    return STACK_ARR[top--];
}


int main(int argc, const char* argv[]) {

    FILE *fp;
    int fd;

    fp = fopen("gsdfgdfghdshgsdfhgsdfhgdfshgdfshgdfhgdfshgsdf.txt", "r");
    if(fp == NULL) {
        handle_error("gsdfgdfghdshgsdfhgsdfhgdfshgdfshgdfhgdfshgsdf.txt");
    }

    push(10);
    push(20);
    push(30);
    // push(40); stack overflow
    
    pop();
    pop();
    STACK_STATUS();
    pop();
    // pop(); stack underflow
}