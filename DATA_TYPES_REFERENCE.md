# Complete Data Types Helper Functions Reference

## Available Data Types and Helper Functions

Your linked list now supports helper functions for all common C data types:

### 1. **Integer (`int`)**
```c
// Example usage
Node *intList = NULL;
int value = 42;
insertAtTail(&intList, &value, sizeof(int));
displayList(intList, printInt);        // Uses: printInt
deleteNode(&intList, &value, compareInt); // Uses: compareInt
```

### 2. **Character (`char`)**
```c
// Example usage
Node *charList = NULL;
char ch = 'A';
insertAtTail(&charList, &ch, sizeof(char));
displayList(charList, printChar);        // Uses: printChar
deleteNode(&charList, &ch, compareChar); // Uses: compareChar
```

### 3. **Float (`float`)**
```c
// Example usage
Node *floatList = NULL;
float num = 3.14f;
insertAtTail(&floatList, &num, sizeof(float));
displayList(floatList, printFloat);        // Uses: printFloat
deleteNode(&floatList, &num, compareFloat); // Uses: compareFloat
```

### 4. **Double (`double`)**
```c
// Example usage
Node *doubleList = NULL;
double num = 123.456;
insertAtTail(&doubleList, &num, sizeof(double));
displayList(doubleList, printDouble);        // Uses: printDouble
deleteNode(&doubleList, &num, compareDouble); // Uses: compareDouble
```

### 5. **Long (`long`)**
```c
// Example usage
Node *longList = NULL;
long bigNum = 1000000L;
insertAtTail(&longList, &bigNum, sizeof(long));
displayList(longList, printLong);        // Uses: printLong
deleteNode(&longList, &bigNum, compareLong); // Uses: compareLong
```

### 6. **Short (`short`)**
```c
// Example usage
Node *shortList = NULL;
short smallNum = 100;
insertAtTail(&shortList, &smallNum, sizeof(short));
displayList(shortList, printShort);        // Uses: printShort
deleteNode(&shortList, &smallNum, compareShort); // Uses: compareShort
```

### 7. **Unsigned Integer (`unsigned int`)**
```c
// Example usage
Node *uintList = NULL;
unsigned int unum = 42U;
insertAtTail(&uintList, &unum, sizeof(unsigned int));
displayList(uintList, printUnsignedInt);        // Uses: printUnsignedInt
deleteNode(&uintList, &unum, compareUnsignedInt); // Uses: compareUnsignedInt
```

### 8. **String (`char*`)**
```c
// Example usage
Node *stringList = NULL;
const char *text = "Hello World";
insertAtTail(&stringList, &text, sizeof(char*));
displayList(stringList, printString);        // Uses: printString
deleteNode(&stringList, &text, compareString); // Uses: compareString
```

## Complete Function Reference

### Compare Functions:
- `int compareInt(const void *a, const void *b)`
- `int compareChar(const void *a, const void *b)`
- `int compareFloat(const void *a, const void *b)`
- `int compareDouble(const void *a, const void *b)`
- `int compareLong(const void *a, const void *b)`
- `int compareShort(const void *a, const void *b)`
- `int compareUnsignedInt(const void *a, const void *b)`
- `int compareString(const void *a, const void *b)`

### Print Functions:
- `void printInt(const void *data)`
- `void printChar(const void *data)`
- `void printFloat(const void *data)` - Prints with 2 decimal places
- `void printDouble(const void *data)` - Prints with 2 decimal places
- `void printLong(const void *data)`
- `void printShort(const void *data)`
- `void printUnsignedInt(const void *data)`
- `void printString(const void *data)`

## Array-like Operations with Different Types

You can also use array-like syntax with any data type:

```c
// Float example
Node *floatList = NULL;
float values[] = {1.1f, 2.2f, 3.3f};

// Build list
for (int i = 0; i < 3; i++) {
    insertAtTail(&floatList, &values[i], sizeof(float));
}

// Array-like access
float *val = (float*)getDataAtIndex(floatList, 1);  // floatList[1]
printf("Value: %.2f\n", *val);

// Array-like modification
float newVal = 9.99f;
setDataAtIndex(&floatList, 1, &newVal, sizeof(float)); // floatList[1] = 9.99f
```

## Quick Usage Template

```c
#include "linkedList.h"

int main() {
    Node *list = NULL;

    // Replace 'TYPE' with your data type (int, float, char, etc.)
    TYPE value = /* your value */;

    // Insert
    insertAtTail(&list, &value, sizeof(TYPE));

    // Display (choose appropriate print function)
    displayList(list, printTYPE);  // e.g., printInt, printFloat, etc.

    // Delete (choose appropriate compare function)
    deleteNode(&list, &value, compareTYPE);  // e.g., compareInt, compareFloat, etc.

    // Array-like access
    TYPE *retrieved = (TYPE*)getDataAtIndex(list, 0);

    // Clean up
    freeList(&list, NULL);

    return 0;
}
```

## Notes:
- All compare functions return -1, 0, or 1 for less than, equal, or greater than
- Float and double print functions show 2 decimal places by default
- String functions expect `char**` (pointer to string pointer)
- All functions are memory-safe and handle NULL pointers appropriately
