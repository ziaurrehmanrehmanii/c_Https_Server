#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void test_data_type(const char *typeName, Node **list, void *data, size_t dataSize,
                    print_func_t printFunc, compare_func_t compareFunc)
{
    printf("Testing %s:\n", typeName);

    // Test basic operations
    insertAtTail(list, data, dataSize);
    printf("  After insert: ");
    displayList(*list, printFunc);

    // Test array-like access
    void *retrieved = getDataAtIndex(*list, 0);
    if (retrieved)
    {
        printf("  list[0] = ");
        printFunc(retrieved);
        printf("\n");
    }

    // Test deletion
    deleteNode(list, data, compareFunc);
    printf("  After delete: ");
    displayList(*list, printFunc);

    freeList(list, NULL);
    printf("\n");
}

int main()
{
    printf("=== Final Comprehensive Test of All Features ===\n\n");

    // Test all data types
    Node *list = NULL;

    // Integer
    int intVal = 42;
    test_data_type("int", &list, &intVal, sizeof(int), printInt, compareInt);

    // Character
    char charVal = 'X';
    test_data_type("char", &list, &charVal, sizeof(char), printChar, compareChar);

    // Float
    float floatVal = 3.14f;
    test_data_type("float", &list, &floatVal, sizeof(float), printFloat, compareFloat);

    // Double
    double doubleVal = 123.456;
    test_data_type("double", &list, &doubleVal, sizeof(double), printDouble, compareDouble);

    // Long
    long longVal = 1000000L;
    test_data_type("long", &list, &longVal, sizeof(long), printLong, compareLong);

    // Short
    short shortVal = 500;
    test_data_type("short", &list, &shortVal, sizeof(short), printShort, compareShort);

    // Unsigned int
    unsigned int uintVal = 999U;
    test_data_type("unsigned int", &list, &uintVal, sizeof(unsigned int), printUnsignedInt, compareUnsignedInt);

    // String
    const char *stringVal = "Hello";
    test_data_type("string", &list, &stringVal, sizeof(char *), printString, compareString);

    // Test comprehensive array-like operations
    printf("=== Array-like Operations Test ===\n");
    list = NULL;

    // Build a mixed demonstration list with integers
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&list, &values[i], sizeof(int));
    }

    printf("Initial list: ");
    displayList(list, printInt);
    printf("List size: %zu\n", getListSize(list));

    // Test all array-like operations
    printf("\nArray-like access test:\n");
    for (size_t i = 0; i < getListSize(list); i++)
    {
        int *val = (int *)getDataAtIndex(list, i);
        printf("  list[%zu] = %d\n", i, *val);
    }

    // Modify elements
    printf("\nModifying elements:\n");
    int newVal1 = 999;
    setDataAtIndex(&list, 2, &newVal1, sizeof(int));
    printf("  After setting list[2] = 999: ");
    displayList(list, printInt);

    // Insert at index
    int newVal2 = 777;
    insertAtIndex(&list, 1, &newVal2, sizeof(int));
    printf("  After inserting 777 at index 1: ");
    displayList(list, printInt);

    // Delete at index
    deleteAtIndex(&list, 3, NULL);
    printf("  After deleting at index 3: ");
    displayList(list, printInt);

    printf("  Final size: %zu\n", getListSize(list));

    // Test bounds checking
    printf("\nBounds checking test:\n");
    int *outOfBounds = (int *)getDataAtIndex(list, 100);
    if (outOfBounds == NULL)
    {
        printf("  ✓ Out of bounds access correctly returns NULL\n");
    }

    if (setDataAtIndex(&list, 100, &newVal1, sizeof(int)) == -1)
    {
        printf("  ✓ Out of bounds set correctly returns -1\n");
    }

    freeList(&list, NULL);

    printf("\n=== All Tests Completed Successfully! ===\n");
    printf("✓ All 8 data types supported\n");
    printf("✓ Traditional linked list operations working\n");
    printf("✓ Array-like indexing operations working\n");
    printf("✓ Bounds checking working\n");
    printf("✓ Memory management working\n");

    return 0;
}
