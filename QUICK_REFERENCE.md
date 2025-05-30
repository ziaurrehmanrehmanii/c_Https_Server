# Linked List Quick Reference Card

## Basic Operations
```c
Node *list = NULL;                              // Initialize
insertAtTail(&list, &data, sizeof(TYPE));      // Add to end
insertAtHead(&list, &data, sizeof(TYPE));      // Add to beginning
displayList(list, printTYPE);                  // Display all
deleteNode(&list, &key, compareTYPE);          // Delete by value
freeList(&list, NULL);                         // Clean up
```

## Array-like Operations
```c
size_t size = getListSize(list);               // Get size
TYPE *val = (TYPE*)getDataAtIndex(list, i);   // Get list[i]
setDataAtIndex(&list, i, &data, sizeof(TYPE)); // Set list[i] = data
insertAtIndex(&list, i, &data, sizeof(TYPE));  // Insert at index i
deleteAtIndex(&list, i, NULL);                // Delete at index i
```

## Helper Functions by Data Type

| Type | Compare Function | Print Function |
|------|------------------|----------------|
| `int` | `compareInt` | `printInt` |
| `char` | `compareChar` | `printChar` |
| `float` | `compareFloat` | `printFloat` |
| `double` | `compareDouble` | `printDouble` |
| `long` | `compareLong` | `printLong` |
| `short` | `compareShort` | `printShort` |
| `unsigned int` | `compareUnsignedInt` | `printUnsignedInt` |
| `char*` | `compareString` | `printString` |

## Quick Examples

### Integer List
```c
Node *list = NULL;
int value = 42;
insertAtTail(&list, &value, sizeof(int));
displayList(list, printInt);
freeList(&list, NULL);
```

### Float List with Array Access
```c
Node *list = NULL;
float nums[] = {1.1f, 2.2f, 3.3f};

for (int i = 0; i < 3; i++) {
    insertAtTail(&list, &nums[i], sizeof(float));
}

float *val = (float*)getDataAtIndex(list, 1);  // Get nums[1]
printf("Value: %.2f\n", *val);

freeList(&list, NULL);
```

### Character List
```c
Node *list = NULL;
char letters[] = {'A', 'B', 'C'};

for (int i = 0; i < 3; i++) {
    insertAtTail(&list, &letters[i], sizeof(char));
}

displayList(list, printChar);
freeList(&list, NULL);
```

## Tips
- Always use `sizeof(TYPE)` for data size
- Choose the correct compare/print function for your data type
- Use `freeList(&list, NULL)` for simple types
- For custom types, create custom compare/print functions
- Array-like operations are O(n), traditional head/tail operations are O(1)
