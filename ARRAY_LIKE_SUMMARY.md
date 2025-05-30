# Array-like Linked List Implementation - Summary

## What We've Added

Your linked list now behaves more like an array with the following new capabilities:

### New Functions Added:

1. **`getListSize(Node *head)`** - Get the number of elements (like `array.length`)
2. **`getDataAtIndex(Node *head, size_t index)`** - Access element at index (like `array[i]`)
3. **`setDataAtIndex(Node **head, size_t index, const void *data, size_t dataSize)`** - Modify element at index (like `array[i] = value`)
4. **`insertAtIndex(Node **head, size_t index, const void *data, size_t dataSize)`** - Insert at specific index
5. **`deleteAtIndex(Node **head, size_t index, free_data_func_t freeData)`** - Delete at specific index
6. **`getNodeAtIndex(Node *head, size_t index)`** - Internal helper to get node at index

### Usage Examples:

```c
Node *list = NULL;
int nums[] = {10, 20, 30, 40, 50};

// Build the list
for (int i = 0; i < 5; i++) {
    insertAtTail(&list, &nums[i], sizeof(int));
}

// Array-like access
int *value = (int *)getDataAtIndex(list, 2);  // Get list[2]
printf("list[2] = %d\n", *value);             // Output: 30

// Array-like modification
int newValue = 999;
setDataAtIndex(&list, 2, &newValue, sizeof(int));  // list[2] = 999

// Insert at specific position
insertAtIndex(&list, 1, &newValue, sizeof(int));   // Insert at index 1

// Delete at specific position
deleteAtIndex(&list, 3, NULL);                     // Delete element at index 3

// Get size
size_t size = getListSize(list);                   // Get list size
```

## Files Created/Modified:

### New Implementation Files:
- `src/linkedList/getListSize.c`
- `src/linkedList/getNodeAtIndex.c`
- `src/linkedList/getDataAtIndex.c`
- `src/linkedList/setDataAtIndex.c`
- `src/linkedList/insertAtIndex.c`
- `src/linkedList/deleteAtIndex.c`

### Updated Files:
- `include/linkedList.h` - Added function declarations
- `examples/README.md` - Updated documentation
- `examples/array_like_example.c` - Complete demonstration
- `examples/comparison_example.c` - Traditional vs array-like comparison

## Key Features:

### ✅ Array-like Syntax
- Access: `getDataAtIndex(list, i)` behaves like `array[i]`
- Modify: `setDataAtIndex(list, i, data, size)` behaves like `array[i] = value`
- Size: `getListSize(list)` behaves like `array.length`

### ✅ Bounds Checking
- All functions check for valid indices
- Return NULL or -1 for out-of-bounds access
- Print error messages for debugging

### ✅ Memory Safety
- Proper memory allocation/deallocation
- No memory leaks when replacing data
- Compatible with existing free functions

### ✅ Generic Support
- Works with any data type (int, string, custom structs)
- Uses same `void *` and `size_t` approach as original

## Performance Considerations:

- **Traditional operations** (`insertAtHead`/`insertAtTail`): O(1)
- **Array-like operations**: O(n) due to traversal to index
- **Best for**: Cases where you need familiar array syntax occasionally
- **Not ideal for**: Frequent random access (use actual arrays instead)

## Backward Compatibility:

- All original functions still work exactly the same
- No breaking changes to existing code
- New functionality is purely additive

Your linked list now gives you the best of both worlds - the flexibility of linked lists with the familiar syntax of arrays!
