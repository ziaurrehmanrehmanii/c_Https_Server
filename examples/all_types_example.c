#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("=== Comprehensive Data Types Example ===\n\n");

    // 1. Integer List
    printf("1. Integer List:\n");
    Node *intList = NULL;
    int nums[] = {42, 15, 8, 99, 3};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&intList, &nums[i], sizeof(int));
    }

    printf("   List: ");
    displayList(intList, printInt);

    int searchInt = 15;
    printf("   Deleting %d...\n", searchInt);
    deleteNode(&intList, &searchInt, compareInt);
    printf("   After deletion: ");
    displayList(intList, printInt);

    freeList(&intList, NULL);
    printf("\n");

    // 2. Character List
    printf("2. Character List:\n");
    Node *charList = NULL;
    char chars[] = {'A', 'Z', 'M', 'B', 'X'};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&charList, &chars[i], sizeof(char));
    }

    printf("   List: ");
    displayList(charList, printChar);

    char searchChar = 'M';
    printf("\n   Deleting '%c'...\n", searchChar);
    deleteNode(&charList, &searchChar, compareChar);
    printf("   After deletion: ");
    displayList(charList, printChar);

    freeList(&charList, NULL);
    printf("\n\n");

    // 3. Float List
    printf("3. Float List:\n");
    Node *floatList = NULL;
    float floats[] = {3.14f, 2.71f, 1.41f, 9.99f, 0.5f};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&floatList, &floats[i], sizeof(float));
    }

    printf("   List: ");
    displayList(floatList, printFloat);

    float searchFloat = 2.71f;
    printf("\n   Deleting %.2f...\n", searchFloat);
    deleteNode(&floatList, &searchFloat, compareFloat);
    printf("   After deletion: ");
    displayList(floatList, printFloat);

    freeList(&floatList, NULL);
    printf("\n\n");

    // 4. Double List
    printf("4. Double List:\n");
    Node *doubleList = NULL;
    double doubles[] = {123.456, 789.012, 345.678, 901.234, 567.890};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&doubleList, &doubles[i], sizeof(double));
    }

    printf("   List: ");
    displayList(doubleList, printDouble);

    double searchDouble = 345.678;
    printf("\n   Deleting %.2lf...\n", searchDouble);
    deleteNode(&doubleList, &searchDouble, compareDouble);
    printf("   After deletion: ");
    displayList(doubleList, printDouble);

    freeList(&doubleList, NULL);
    printf("\n\n");

    // 5. Long List
    printf("5. Long List:\n");
    Node *longList = NULL;
    long longs[] = {1000000L, 2000000L, 3000000L, 4000000L, 5000000L};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&longList, &longs[i], sizeof(long));
    }

    printf("   List: ");
    displayList(longList, printLong);

    long searchLong = 3000000L;
    printf("\n   Deleting %ld...\n", searchLong);
    deleteNode(&longList, &searchLong, compareLong);
    printf("   After deletion: ");
    displayList(longList, printLong);

    freeList(&longList, NULL);
    printf("\n\n");

    // 6. Short List
    printf("6. Short List:\n");
    Node *shortList = NULL;
    short shorts[] = {100, 200, 300, 400, 500};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&shortList, &shorts[i], sizeof(short));
    }

    printf("   List: ");
    displayList(shortList, printShort);

    short searchShort = 300;
    printf("\n   Deleting %hd...\n", searchShort);
    deleteNode(&shortList, &searchShort, compareShort);
    printf("   After deletion: ");
    displayList(shortList, printShort);

    freeList(&shortList, NULL);
    printf("\n\n");

    // 7. Unsigned Integer List
    printf("7. Unsigned Integer List:\n");
    Node *uintList = NULL;
    unsigned int uints[] = {100U, 200U, 300U, 400U, 500U};

    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&uintList, &uints[i], sizeof(unsigned int));
    }

    printf("   List: ");
    displayList(uintList, printUnsignedInt);

    unsigned int searchUint = 300U;
    printf("\n   Deleting %u...\n", searchUint);
    deleteNode(&uintList, &searchUint, compareUnsignedInt);
    printf("   After deletion: ");
    displayList(uintList, printUnsignedInt);

    freeList(&uintList, NULL);
    printf("\n\n");

    // 8. Array-like operations with different data types
    printf("8. Array-like operations with different data types:\n");

    // Float array-like operations
    Node *mixedFloats = NULL;
    float moreFloats[] = {1.1f, 2.2f, 3.3f, 4.4f};

    for (int i = 0; i < 4; i++)
    {
        insertAtTail(&mixedFloats, &moreFloats[i], sizeof(float));
    }

    printf("   Float list: ");
    displayList(mixedFloats, printFloat);

    // Access by index
    float *valueAtIndex = (float *)getDataAtIndex(mixedFloats, 2);
    printf("\n   floatList[2] = %.2f\n", *valueAtIndex);

    // Modify by index
    float newFloatValue = 9.99f;
    setDataAtIndex(&mixedFloats, 2, &newFloatValue, sizeof(float));
    printf("   After setting floatList[2] = 9.99: ");
    displayList(mixedFloats, printFloat);

    freeList(&mixedFloats, NULL);
    printf("\n\n");

    printf("=== All data type helpers are working correctly! ===\n");

    return 0;
}
