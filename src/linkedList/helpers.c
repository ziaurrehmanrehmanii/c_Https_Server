#include "linkedList.h"
#include <stdio.h>
#include <string.h>

// ===== COMPARISON FUNCTIONS =====

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

// Helper function to compare characters
int compareChar(const void *a, const void *b)
{
    char charA = *(const char *)a;
    char charB = *(const char *)b;

    if (charA < charB)
        return -1;
    if (charA > charB)
        return 1;
    return 0;
}

// Helper function to compare floats
int compareFloat(const void *a, const void *b)
{
    float floatA = *(const float *)a;
    float floatB = *(const float *)b;

    if (floatA < floatB)
        return -1;
    if (floatA > floatB)
        return 1;
    return 0;
}

// Helper function to compare doubles
int compareDouble(const void *a, const void *b)
{
    double doubleA = *(const double *)a;
    double doubleB = *(const double *)b;

    if (doubleA < doubleB)
        return -1;
    if (doubleA > doubleB)
        return 1;
    return 0;
}

// Helper function to compare longs
int compareLong(const void *a, const void *b)
{
    long longA = *(const long *)a;
    long longB = *(const long *)b;

    if (longA < longB)
        return -1;
    if (longA > longB)
        return 1;
    return 0;
}

// Helper function to compare shorts
int compareShort(const void *a, const void *b)
{
    short shortA = *(const short *)a;
    short shortB = *(const short *)b;

    if (shortA < shortB)
        return -1;
    if (shortA > shortB)
        return 1;
    return 0;
}

// Helper function to compare unsigned integers
int compareUnsignedInt(const void *a, const void *b)
{
    unsigned int uintA = *(const unsigned int *)a;
    unsigned int uintB = *(const unsigned int *)b;

    if (uintA < uintB)
        return -1;
    if (uintA > uintB)
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

// ===== PRINT FUNCTIONS =====

// Helper function to print integers
void printInt(const void *data)
{
    printf("%d", *(const int *)data);
}

// Helper function to print characters
void printChar(const void *data)
{
    printf("%c", *(const char *)data);
}

// Helper function to print floats
void printFloat(const void *data)
{
    printf("%.2f", *(const float *)data);
}

// Helper function to print doubles
void printDouble(const void *data)
{
    printf("%.2lf", *(const double *)data);
}

// Helper function to print longs
void printLong(const void *data)
{
    printf("%ld", *(const long *)data);
}

// Helper function to print shorts
void printShort(const void *data)
{
    printf("%hd", *(const short *)data);
}

// Helper function to print unsigned integers
void printUnsignedInt(const void *data)
{
    printf("%u", *(const unsigned int *)data);
}

// Helper function to print strings
void printString(const void *data)
{
    printf("%s", *(const char **)data);
}
