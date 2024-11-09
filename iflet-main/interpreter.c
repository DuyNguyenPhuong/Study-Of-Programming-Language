#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include "talloc.h"
#include "parser.h"

#ifndef _INTERPRETER
#define _INTERPRETER

#include "object.h"

// Helper function to create a Unspecific object
Object *makeUnspecificType()
{
    Object *obj = (Object *)talloc(sizeof(Object));
    if (obj == NULL)
    {
        printf("Error when talloc a new Unspecific Type");
        texit(1);
    }
    obj->type = UNSPECIFIED_TYPE;
    return obj;
}

// Helper function to create a new Frame from a specfic frame
// The new frame will have a linked list of bindings and
// a reference to its parent frame.
// Each Node in the linkedlist is a linkedlist where 1st and 2nd elements is
// variable and value
Frame *createNewFrameFrom(Frame *parentFrame)
{
    Frame *newFrame = (Frame *)talloc(sizeof(Frame));
    if (newFrame == NULL)
    {
        printf("Error when talloc a new Frame");
        texit(1);
    }
    newFrame->parent = parentFrame;
    newFrame->bindings = makeNull();

    return newFrame;
}

// Helper function for evaluation errors.
// Terminates the program in case of an error in evaluation.
Object *evaluationError()
{
    texit(1);
    return makeNull();
}

// Look up the symbol in frame
// each frame will have a linked lists of bindings
// Each item of the list is a binding
// a bidning is again a linkedlists of size 2 with 1st elemnent a symbol and 2nd value
Object *lookUpSymbol(Object *symbol, Frame *frame, bool onlyFrame)
{
    while (frame)
    {
        // Check the frame's bindings
        Object *bindings = frame->bindings;
        // Check if the current binding matches the symbol we're looking for
        while (!isNull(bindings) && bindings->type == CONS_TYPE)
        {
            // Current element of the frame's linked lists
            Object *current = car(bindings);
            // Check if current element has the same symbol
            char *currentStr = ((Symbol *)car(current))->value;

            char *symbolStr = ((Symbol *)symbol)->value;
            // If match, return the value associated with the symbol
            if (strcmp(currentStr, symbolStr) == 0)
            {
                return cdr(current);
            }
            // If don't match, move to the next bindings
            else
            {
                bindings = cdr(bindings);
            }
        }
        if (onlyFrame)
        {
            // Only search in the current frame if `onlyFrame` is true
            return makeUnspecificType();
        }
        // Check the parents if we can't find anything
        frame = frame->parent;
    }
    printf("Evaluation Error: symbol '%s' not found.\n", ((Symbol *)symbol)->value);
    return evaluationError();
}

// Helper function to add a binding to a frame.
// Make sure that the variable is not already bound in the frame, then adds it with the given value.
void addBindingHelper(Frame *frame, Object *var, Object *val)
{
    // Check if the variable is already bound in the frame, if so return error
    if (lookUpSymbol(var, frame, true)->type != UNSPECIFIED_TYPE)
    {
        printf("Evaluation Error\n");
        evaluationError();
    }
    // Create a binding pair (var . val) and add it to the frame's bindings
    Object *binding = cons(var, val);
    frame->bindings = cons(binding, frame->bindings);
}

