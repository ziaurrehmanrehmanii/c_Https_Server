# Generic Linked List Implementation

This directory contains a generic linked list implementation in C that can handle any data type.

## Features

- **Generic**: Can store any data type using `void*` pointers
- **Type-safe**: Uses function pointers for comparison and printing operations
- **Memory-safe**: Proper memory allocation and deallocation
- **Flexible**: Support for custom data types with custom comparison and print functions
- **Array-like Access**: Index-based access and modification (NEW!)
- **Array-like Operations**: Insert/delete at specific indices, get list size

## API Reference

### Core Functions

```c
Node *createNode(const void *data, size_t dataSize);
void insertAtHead(Node **head, const void *data, size_t dataSize);
void insertAtTail(Node **head, const void *data, size_t dataSize);
void deleteNode(Node **head, const void *key, compare_func_t compare);
void displayList(Node *head, print_func_t print);
void freeList(Node **head, free_data_func_t freeData);
```

### Array-like Access Functions (NEW!)

```c
Node *getNodeAtIndex(Node *head, size_t index);
void *getDataAtIndex(Node *head, size_t index);
int setDataAtIndex(Node **head, size_t index, const void *data, size_t dataSize);
void insertAtIndex(Node **head, size_t index, const void *data, size_t dataSize);
void deleteAtIndex(Node **head, size_t index, free_data_func_t freeData);
size_t getListSize(Node *head);
```

### Helper Functions (for common data types)

```c
// Compare functions
int compareInt(const void *a, const void *b);
int compareChar(const void *a, const void *b);
int compareFloat(const void *a, const void *b);
int compareDouble(const void *a, const void *b);
int compareLong(const void *a, const void *b);
int compareShort(const void *a, const void *b);
int compareUnsignedInt(const void *a, const void *b);
int compareString(const void *a, const void *b);

// Print functions
void printInt(const void *data);
void printChar(const void *data);
void printFloat(const void *data);
void printDouble(const void *data);
void printLong(const void *data);
void printShort(const void *data);
void printUnsignedInt(const void *data);
void printString(const void *data);
```

## Array-like Usage

The linked list now supports array-like indexing and operations. Here's how to use it:

### Basic Array-like Access

```c
Node *list = NULL;
int values[] = {10, 20, 30, 40, 50};

// Build the list
for (int i = 0; i < 5; i++) {
    insertAtTail(&list, &values[i], sizeof(int));
}

// Access elements by index (like array[i])
for (size_t i = 0; i < getListSize(list); i++) {
    int *value = (int *)getDataAtIndex(list, i);
    printf("list[%zu] = %d\n", i, *value);
}

// Modify elements by index (like array[i] = newValue)
int newValue = 999;
setDataAtIndex(&list, 2, &newValue, sizeof(int));

// Insert at specific index
insertAtIndex(&list, 1, &newValue, sizeof(int));

// Delete at specific index
deleteAtIndex(&list, 3, NULL);

// Get size (like array.length)
size_t size = getListSize(list);
```

### Function Pointer Types

```c
typedef int (*compare_func_t)(const void *a, const void *b);
typedef void (*print_func_t)(const void *data);
typedef void (*free_data_func_t)(void *data);
```

## Usage Examples

### Integer Linked List

```c
Node *intList = NULL;
int value = 42;

// Insert integers
insertAtTail(&intList, &value, sizeof(int));

// Display the list
displayList(intList, printInt);

// Delete an element
deleteNode(&intList, &value, compareInt);

// Free the list
freeList(&intList, NULL);
```

### String Linked List

```c
Node *stringList = NULL;
const char *text = "Hello World";

// Insert strings (store pointer to string)
insertAtTail(&stringList, &text, sizeof(char *));

// Display and cleanup
displayList(stringList, printString);
freeList(&stringList, NULL);
```

### Custom Struct Example

```c
typedef struct {
    int id;
    char name[50];
    float score;
} Student;

// Custom comparison function
int compareStudent(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentA->id - studentB->id;
}

// Custom print function
void printStudent(const void *data) {
    const Student *student = (const Student *)data;
    printf("Student{id:%d, name:%s, score:%.2f}",
           student->id, student->name, student->score);
}

// Usage
Node *studentList = NULL;
Student student = {1, "Alice", 95.5};

insertAtTail(&studentList, &student, sizeof(Student));
displayList(studentList, printStudent);
freeList(&studentList, NULL);
```

