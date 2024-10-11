#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

// Initializes a Vector with a specified memory size.
void init(Vector *vector, int memorySize)
{
    // Allocate memory for any array
    vector->array = (int *)malloc(memorySize * sizeof(int));
    vector->memorySize = memorySize;
    vector->size = 0;
}

// Frees the memory allocated for the Vector's array.
void cleanup(Vector *vector)
{
    free(vector->array);
    // Resets the pointer
    vector->array = NULL;
    vector->memorySize = 0;
    vector->size = 0;
}

// Prints the contents
void print(Vector *vector)
{
    // print the open bracket
    printf("[");
    for (int i = 0; i < vector->size; i++)
    {
        printf("%d", vector->array[i]);
        if (i < vector->size - 1)
        {
            printf(", ");
        }
    }
    // print the close bracket
    printf("]\n");
}

// Inserts a value at the specified location in the Vector
int insert(Vector *vector, int location, int value)
{
    // Check if the location is valid
    if (location < 0 || location > vector->size)
    {
        return 0;
    }

    // If the array is full, double its size using realloc
    if (vector->size >= vector->memorySize)
    {
        vector->memorySize *= 2;
        int *newArray = (int *)realloc(vector->array, vector->memorySize * sizeof(int));
        if (newArray == NULL)
        {
            return 0; // Return 0 if Failed
        }
        vector->array = newArray;
    }

    // Shift elements to the right to make space for the new value
    for (int i = vector->size; i > location; i--)
    {
        vector->array[i] = vector->array[i - 1];
    }

    // Insert the new value at the target location
    vector->array[location] = value;
    vector->size++; // Increment the size of the vector
    return 1;       // Return 1 if success
}

// Retrieves the value at the specified location in the Vector.
int get(Vector *vector, int location, int *value)
{
    // Check if the location is valid
    if (location < 0 || location >= vector->size)
    {
        return 0;
    }
    *value = vector->array[location];
    return 1;
}

// Deletes the value at the specified location in the Vector
int delete(Vector *vector, int location)
{
    // Check if the location is valid
    if (location < 0 || location >= vector->size)
    {
        return 0;
    }

    // Shift elements to the left to fill the gap of the deleted element
    for (int i = location; i < vector->size - 1; i++)
    {
        vector->array[i] = vector->array[i + 1];
    }

    vector->size--; // Decrement the size of the vector
    return 1;       // Return 1 if successs
}
