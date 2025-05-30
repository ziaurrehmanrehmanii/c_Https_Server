/*
 * Array-like Linked List Usage Example
 *
 * This demonstrates how to use the linked list with array-like indexing.
 */

#include "linkedList.h"
#include <stdio.h>

void demonstrate_array_like_usage()
{
    Node *list = NULL;

    // 1. Create a list like an array
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&list, &values[i], sizeof(int));
    }

    // 2. Access elements by index (like array[i])
    printf("Reading elements:\n");
    for (size_t i = 0; i < getListSize(list); i++)
    {
        int *value = (int *)getDataAtIndex(list, i);
        if (value)
        {
            printf("list[%zu] = %d\n", i, *value);
        }
    }

    // 3. Modify elements by index (like array[i] = newValue)
    int newValue = 999;
    setDataAtIndex(&list, 2, &newValue, sizeof(int));
    printf("After setting list[2] = 999:\n");
    displayList(list, printInt);

    // 4. Insert at specific index
    int insertValue = 777;
    insertAtIndex(&list, 1, &insertValue, sizeof(int));
    printf("After inserting 777 at index 1:\n");
    displayList(list, printInt);

    // 5. Delete at specific index
    deleteAtIndex(&list, 3, NULL);
    printf("After deleting element at index 3:\n");
    displayList(list, printInt);

    // 6. Get list size (like array.length)
    printf("List size: %zu\n", getListSize(list));

    // Clean up
    freeList(&list, NULL);
}
