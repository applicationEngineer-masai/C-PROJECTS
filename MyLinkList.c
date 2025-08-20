#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)
#define NULL ((void*)0)

typedef enum {
    I8,
    I16,
    I32,
    I64,
    I128,
    U8,
    U16,
    U32,
    U64,
    U128,
    F32,
    F64,
    CHAR,
    STRING,
    FLOAT,
    BOOL,
    Pointer,
}Type;

typedef struct
{
    Type type;
    union {
        int8_t I8;
        int16_t I16;
        int32_t I32;
        int64_t I64;
        __int128_t I128;
        uint8_t U8;
        uint16_t U16;
        uint32_t U32;
        uint64_t U64;
        __uint128_t U128;
        float F32;
        double F64;
        char CHAR;
        char* STRING;
        bool BOOL;
        void* Pointer;
    }Values;
}DataType;

typedef struct Node {
    DataType data;
    struct Node* next;
}Node;

// Helper function to create a DataType
DataType createDataType(Type type, ...) {
    DataType dt;
    dt.type = type;
    
    va_list args;
    va_start(args, type);
    
    switch(type) {
        case I8:
            dt.Values.I8 = (int8_t)va_arg(args, int);
            break;
        case I16:
            dt.Values.I16 = (int16_t)va_arg(args, int);
            break;
        case I32:
            dt.Values.I32 = va_arg(args, int32_t);
            break;
        case I64:
            dt.Values.I64 = va_arg(args, int64_t);
            break;
        case U8:
            dt.Values.U8 = (uint8_t)va_arg(args, unsigned int);
            break;
        case U16:
            dt.Values.U16 = (uint16_t)va_arg(args, unsigned int);
            break;
        case U32:
            dt.Values.U32 = va_arg(args, uint32_t);
            break;
        case U64:
            dt.Values.U64 = va_arg(args, uint64_t);
            break;
        case F32:
            dt.Values.F32 = (float)va_arg(args, double);
            break;
        case F64:
            dt.Values.F64 = va_arg(args, double);
            break;
        case CHAR:
            dt.Values.CHAR = (char)va_arg(args, int);
            break;
        case STRING:
            dt.Values.STRING = va_arg(args, char*);
            break;
        case BOOL:
            dt.Values.BOOL = va_arg(args, int); // Note: bool is promoted to int in varargs
            break;
        case Pointer:
            dt.Values.Pointer = va_arg(args, void*);
            break;
        default:
            break;
    }
    
    va_end(args);
    return dt;
}

Node* createNode(DataType value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        perror("Memory allocation failed for new node");
        return NULL; // Return NULL instead of void
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** headRef, DataType value) {
    // call to create a new node
    Node* newNode = createNode(value);
    if(newNode == NULL) return; // Handle memory allocation failure

    // if node is headRef is null it means node is head, so treat as head
    if(*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    // else make node current
    Node* current = *headRef;

    // and iterate over each node
    while(current->next != NULL) {
        // every time set next node to current node to perform next iteration
        current = current->next;
    }
    // now if found the last node
    // append new node to last node
    current->next = newNode;
}

char* printData(DataType val) {
    char* ret_str = malloc(128);

    if(ret_str == NULL) {
        return NULL;
    }

    switch (val.type) // Fixed: use val.type instead of data.type
    {
        case I8:
            snprintf(ret_str, 128, "%d", val.Values.I8);
            break;
        case I16:
            snprintf(ret_str, 128, "%d", val.Values.I16);
            break;
        case I32:
            snprintf(ret_str, 128, "%d", val.Values.I32);
            break;
        case I64:
            snprintf(ret_str, 128, "%lld", (long long)val.Values.I64);
            break;
        case I128:
            // Note: I128 printing is complex, using a simplified approach
            snprintf(ret_str, 128, "%lld", (long long)val.Values.I128);
            break;
        case U8:
            snprintf(ret_str, 128, "%u", val.Values.U8);
            break;
        case U16:
            snprintf(ret_str, 128, "%u", val.Values.U16);
            break;
        case U32:
            snprintf(ret_str, 128, "%u", val.Values.U32);
            break;
        case U64:
            snprintf(ret_str, 128, "%llu", (unsigned long long)val.Values.U64);
            break;
        case U128:
            snprintf(ret_str, 128, "%llu", (unsigned long long)val.Values.U128);
            break; // Added missing break
        case F32:
            snprintf(ret_str, 128, "%.6f", val.Values.F32);
            break;
        case F64:
            snprintf(ret_str, 128, "%.12lf", val.Values.F64);
            break;
        case CHAR:
            snprintf(ret_str, 128, "%c", val.Values.CHAR);
            break;
        case STRING:
            snprintf(ret_str, 128, "%s", val.Values.STRING ? val.Values.STRING : "(null)");
            break;
        case BOOL:
            snprintf(ret_str, 128, "%s", val.Values.BOOL ? "true" : "false");
            break;
        case Pointer:
            snprintf(ret_str, 128, "%p", val.Values.Pointer);
            break;
        default:
            snprintf(ret_str, 128, "(unknown type)");
            break;
    }
    return ret_str;
}

void printNode(Node* head) {
    Node* current = head;
    if(current == NULL) {
        printf("NULL\n");
        return;
    }
    
    while(current != NULL) { // Fixed: check current != NULL instead of current->next
        char* dataStr = printData(current->data);
        if(dataStr) {
            printf("[%s]", dataStr);
            free(dataStr); // Free the allocated string
        }
        
        current = current->next;
        if(current != NULL) {
            printf("->");
        }
    }
    printf("->NULL\n");
}

void free_linkedlist(Node* head) {
    Node* temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        // If the node contains a STRING that was dynamically allocated,
        // you might need to free it here as well
        free(temp);
    }
}

int main() {
    // Dynamic Linked List
    Node *head = NULL;

    // Example usage with different data types
    appendNode(&head, createDataType(I32, 42));
    appendNode(&head, createDataType(F32, 3.14f));
    appendNode(&head, createDataType(CHAR, 'A'));
    appendNode(&head, createDataType(STRING, "Hello World"));
    appendNode(&head, createDataType(BOOL, true));
    appendNode(&head, createDataType(BOOL, false));

    printf("Linked List contents: ");
    printNode(head);
    
    free_linkedlist(head);
    return 0;
}