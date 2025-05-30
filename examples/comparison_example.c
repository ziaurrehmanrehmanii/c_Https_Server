#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void demonstrate_traditional_vs_array_like()
{
    printf("=== Traditional vs Array-like Operations Comparison ===\n\n");

    Node *list = NULL;

    // Traditional way - efficient for head/tail operations
    printf("1. Traditional linked list operations (efficient):\n");

    int values[] = {10, 20, 30, 40, 50};

    // Traditional: Insert at head (O(1))
    printf("   Inserting at head (O(1)): ");
    for (int i = 0; i < 5; i++)
    {
        insertAtHead(&list, &values[i], sizeof(int));
        printf("%d ", values[i]);
    }
    printf("\n   Result: ");
    displayList(list, printInt);

    // Clear list for next demonstration
    freeList(&list, NULL);
    list = NULL;

    // Build list for array-like demo
    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&list, &values[i], sizeof(int));
    }

    printf("\n2. Array-like operations (convenient but slower for random access):\n");
    printf("   Original list: ");
    displayList(list, printInt);

    // Array-like: Access by index (O(n))
    printf("   Accessing elements by index:\n");
    for (size_t i = 0; i < getListSize(list); i++)
    {
        int *value = (int *)getDataAtIndex(list, i);
        if (value)
        {
            printf("     list[%zu] = %d\n", i, *value);
        }
    }

    // Array-like: Modify by index (O(n))
    printf("   Modifying list[2] to 999:\n");
    int newValue = 999;
    setDataAtIndex(&list, 2, &newValue, sizeof(int));
    printf("     Updated list: ");
    displayList(list, printInt);

    // Array-like: Insert at specific index (O(n))
    printf("   Inserting 777 at index 1:\n");
    int insertValue = 777;
    insertAtIndex(&list, 1, &insertValue, sizeof(int));
    printf("     Updated list: ");
    displayList(list, printInt);

    // Array-like: Delete at specific index (O(n))
    printf("   Deleting element at index 3:\n");
    deleteAtIndex(&list, 3, NULL);
    printf("     Updated list: ");
    displayList(list, printInt);

    printf("\n3. When to use each approach:\n");
    printf("   - Use traditional operations (insertAtHead/Tail) for best performance\n");
    printf("   - Use array-like operations when you need familiar array syntax\n");
    printf("   - Consider arrays/vectors for frequent random access patterns\n");

    freeList(&list, NULL);
}

int main()
{
    demonstrate_traditional_vs_array_like();
    return 0;
}
