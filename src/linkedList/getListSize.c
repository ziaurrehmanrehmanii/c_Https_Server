#include "linkedList.h"
#include <stddef.h>

size_t getListSize(Node *head)
{
    size_t count = 0;
    Node *current = head;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    return count;
}
