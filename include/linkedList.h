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

// Array-like access functions
Node *getNodeAtIndex(Node *head, size_t index);
void *getDataAtIndex(Node *head, size_t index);
int setDataAtIndex(Node **head, size_t index, const void *data, size_t dataSize);
void insertAtIndex(Node **head, size_t index, const void *data, size_t dataSize);
void deleteAtIndex(Node **head, size_t index, free_data_func_t freeData);
size_t getListSize(Node *head);

// Helper functions for common data types
// Compare functions
int compareInt(const void *a, const void *b);
int compareChar(const void *a, const void *b);
int compareFloat(const void *a, const void *b);
int compareDouble(const void *a, const void *b);
int compareLong(const void *a, const void *b);
int compareShort(const void *a, const void *b);
int compareUnsignedInt(const void *a, const void *b);
int compareString(const void *a, const void *b);

// Print functions
void printInt(const void *data);
void printChar(const void *data);
void printFloat(const void *data);
void printDouble(const void *data);
void printLong(const void *data);
void printShort(const void *data);
void printUnsignedInt(const void *data);
void printString(const void *data);

#endif
