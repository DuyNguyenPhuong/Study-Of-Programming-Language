#include "linkedlist.h"
#include "object.h"
#include "talloc.h"
#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

#ifndef _PARSER
#define _PARSER

// Input tokens: A linked list of tokens. The output of the tokenize function.
// Return: A linked list that stores the abstract syntax tree (forest, actually)
// for that token list. If a syntax error is encountered, then an error message
// is printed and the program cleanly exits.
Object *parse(Object *tokens)
{

    int numUnclosedOpens = 0;
    Object *stack = makeNull();

    while (!isNull(tokens))
    {

        Object *current = car(tokens);

        // If it is not closing, keep adding it to stack
        if (current->type != CLOSE_TYPE && current->type != CLOSEBRACE_TYPE)
        {
            stack = cons(current, stack);
            if (current->type == OPEN_TYPE)
            {
                numUnclosedOpens++;
            }
        }
        else
        {
            int closes = 1;
            // If it is not a }, then it represents one close, else it represents all necessary closes
            if (current->type == CLOSEBRACE_TYPE)
            {
                closes = numUnclosedOpens;
            }
            else if (numUnclosedOpens == 0)
            {
                printf("Syntax error: Too many close parentheses\n");
                texit(1);
            }
            for (int i = 0; i < closes; i++)
            {
                numUnclosedOpens--;
                Object *expression = makeNull();
                current = car(stack);
                stack = cdr(stack);
                while (current->type != OPEN_TYPE)
                {
                    expression = cons(current, expression);
                    current = car(stack);
                    stack = cdr(stack);
                }
                stack = cons(expression, stack);
            }
        }
        tokens = cdr(tokens);
    }

    if (numUnclosedOpens > 0)
    {
        printf("Syntax error: not enough close parentheses\n");
        texit(1);
    }

    return reverse(stack);
}

// We use a different function than linkelist.c display(), as this one would
// produce strings of form ""CS 251"" instead of "CS 251"

// Input list: A ConsCell that is the head of a list.
// Prints the entire list in a human-readable way.
void displayHelper(Object *obj)
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
        printf("%s", ((String *)obj)->value);
        break;
    case SYMBOL_TYPE:
        printf("%s", ((Symbol *)obj)->value);
        break;
    case BOOL_TYPE:
        printf("#%s", ((Boolean *)obj)->value ? "t" : "f");
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
            displayHelper(((ConsCell *)current)->car);
            // Move to the tail of the list
            current = ((ConsCell *)current)->cdr;
            first = false;
        }
        // If not cons type
        // If the list does not end with NULL_TYPE, handle improper termination
        if (current->type != NULL_TYPE)
        {
            printf(" . ");          // End of list
            displayHelper(current); // Display the non-null tail element
        }
        printf(")"); // End of the list representation
        break;
    }
    case NULL_TYPE:
        printf("()");
        break;
    default:
        // () open close not null
        printf("Unknown type");
        printf("%i", obj->type);
        break;
    }
}

// Input tree: An abstract syntax tree (forest). The output of parse.
// Prints the tree in a human-readable format that closely resembles the
// original Scheme code that led to the abstract syntax tree.
void printTree(Object *tree)
{

    Object *current = tree; // Pointer to traverse the list
    bool first = true;      // To handle spacing between elements
    // Loop through the list as long as we encounter cons cells
    while (current->type == CONS_TYPE)
    {
        if (!first)
        {
            printf(" "); // Add a space between element if not first
        }
        // Display the head of the current cons cell
        displayHelper(car(current));
        // Move to the tail of the list
        current = cdr(current);
        first = false;
    }
}

#endif