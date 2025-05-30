#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data);
void insertAtHead(Node **head, int data);
void insertAtTail(Node **head, int data);
void deleteNode(Node **head, int key);
void displayList(Node *head);
void freeList(Node **head);

#endif