### Array-like Operations Example

```c
Node *list = NULL;
int nums[] = {10, 20, 30, 40, 50};

// Build list like an array
for (int i = 0; i < 5; i++) {
    insertAtTail(&list, &nums[i], sizeof(int));
}

// Array-like access and modification
printf("list[2] = %d\n", *(int*)getDataAtIndex(list, 2)); // Output: 30

int newValue = 999;
setDataAtIndex(&list, 2, &newValue, sizeof(int)); // list[2] = 999

// Insert and delete at specific indices
insertAtIndex(&list, 1, &newValue, sizeof(int)); // Insert at index 1
deleteAtIndex(&list, 3, NULL); // Delete element at index 3

// Get size
printf("List size: %zu\n", getListSize(list)); // Like array.length

freeList(&list, NULL);
```

### Examples with Different Data Types

```c
// Float example
Node *floatList = NULL;
float pi = 3.14f;
insertAtTail(&floatList, &pi, sizeof(float));
displayList(floatList, printFloat);
deleteNode(&floatList, &pi, compareFloat);
freeList(&floatList, NULL);

// Character example
Node *charList = NULL;
char letter = 'A';
insertAtTail(&charList, &letter, sizeof(char));
displayList(charList, printChar);
deleteNode(&charList, &letter, compareChar);
freeList(&charList, NULL);

// Double example
Node *doubleList = NULL;
double precise = 123.456789;
insertAtTail(&doubleList, &precise, sizeof(double));
displayList(doubleList, printDouble);
deleteNode(&doubleList, &precise, compareDouble);
freeList(&doubleList, NULL);

// Long example
Node *longList = NULL;
long bigNumber = 1000000L;
insertAtTail(&longList, &bigNumber, sizeof(long));
displayList(longList, printLong);
deleteNode(&longList, &bigNumber, compareLong);
freeList(&longList, NULL);
```

## Building and Running

### Compile the examples:
```bash
cd examples

# Original generic list example
gcc -Wall -Wextra -std=c99 -g -I../include generic_list_example.c ../src/linkedList/*.c -o generic_list_example

# Array-like functionality example
gcc -Wall -Wextra -std=c99 -g -I../include array_like_example.c ../src/linkedList/*.c -o array_like_example

# Comprehensive data types example
gcc -Wall -Wextra -std=c99 -g -I../include all_types_example.c ../src/linkedList/*.c -o all_types_example

# Comparison example (traditional vs array-like)
gcc -Wall -Wextra -std=c99 -g -I../include comparison_example.c ../src/linkedList/*.c -o comparison_example
```

### Run the examples:
```bash
# Run original example
./generic_list_example

# Run array-like example
./array_like_example

# Run comprehensive data types example
./all_types_example

# Run comparison example
./comparison_example
```

## Key Changes from Original Implementation

1. **Data Storage**: Changed from `int data` to `void *data` with `size_t dataSize`
2. **Memory Management**: Added proper memory allocation and copying for generic data
3. **Function Pointers**: Added support for custom comparison and print functions
4. **Type Safety**: All functions now require appropriate function pointers for operations
5. **Flexibility**: Can handle any data type including complex structs
6. **Array-like Access**: Added index-based operations for familiar array-like usage (NEW!)
7. **Complete Helper Functions**: Added compare and print functions for all common C data types (NEW!)

## Memory Management Notes

- The linked list creates copies of the data you provide
- For complex data types with pointers, you may need custom free functions
- Always call `freeList()` to prevent memory leaks
- Use `NULL` as the free function for simple data types

## Performance Considerations

### Array-like Operations Time Complexity:
- `getDataAtIndex(list, i)`: O(i) - Linear time to reach index i
- `setDataAtIndex(list, i, data)`: O(i) - Linear time to reach index i
- `insertAtIndex(list, i, data)`: O(i) - Linear time to reach index i
- `deleteAtIndex(list, i)`: O(i) - Linear time to reach index i
- `getListSize(list)`: O(n) - Must traverse entire list

### Best Practices:
- For frequent random access, consider using arrays or dynamic arrays
- Use linked lists when you primarily insert/delete at head/tail
- Cache list size if you need it frequently
- Use traditional linked list operations (`insertAtHead`, `insertAtTail`) when possible for better performance
