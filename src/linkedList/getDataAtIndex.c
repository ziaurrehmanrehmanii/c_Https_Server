#include "linkedList.h"
#include <stdio.h>
#include <stddef.h>

void *getDataAtIndex(Node *head, size_t index)
{
    Node *node = getNodeAtIndex(head, index);

    if (node == NULL)
    {
        printf("Index %zu is out of bounds\n", index);
        return NULL;
    }

    return node->data;
}
