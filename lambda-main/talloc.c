// talloc.c
#include <stdlib.h>
#include <stdio.h>
#include "talloc.h"

// Linked list node to track allocations
typedef struct AllocationNode
{
    void *ptr;                   // Pointer to allocated memory
    struct AllocationNode *next; // Pointer to the next node
} AllocationNode;

// Head of the linked list of allocations (set as NULL)
static AllocationNode *allocations = NULL;

// Input size: The number of bytes to allocate from the heap.
// Return: A pointer to heap-allocated memory of size bytes. NULL upon failure.
// A replacement for the built-in C function malloc. This function tracks the
// allocated heap memory in a data structure, such that tfree can free it later.
void *talloc(size_t size)
{
    // Allocate memory requested by the user
    void *newPtr = malloc(size);
    if (newPtr == NULL)
    {
        return NULL; // Return NULL if malloc fails
    }

    // Create a new node to track this allocation
    AllocationNode *newNode = malloc(sizeof(AllocationNode));
    if (newNode == NULL)
    {
        free(newPtr); // Free the allocated memory if fails
        return NULL;
    }

    newNode->ptr = newPtr;
    newNode->next = allocations;
    allocations = newNode; // Insert newNode at the beginning of the list.

    return newPtr;
}

// Frees all heap memory previously talloced (as well as any memory needed to
// administer that memory).
void tfree()
{
    // Iterate over the linked list and free all allocations
    AllocationNode *current = allocations;
    while (current != NULL)
    {
        free(current->ptr); // Free the allocated memory
        AllocationNode *temp = current;
        current = current->next;
        free(temp); // Free the tracking node
    }
    allocations = NULL; // Reset the head of the list
}

// Input status: A C error code. Zero if no error, non-zero if error.
// A replacement for the built-in C function exit. Calls tfree and then exit.
void texit(int status)
{
    tfree();      // Free all tracked allocations
    exit(status); // Exit with status
}
