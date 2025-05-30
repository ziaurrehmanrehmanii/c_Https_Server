#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stddef.h>

// Function pointer types for generic operations
typedef int (*compare_func_t)(const void *a, const void *b);
typedef void (*print_func_t)(const void *data);
typedef void (*free_data_func_t)(void *data);

typedef struct Node
{
    void *data;
    size_t dataSize;
    struct Node *next;
} Node;

Node *createNode(const void *data, size_t dataSize);
void insertAtHead(Node **head, const void *data, size_t dataSize);
void insertAtTail(Node **head, const void *data, size_t dataSize);
void deleteNode(Node **head, const void *key, compare_func_t compare);
void displayList(Node *head, print_func_t print);
void freeList(Node **head, free_data_func_t freeData);

// Helper functions for common data types
int compareInt(const void *a, const void *b);
int compareString(const void *a, const void *b);
void printInt(const void *data);
void printString(const void *data);

#endif
