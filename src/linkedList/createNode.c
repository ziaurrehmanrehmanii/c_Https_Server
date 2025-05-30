#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

Node *createNode(int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->next = NULL;
    return temp;
}
