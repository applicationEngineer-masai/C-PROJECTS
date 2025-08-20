
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>


#define console(...) printf(__VA_ARGS__)
#define input(...) scanf(__VA_ARGS__)
#define NULL ((void *)0)

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL) {
        perror("Memory allocation failed for new node...!");
        return NULL;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void append_node(Node** headRef, int value) {
    Node* newNode = create_node(value);
    if(*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    Node* current = *headRef;
    while (current->next != NULL)
    {
        current=current->next;
    }
    current->next = newNode;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL)
    {
        console("[%i]->", current->data);
        current=current->next;
    }
    console("NULL\n");
}

void free_linkedlist(Node* head) {
    Node* temp;
    while(head != NULL) {
        temp = head;
        head=head->next;
        free(temp);
    }
}

int main() {
    
    Node *head = NULL;

    append_node(&head, 10);
    append_node(&head, 20);
    append_node(&head, 30);
    append_node(&head, 40);

    printList(head);
    free_linkedlist(head);

    console("%i\n", head->next->next->data);

    return 0;
}