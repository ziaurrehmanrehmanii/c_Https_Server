#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void deleteAtIndex(Node **head, size_t index, free_data_func_t freeData)
{
    // Handle empty list
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    // Special case: deleting the head node (index 0)
    if (index == 0)
    {
        Node *temp = *head;
        *head = (*head)->next; // Move head to next node

        // Free the data using custom function if provided
        if (freeData)
        {
            freeData(temp->data);
        }
        else
        {
            free(temp->data); // Default free for simple data types
        }
        free(temp); // Free the node
        return;
    }

    // Find the node at position (index - 1)
    Node *prevNode = getNodeAtIndex(*head, index - 1);

    if (prevNode == NULL || prevNode->next == NULL)
    {
        printf("Index %zu is out of bounds\n", index);
        return;
    }

    // Node to delete is prevNode->next
    Node *nodeToDelete = prevNode->next;

    // Update the link
    prevNode->next = nodeToDelete->next;

    // Free the data using custom function if provided
    if (freeData)
    {
        freeData(nodeToDelete->data);
    }
    else
    {
        free(nodeToDelete->data); // Default free for simple data types
    }
    free(nodeToDelete); // Free the node
}
