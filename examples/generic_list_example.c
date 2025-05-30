#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Custom struct example
typedef struct
{
    int id;
    char name[50];
    float score;
} Student;

// Custom comparison function for Student
int compareStudent(const void *a, const void *b)
{
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentA->id - studentB->id;
}

// Custom print function for Student
void printStudent(const void *data)
{
    const Student *student = (const Student *)data;
    printf("Student{id:%d, name:%s, score:%.2f}", student->id, student->name, student->score);
}

int main()
{
    printf("=== Generic Linked List Examples ===\n\n");

    // Example 1: Integer linked list
    printf("1. Integer Linked List:\n");
    Node *intList = NULL;

    int nums[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
    {
        insertAtTail(&intList, &nums[i], sizeof(int));
    }

    printf("List: ");
    displayList(intList, printInt);

    // Delete an element
    int deleteKey = 30;
    printf("Deleting %d...\n", deleteKey);
    deleteNode(&intList, &deleteKey, compareInt);
    printf("List after deletion: ");
    displayList(intList, printInt);

    freeList(&intList, NULL);
    printf("\n");

    // Example 2: String linked list
    printf("2. String Linked List:\n");
    Node *stringList = NULL;

    const char *fruits[] = {"Apple", "Banana", "Cherry", "Date"};
    for (int i = 0; i < 4; i++)
    {
        // For strings, we store pointers to the strings
        insertAtTail(&stringList, &fruits[i], sizeof(char *));
    }

    printf("List: ");
    displayList(stringList, printString);

    // Delete a string
    const char *deleteStr = "Banana";
    printf("Deleting %s...\n", deleteStr);
    deleteNode(&stringList, &deleteStr, compareString);
    printf("List after deletion: ");
    displayList(stringList, printString);

    freeList(&stringList, NULL);
    printf("\n");

    // Example 3: Custom struct (Student) linked list
    printf("3. Student Linked List:\n");
    Node *studentList = NULL;

    Student students[] = {
        {1, "Alice", 85.5},
        {2, "Bob", 92.0},
        {3, "Charlie", 78.5},
        {4, "Diana", 95.5}};

    for (int i = 0; i < 4; i++)
    {
        insertAtHead(&studentList, &students[i], sizeof(Student));
    }

    printf("List: ");
    displayList(studentList, printStudent);

    // Delete a student by ID
    Student searchStudent = {2, "", 0.0}; // Only ID matters for comparison
    printf("Deleting student with ID 2...\n");
    deleteNode(&studentList, &searchStudent, compareStudent);
    printf("List after deletion: ");
    displayList(studentList, printStudent);

    freeList(&studentList, NULL);

    printf("\n=== All examples completed successfully! ===\n");
    return 0;
}