// Evaluates an expression with respect to a given frame.
// Input tree: A cons cell representing the root of the abstract syntax tree for
// a single Scheme expression (not an entire program).
// Input frame: The frame, with respect to which to perform the evaluation.
// Return: The value of the given expression with respect to the given frame.
Object *eval(Object *tree, Frame *frame)
{
    if (tree->type == INT_TYPE)
    {
        return tree;
    }
    else if (tree->type == DOUBLE_TYPE)
    {
        return tree;
    }
    else if (tree->type == STR_TYPE)
    {
        return tree;
    }
    else if (tree->type == BOOL_TYPE)
    {
        return tree;
    }
    else if (tree->type == SYMBOL_TYPE)
    {
        // Look up and return the symbol's value
        return lookUpSymbol(tree, frame, false);
    }
    else if (tree->type == CONS_TYPE)
    {
        Object *firstElement = car(tree);
        if (firstElement->type == SYMBOL_TYPE)
        {
            // If expression handling
            if (strcmp(((Symbol *)firstElement)->value, "if") == 0)
            {
                Object *expression = cdr(tree);
                // If we have this (if)
                if (isNull(expression))
                {
                    printf("Evaluation error\n");
                    return evaluationError();
                }
                // Condition expression
                Object *condition = car(expression);
                if (isNull(condition))
                {
                    printf("Evaluation error\n");
                    return evaluationError();
                }
                // If there is no consequent follwing an if
                if (isNull(cdr(expression)))
                {
                    printf("Evaluation error: no consequent following an if.\n");
                    return evaluationError();
                }

                Object *thenClause = car(cdr(expression));
                // If there is no then clause
                if (isNull(thenClause))
                {
                    printf("Evaluation error\n");
                    return evaluationError();
                }

                Object *elseClause = makeNull();
                // If there is smth after then clause, assign it to then clause
                if (!isNull(cdr(cdr(expression))))
                {
                    elseClause = car(cdr(cdr(expression)));
                }

                // Test if it has more than 3 arguments
                if (!isNull(elseClause))
                {
                    if (!isNull(cdr(cdr(cdr(expression)))))
                    {
                        printf("Evaluation error\n");
                        return evaluationError();
                    }
                }

                // Evaluate the condition
                Object *conditionResult = eval(condition, frame);
                // If condition result is false
                if (conditionResult->type == BOOL_TYPE && ((Boolean *)conditionResult)->value == 0)
                {
                    // If there is an else clause
                    if (!isNull(elseClause))
                    {
                        return eval(elseClause, frame);
                    }
                    // If there is not an else clause
                    else
                    {
                        return makeUnspecificType();
                    }
                }
                // If condition result is true, return then clause
                else
                {
                    return eval(thenClause, frame);
                }
            }
            // Handle let expression
            else if (strcmp(((Symbol *)firstElement)->value, "let") == 0)
            {
                // create a new frame
                Frame *newFrame = createNewFrameFrom(frame);
                // Get argument, don't take the let
                Object *expression = cdr(tree);

                // If we have this (let)
                if (isNull(expression))
                {
                    printf("Evaluation error\n");
                    return evaluationError();
                }
                // Get the biding list
                Object *bindingList = car(expression);
                // Get body expression
                Object *body = makeNull();
                if (!isNull(cdr(expression)))
                {
                    body = cdr(expression);
                }
                // If there is no body, return unspecific type
                if (isNull(body))
                {
                    return makeUnspecificType();
                }

                // If is not a list or list of length 0
                if (bindingList->type != CONS_TYPE && bindingList->type != NULL_TYPE)
                {
                    printf("Evaluation error\n");
                    return evaluationError();
                }

                // Process the binding
                while (!isNull(bindingList))
                {
                    // Current binding
                    Object *binding = car(bindingList);
                    if (binding->type != CONS_TYPE)
                    {
                        printf("Evaluation error\n");
                        return evaluationError();
                    }
                    Object *var = car(binding);
                    // Can be an expression
                    Object *valExpression = car(cdr(binding));

                    // var needs to be symbol type
                    if (var->type != SYMBOL_TYPE)
                    {
                        printf("Evaluation error\n");
                        return evaluationError();
                    }
                    // Can be an expression
                    Object *val = eval(valExpression, frame);
                    // add binding to the new frame
                    addBindingHelper(newFrame, var, val);
                    // Move to the next binding
                    bindingList = cdr(bindingList);
                }

                // Initialize the result
                Object *result = makeUnspecificType();

                while (!isNull(body))
                {
                    // Make a while loop
                    result = eval(car(body), newFrame);

                    body = cdr(body);
                }
                return result;
            }
            // If other expression
            else
            {
                return makeUnspecificType();
            }
        }
        else
        {
            return makeUnspecificType();
        }
    }
    else
    {
        printf("Evaluation error\n");
        return evaluationError();
    }
}

// Input list: A ConsCell that is the head of a list.
// Prints the entire list in a human-readable way.
void printHelper(Object *obj)
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
            printHelper(((ConsCell *)current)->car);
            // Move to the tail of the list
            current = ((ConsCell *)current)->cdr;
            first = false;
        }
        // If not cons type
        // If the list does not end with NULL_TYPE, handle improper termination
        if (current->type != NULL_TYPE)
        {
            printf(" . ");        // End of list
            printHelper(current); // Display the non-null tail element
        }
        printf(")"); // End of the list representation
        break;
    }
    case NULL_TYPE:
        printf("()");
        break;
    case UNSPECIFIED_TYPE:
        printf("#<unspecified>");
        break;
    default:
        // () open close not null
        printf("Unknown type");
        printf("%i", obj->type);
        break;
    }

    printf("\n");
}

// Input tree: A cons cell representing the root of the abstract syntax tree for
// a Scheme program (which may contain multiple expressions).
// Evaluates the program, printing the result of each expression in it.
void interpret(Object *tree)
{
    // Evaluate the current expression in the global frame
    Frame *globalFrame = createNewFrameFrom(NULL);

    while (!isNull(tree))
    {
        Object *result = eval(car(tree), globalFrame);
        // Move to the next expression in the program
        tree = cdr(tree);
        // Print the evaluated result of the current expression
        printHelper(result);
    }
    // Exit after completing the interpretation
    texit(0);
}

#endif