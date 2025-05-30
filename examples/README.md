# Generic Linked List Implementation

This directory contains a generic linked list implementation in C that can handle any data type.

## Features

- **Generic**: Can store any data type using `void*` pointers
- **Type-safe**: Uses function pointers for comparison and printing operations
- **Memory-safe**: Proper memory allocation and deallocation
- **Flexible**: Support for custom data types with custom comparison and print functions

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

### Helper Functions (for common data types)

```c
int compareInt(const void *a, const void *b);
int compareString(const void *a, const void *b);
void printInt(const void *data);
void printString(const void *data);
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

## Building and Running

### Compile the example:
```bash
cd examples
gcc -Wall -Wextra -std=c99 -g -I../include generic_list_example.c ../src/linkedList/*.c -o generic_list_example
```

### Run the example:
```bash
./generic_list_example
```

## Key Changes from Original Implementation

1. **Data Storage**: Changed from `int data` to `void *data` with `size_t dataSize`
2. **Memory Management**: Added proper memory allocation and copying for generic data
3. **Function Pointers**: Added support for custom comparison and print functions
4. **Type Safety**: All functions now require appropriate function pointers for operations
5. **Flexibility**: Can handle any data type including complex structs

## Memory Management Notes

- The linked list creates copies of the data you provide
- For complex data types with pointers, you may need custom free functions
- Always call `freeList()` to prevent memory leaks
- Use `NULL` as the free function for simple data types
