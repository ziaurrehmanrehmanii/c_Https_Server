#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void insertAtIndex(Node **head, size_t index, const void *data, size_t dataSize)
{
    // If index is 0, insert at head
    if (index == 0)
    {
        insertAtHead(head, data, dataSize);
        return;
    }

    // Get the size of the list
    size_t listSize = getListSize(*head);

    // If index is greater than or equal to list size, insert at tail
    if (index >= listSize)
    {
        insertAtTail(head, data, dataSize);
        return;
    }

    // Find the node at position (index - 1)
    Node *prevNode = getNodeAtIndex(*head, index - 1);

    if (prevNode == NULL)
    {
        printf("Invalid index %zu\n", index);
        return;
    }

    // Create new node
    Node *newNode = createNode(data, dataSize);

    // Insert the new node
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}
