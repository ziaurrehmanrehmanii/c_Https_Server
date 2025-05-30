#include "linkedList.h"
#include <stdio.h>
#include <stddef.h>

Node *getNodeAtIndex(Node *head, size_t index)
{
    Node *current = head;
    size_t currentIndex = 0;

    while (current != NULL && currentIndex < index)
    {
        current = current->next;
        currentIndex++;
    }

    // Return NULL if index is out of bounds
    return current;
}
