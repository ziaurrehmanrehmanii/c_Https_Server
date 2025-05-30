#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void deleteNode(Node **head, const void *key, compare_func_t compare)
{
    // Handle empty list
    if (*head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    // Special case: deleting the head node
    if (compare((*head)->data, key) == 0)
    {
        Node *temp = *head;
        *head = (*head)->next; // Move head to next node
        free(temp->data);      // Free the data
        free(temp);            // Free the node
        return;
    }

    // Find the node before the target node
    Node *prev = *head;
    while (prev->next != NULL && compare(prev->next->data, key) != 0)
    {
        prev = prev->next;
    }

    // If key not found
    if (prev->next == NULL)
    {
        printf("Key not found in the list\n");
        return;
    }

    // Node to delete is prev->next
    Node *nodeToDelete = prev->next;
    prev->next = nodeToDelete->next; // Link prev to the node after target
    free(nodeToDelete->data);        // Free the data
    free(nodeToDelete);              // Free the target node
}
