#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void freeList(Node **head, free_data_func_t freeData)
{
    Node *current = *head;
    Node *nextNode;

    while (current != NULL)
    {
        nextNode = current->next; // Store the next node

        // Free the data using custom function if provided
        if (freeData)
        {
            freeData(current->data);
        }
        else
        {
            free(current->data); // Default free for simple data types
        }

        free(current);      // Free the current node
        current = nextNode; // Move to the next node
    }

    *head = NULL; // Set head to NULL after freeing all nodes
    printf("List has been freed successfully.\n");
};
