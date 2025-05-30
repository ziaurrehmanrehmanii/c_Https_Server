#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

int main()
{
    Node *priceList = NULL;
    Node *nameList = NULL;
    int numItems;
    int price;
    int total = 0;

    printf("=== RECEIPT GENERATOR ===\n");
    printf("Enter the number of items: ");
    scanf("%d", &numItems);

    if (numItems <= 0)
    {
        printf("Invalid number of items!\n");
        return 1;
    }

    printf("\nEnter item details:\n");
    for (int i = 0; i < numItems; i++)
    {
        char itemName[100];
        printf("Item %d name: ", i + 1);
        scanf(" %99[^\n]", itemName);

        printf("Item %d price: $", i + 1);
        scanf("%d", &price);

        if (price < 0)
        {
            printf("Invalid price! Please enter a positive value.\n");
            i--; // Retry this item
            continue;
        }

        // Insert name and price into their respective linked lists
        char *namePtr = malloc((strlen(itemName) + 1) * sizeof(char));
        if (namePtr == NULL)
        {
            printf("Memory allocation failed!\n");
            freeList(&priceList, NULL);
            freeList(&nameList, free);
            return 1;
        }
        strcpy(namePtr, itemName);

        insertAtTail(&nameList, &namePtr, sizeof(char *));
        insertAtTail(&priceList, &price, sizeof(int));
    }

    printf("\n=== RECEIPT ===\n");
    printf("Item\t\t\tPrice\n");
    printf("----\t\t\t-----\n");

    Node *currentPrice = priceList;
    Node *currentName = nameList;
    while (currentPrice != NULL && currentName != NULL)
    {
        char *itemName = *(char **)currentName->data;
        printf("%-20s\t$", itemName);
        printInt(currentPrice->data);
        printf("\n");
        total += *(int *)currentPrice->data;
        currentPrice = currentPrice->next;
        currentName = currentName->next;
    }

    printf("----\t\t\t-----\n");
    printf("Total:\t\t\t$%d\n", total);
    printf("\nThank you for your purchase!\n");

    // Clean up memory
    freeList(&priceList, NULL);
    freeList(&nameList, free);

    return 0;
}
