#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Array-like Linked List Example ===\n\n");

    // Create an integer linked list
    Node *list = NULL;
    int nums[] = {10, 20, 30, 40, 50};

    // Insert elements (like array initialization)
    printf("1. Building list with values: ");
    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&list, &nums[i], sizeof(int));
        printf("%d ", nums[i]);
    }
    printf("\n");

    // Display the list
    printf("   Current list: ");
    displayList(list, printInt);
    printf("   List size: %zu\n\n", getListSize(list));

    // Array-like access: read elements by index
    printf("2. Array-like access (reading by index):\n");
    for (size_t i = 0; i < getListSize(list); i++)
    {
        int *value = (int *)getDataAtIndex(list, i);
        if (value != NULL)
        {
            printf("   list[%zu] = %d\n", i, *value);
        }
    }
    printf("\n");

    // Array-like modification: set elements by index
    printf("3. Array-like modification (setting by index):\n");
    int newValue1 = 100;
    int newValue2 = 200;

    printf("   Setting list[1] = %d\n", newValue1);
    setDataAtIndex(&list, 1, &newValue1, sizeof(int));

    printf("   Setting list[3] = %d\n", newValue2);
    setDataAtIndex(&list, 3, &newValue2, sizeof(int));

    printf("   Updated list: ");
    displayList(list, printInt);
    printf("\n");

    // Insert at specific index
    printf("4. Insert at specific index:\n");
    int insertValue = 999;
    printf("   Inserting %d at index 2\n", insertValue);
    insertAtIndex(&list, 2, &insertValue, sizeof(int));

    printf("   List after insertion: ");
    displayList(list, printInt);
    printf("   New list size: %zu\n\n", getListSize(list));

    // Delete at specific index
    printf("5. Delete at specific index:\n");
    printf("   Deleting element at index 4\n");
    deleteAtIndex(&list, 4, NULL);

    printf("   List after deletion: ");
    displayList(list, printInt);
    printf("   New list size: %zu\n\n", getListSize(list));

    // Demonstrate bounds checking
    printf("6. Bounds checking:\n");
    printf("   Trying to access index 10 (out of bounds):\n");
    int *outOfBounds = (int *)getDataAtIndex(list, 10);
    if (outOfBounds == NULL)
    {
        printf("   Access failed as expected\n");
    }

    printf("   Trying to set index 10 (out of bounds):\n");
    int dummyValue = 777;
    if (setDataAtIndex(&list, 10, &dummyValue, sizeof(int)) == -1)
    {
        printf("   Set operation failed as expected\n");
    }
    printf("\n");

    // Final list state
    printf("7. Final list state:\n");
    printf("   Final list: ");
    displayList(list, printInt);
    printf("   Final size: %zu\n\n", getListSize(list));

    // Clean up
    freeList(&list, NULL);

    return 0;
}
