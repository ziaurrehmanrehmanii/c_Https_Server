#include "linkedList.h"
#include <stdio.h>
#include <string.h>

// Helper function to compare integers
int compareInt(const void *a, const void *b)
{
    int intA = *(const int *)a;
    int intB = *(const int *)b;

    if (intA < intB)
        return -1;
    if (intA > intB)
        return 1;
    return 0;
}

// Helper function to compare strings
int compareString(const void *a, const void *b)
{
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    return strcmp(strA, strB);
}

// Helper function to print integers
void printInt(const void *data)
{
    printf("%d", *(const int *)data);
}

// Helper function to print strings
void printString(const void *data)
{
    printf("%s", *(const char **)data);
}
