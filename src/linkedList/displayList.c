#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void displayList(Node *head, print_func_t print)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    Node *current = head;
    while (current != NULL)
    {
        print(current->data);
        if (current->next != NULL)
        {
            printf(" -> ");
        }
        current = current->next; // Move to next node
    }
    printf(" -> NULL\n");
}
