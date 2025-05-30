#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
void insertAtTail(Node **head, int data)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    if (!temp)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->next = NULL;

    // If list is empty, make temp the head
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    Node *current = *head;

    while (current->next != NULL) // Go until we find the last node
    {
        current = current->next;
    }
    current->next = temp;
};
