#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "object.h"
#include "linkedlist.h"
#include "talloc.h"

// Return: A newly allocated Object of NULL_TYPE.
Object *makeNull()
{
    Object *nullObj = (Object *)talloc(sizeof(Object));
    nullObj->type = NULL_TYPE;
    return nullObj;
}

// // Helper function to create an Integer object
// Object *makeInteger(int value)
// {
//     Integer *intObj = (Integer *)malloc(sizeof(Integer));
//     intObj->type = INT_TYPE;
//     intObj->value = value;
//     return (Object *)intObj;
// }

// // Helper function to create a Double object
// Object *makeDouble(double value)
// {
//     Double *doubleObj = (Double *)malloc(sizeof(Double));
//     doubleObj->type = DOUBLE_TYPE;
//     doubleObj->value = value;
//     return (Object *)doubleObj;
// }

// // Helper function to create a String object
// Object *makeString(const char *str)
// {
//     String *strObj = (String *)malloc(sizeof(String));
//     strObj->type = STR_TYPE;
//     strObj->value = strdup(str); // Duplicate the string into allocated memory
//     return (Object *)strObj;
// }

// Input newCar: An instance of Object or one of its subclasses.
// Input newCdr: An instance of Object or one of its subclasses.
// Return: A newly allocated ConsCell object with that car and cdr.
Object *cons(Object *newCar, Object *newCdr)
{
    ConsCell *cell = (ConsCell *)talloc(sizeof(ConsCell));
    // Initiate the type
    cell->type = CONS_TYPE;
    // Set car and cdr
    cell->car = newCar;
    cell->cdr = newCdr;
    return (Object *)cell;
}

// Input list: A ConsCell that is the head of a list.
// Prints the entire list in a human-readable way.
void display(Object *obj)
{
    // Make a switch base on types
    switch (obj->type)
    {
    case INT_TYPE:
        printf("%d", ((Integer *)obj)->value);
        break;
    case DOUBLE_TYPE:
        printf("%f", ((Double *)obj)->value);
        break;
    case STR_TYPE:
        printf("\"%s\"", ((String *)obj)->value);
        break;
    case CONS_TYPE:
    {
        printf("(");           // Start of the list
        Object *current = obj; // Pointer to traverse the list
        bool first = true;     // To handle spacing between elements
        // Loop through the list as long as we encounter cons cells
        while (current->type == CONS_TYPE)
        {
            if (!first)
            {
                printf(" "); // Add a space between element if not first
            }
            // Display the head of the current cons cell
            display(((ConsCell *)current)->car);
            // Move to the tail of the list
            current = ((ConsCell *)current)->cdr;
            first = false;
        }
        // If not cons type
        // If the list does not end with NULL_TYPE, handle improper termination
        if (current->type != NULL_TYPE)
        {
            printf(" . ");    // End of list
            display(current); // Display the non-null tail element
        }
        printf(")"); // End of the list representation
        break;
    }
    case NULL_TYPE:
        printf("()");
        break;
    default:
        printf("Unknown type");
        break;
    }
}

// Input list: A ConsCell that is the head of a list.
// Return: A ConsCell that is the head of a list. The new list is the reverse of
// the given list. The content of the list (the cars) is not duplicated but
// rather shared between the old and new lists.
Object *reverse(Object *list)
{
    Object *reversed = makeNull();
    Object *current = list;

    while (current->type == CONS_TYPE)
    {
        Object *carObj = ((ConsCell *)current)->car;

        // Instead of duplicating carObj, we just copy the pointer
        reversed = cons(carObj, reversed);

        current = ((ConsCell *)current)->cdr;
    }

    assert(current->type == NULL_TYPE); // Ensure the list ends properly
    return reversed;
}

// Input list: A ConsCell
// Return: The car of that ConsCell.
// This is a convenience function to slightly accelerate taking cars of objects
// known to be cons cells.
Object *car(Object *list)
{
    // Asseration if list is not null or Constype
    assert(list != NULL);
    assert(list->type == CONS_TYPE);
    return ((ConsCell *)list)->car;
}

// Input list: A ConsCell.
// Return: The cdr of that ConsCell.
// This is a convenience function to slightly accelerate taking cars of objects
// known to be cons cells.
Object *cdr(Object *list)
{
    // Asseration if list is not null or Constype
    assert(list != NULL);
    assert(list->type == CONS_TYPE);
    return ((ConsCell *)list)->cdr;
}

// Input list: Any object.
// Return: A Boolean indicating whether that object is of NULL_TYPE.
bool isNull(Object *value)
{
    return (value != NULL) && (value->type == NULL_TYPE);
}

// Input value: A ConsCell that is the head of a list.
// Return: The length of the list. For example, the Scheme list () has length 0,
// and the Scheme list (7) has length 1.
int length(Object *list)
{
    int len = 0;
    Object *current = list;

    // Tranverse throught the list
    while (current->type == CONS_TYPE)
    {
        len++;
        current = ((ConsCell *)current)->cdr;
    }

    assert(current->type == NULL_TYPE); // Ensure the list is terminated
    return len;
}
