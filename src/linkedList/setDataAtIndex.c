#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int setDataAtIndex(Node **head, size_t index, const void *data, size_t dataSize)
{
    Node *node = getNodeAtIndex(*head, index);

    if (node == NULL)
    {
        printf("Index %zu is out of bounds\n", index);
        return -1; // Return -1 to indicate failure
    }

    // Free the old data
    free(node->data);

    // Allocate new memory for the new data
    node->data = malloc(dataSize);
    if (!node->data)
    {
        fprintf(stderr, "Memory allocation failed for data\n");
        return -1;
    }

    // Copy the new data
    memcpy(node->data, data, dataSize);
    node->dataSize = dataSize;

    return 0; // Return 0 to indicate success
}
