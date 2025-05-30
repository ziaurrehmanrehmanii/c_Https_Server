#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *createNode(const void *data, size_t dataSize)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the data
    temp->data = malloc(dataSize);
    if (!temp->data)
    {
        free(temp);
        fprintf(stderr, "Memory allocation failed for data\n");
        exit(EXIT_FAILURE);
    }

    // Copy the data
    memcpy(temp->data, data, dataSize);
    temp->dataSize = dataSize;
    temp->next = NULL;
    return temp;
}
