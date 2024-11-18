#include "linkedlist.h"
#include <stdio.h>
#include <string.h>
#include "talloc.h"
#include "parser.h"

#ifndef _INTERPRETER
#define _INTERPRETER

#include "object.h"

// Helper function to make a Symbol
Object *makeSymbolNew(char *value)
{
    String *newSymbol = talloc(sizeof(Symbol));
    newSymbol->type = SYMBOL_TYPE;
    newSymbol->value = talloc(sizeof(char) * (strlen(value) + 1));
    strcpy(newSymbol->value, value);

    return (Object *)newSymbol;
}

// Helper function for evaluation errors.
// Terminates the program in case of an error in evaluation.
Object *evaluationError()
{
    texit(1);
    return makeNull();
}
// Primitive Function: null?
Object *primitiveNull(Object *args)
{
    if (isNull(args) || !isNull(cdr(args)))
    {
        // printf("Evaluation error: null? requires exactly one argument.\n");
        return evaluationError();
    }

    Object *arg = car(args);
    // printf("Test in primitive Null %d \n", ((Integer *)car(args))->value);
    if (isNull(arg))
    {
        // printf("If null %d \n", ((Integer *)car(args))->value);
        Boolean *result = talloc(sizeof(Boolean));
        result->type = BOOL_TYPE;
        result->value = 1;
        return (Object *)result;
    }
    else
    {
        // printf("If not null %d \n", ((Integer *)car(args))->value);
        Boolean *result = talloc(sizeof(Boolean));
        result->type = BOOL_TYPE;
        result->value = 0;
        return (Object *)result;
    }
}

// Primitive car
Object *primitiveCar(Object *args)
{
    if (isNull(args) || !isNull(cdr(args)))
    {
        return evaluationError();
    }

    Object *arg = car(args);
    if (arg->type != CONS_TYPE)
    {
        return evaluationError();
    }

    return car(arg); // Return the first element of the cons cell
}

Object *primitiveCdr(Object *args)
{
    if (isNull(args) || !isNull(cdr(args)))
    {
        return evaluationError();
    }

    Object *arg = car(args);
    if (arg->type != CONS_TYPE)
    {
        return evaluationError();
    }

    return cdr(arg); // Return the second part of the cons cell
}

Object *primitiveCons(Object *args)
{
    // printf("Test 1 cons \n");
    // if (isNull(args) || !isNull(cdr(args)) || !isNull(cdr(cdr(args))))
    // {
    //     return evaluationError();
    // }
    if (isNull(args) || isNull(cdr(args)) || !isNull(cdr(cdr(args))))
    {
        return evaluationError(); // Error if the argument list is not exactly two items
    }

    // printf("Test 2 cons \n");

    Object *first = car(args);
    Object *second = car(cdr(args));

    // printf("Test 3 cons \n");

    // Create and return a new cons cell
    return cons(first, second);
}

Object *primitiveAdd(Object *args)
{
    double sum = 0.0; // We will always accumulate the sum as a double
    int isDouble = 0; // Flag to track if we've encountered any double

    while (args->type != NULL_TYPE)
    { // Iterate through the arguments
        Object *current = car(args);

        if (current->type == INT_TYPE)
        {
            // If it's an Integer, add its value to the sum
            sum += ((Integer *)current)->value;
        }
        else if (current->type == DOUBLE_TYPE)
        {
            // If it's a Double, add its value to the sum and set the flag
            sum += ((Double *)current)->value;
            isDouble = 1;
        }
        else
        {
            // If the argument is not an Integer or Double, return an error
            return evaluationError();
        }

        args = cdr(args); // Move to the next argument
    }

    // Create a new result object based on whether we encountered a double
    if (isDouble)
    {
        Double *result = talloc(sizeof(Double));
        result->type = DOUBLE_TYPE;
        result->value = sum;
        return (Object *)result;
    }
    else
    {
        Integer *result = talloc(sizeof(Integer));
        result->type = INT_TYPE;
        result->value = (int)sum; // Cast to int if no Doubles were involved
        return (Object *)result;
    }
}

//  START OF DAVE CODE
// Helper function to create an Closure object
Object *makeClosureType(Object *paramNames, Object *functionCode, Frame *frame)
{
    Closure *closureObj = (Closure *)talloc(sizeof(Closure));
    closureObj->type = CLOSURE_TYPE;
    closureObj->paramNames = paramNames;
    closureObj->functionCode = functionCode;
    closureObj->frame = frame;
    return (Object *)closureObj;
}

// Helper function to create a Void object
Object *makeVoidType()
{
    Object *obj = (Object *)talloc(sizeof(Object));
    if (obj == NULL)
    {
        printf("Error when talloc a new Void Type");
        texit(1);
    }
    obj->type = VOID_TYPE;
    return obj;
}

// END OF DAVE CODE

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
// Object *evaluationError()
// {
//     texit(1);
//     return makeNull();
// }

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
    //  START OF DAVE CODE
    else if (tree->type == VOID_TYPE)
    {
        // What to do?
        return makeNull();
    }
    else if (tree->type == CONS_TYPE)
    {
        // Object *firstElement = car(tree); // The first element of the cons cell

        // printf("Test 1 \n");

        Object *firstElementRaw = car(tree); // The first element of the cons cell
        Object *args = cdr(tree);            // The rest of the list (arguments)

        // printf("Test 0 %s \n", ((Symbol *)firstElementRaw)->value);

        // Check if the first element is 'quote'
        if (firstElementRaw->type == SYMBOL_TYPE && strcmp(((Symbol *)firstElementRaw)->value, "quote") == 0)
        {
            // printf("Test 1 go in here \n");
            // If it's 'quote', return the argument as is (do not evaluate)
            if (isNull(args))
            {
                printf("Evaluation Error: Too few arguments to quote\n");
                return evaluationError();
            }
            // Return the argument to quote (without evaluating it)
            return car(args); // This is the quoted expression
        }

        // printf("Test 0 %s \n", ((Symbol *)firstElementRaw)->value);
        // printf("Test 1 %d \n", ((Object *)car(args))->type);

        // printf("Test 1 %d \n", ((Integer *)car(args))->value);

        // Evaluate the first element to determine the function
        // printf("Test 2 \n");
        Object *firstElement = makeNull();

        if (strcmp(((Symbol *)firstElementRaw)->value, "let") == 0 ||
            strcmp(((Symbol *)firstElementRaw)->value, "define") == 0 ||
            strcmp(((Symbol *)firstElementRaw)->value, "lambda") == 0 ||
            strcmp(((Symbol *)firstElementRaw)->value, "quote") == 0
            // ||
            // strcmp(((Symbol *)firstElementRaw)->value, "if") == 0
        )
        {
            firstElement = firstElementRaw;
        }
        else
        {
            // printf("not special \n");
            firstElement = eval(firstElementRaw, frame);
        }

        // printf("Test 3 \n");

        if (firstElement->type == SYMBOL_TYPE)
        {
            // printf("Test 3 \n");

            // printf("Test 3.5 %s \n", ((Symbol *)firstElement)->value);

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
                // printf("Test if go to let \n");
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
            else if (strcmp(((Symbol *)firstElement)->value, "quote") == 0)
            {
                Object *arguments = cdr(tree);

                // Check for too few arguments
                if (isNull(arguments))
                {
                    printf("Evaluation Error: Too few arguments to quote\n");
                    return evaluationError();
                }
                if (!isNull(cdr(arguments)))
                {
                    printf("Evaluation Error: Too many arguments to quote\n");
                    return evaluationError();
                }
                Object *expression = car(arguments);
                return expression;
            }
            // START OF DAVE'S CODE
            else if (strcmp(((Symbol *)firstElement)->value, "define") == 0)
            {
                // Take the argument after the define
                Object *arguments = cdr(tree);
                // Check that define has exactly two arguments
                if (isNull(arguments) || isNull(cdr(arguments)) || !isNull(cdr(cdr(arguments))))
                {
                    printf("Evaluation Error: Invalid number of arguments to define\n");
                    return evaluationError();
                }

                // Set variable and variable expression
                Object *var = car(arguments);
                Object *valExpression = car(cdr(arguments));

                // The first argument should be a symbol
                if (var->type != SYMBOL_TYPE)
                {
                    printf("Evaluation Error: First argument of define must be a symbol\n");
                    return evaluationError();
                }

                // Check that the symbol is not already defined in the current frame
                if (lookUpSymbol(var, frame, true)->type != UNSPECIFIED_TYPE)
                {
                    printf("Evaluation Error: Variable already defined\n");
                    return evaluationError();
                }

                // Evaluate the value expression and bind it to the symbol in the current frame
                Object *val = eval(valExpression, frame);
                // Add it to the current frame
                addBindingHelper(frame, var, val);

                // Return a VOID_TYPE object as the result of the define
                Object *voidObj = makeVoidType();
                return voidObj;
            }
            else if (strcmp(((Symbol *)firstElement)->value, "lambda") == 0)
            {
                // Take the argument after the lambda
                Object *arguments = cdr(tree);
                // Check that lambda has at least one argument
                if (isNull(arguments))
                {
                    printf("Evaluation Error: Lambda requires at least one argument\n");
                    return evaluationError();
                }

                // Assign parameter list and body
                Object *paramList = car(arguments);
                Object *body = cdr(arguments);

                // Ensure Lambda has a body
                if (isNull(body))
                {
                    printf("Evaluation Error: Lambda has no body\n");
                    return evaluationError();
                }

                // Ensure that paramList is a list of symbols and there are no repeats
                Object *currentParam = paramList;
                Object *previousParams = makeNull();
                while (!isNull(currentParam))
                {
                    if (car(currentParam)->type != SYMBOL_TYPE)
                    {
                        printf("Evaluation Error: Parameters must be symbols\n");
                        return evaluationError();
                    }

                    Object *tempPreviousParams = previousParams;

                    // Compare to all previous parameter names
                    while (!isNull(tempPreviousParams))
                    {
                        if (strcmp(((Symbol *)car(currentParam))->value, ((Symbol *)car(tempPreviousParams))->value) == 0)
                        {
                            printf("Evaluation Error: Duplicate identifier %s \n", ((Symbol *)car(currentParam))->value);
                            return evaluationError();
                        }

                        tempPreviousParams = cdr(tempPreviousParams);
                    }

                    // If no duplicates are found, add new parameter name to list
                    previousParams = cons(car(currentParam), previousParams);

                    currentParam = cdr(currentParam);
                }

                // Create the Closure object
                Object *closure = makeClosureType(paramList, body, frame);
                return closure;
            }
            else
            {
                Object *function = lookUpSymbol(car(tree), frame, false);

                if (function->type != CLOSURE_TYPE)
                {
                    printf("Evaluation Error: Not a function\n");
                    return evaluationError();
                }

                // Return evaluation of same code but replacing first symbol with corresponding function
                return eval(cons(function, cdr(tree)), frame);
            }

            // There may be a way to incorporate code above into section below, as there is some repeat lines
        }
        // If the function is a primitive, evaluate arguments and call it
        else if (firstElement->type == PRIMITIVE_TYPE)
        {
            // printf("Test 12 \n");

            Primitive *primitive = (Primitive *)firstElement;

            // printf("Test 13 \n");

            // Evaluate the arguments
            Object *evaluatedArgs = makeNull();

            // printf("Test 14 \n");

            while (!isNull(args))
            {
                // printf("Test 15 \n");

                // printf("Test in if statement %d \n", ((Object *)car(car(args)))->type);
                // printf("Test in if statement %d \n", ((Integer *)(car(args)))->value);

                evaluatedArgs = cons(eval(car(args), frame), evaluatedArgs);
                args = cdr(args);
            }
            // printf("Test 16 \n");

            evaluatedArgs = reverse(evaluatedArgs); // Preserve argument order

            // printf("Test 17 \n");

            // Call the primitive function
            // return primitive->pf(evaluatedArgs);
            Object *test = primitive->pf(evaluatedArgs);
            // printf("Test 18 \n");

            // printf("Test 16 type of test is %d \n", ((Object *)test)->type);
            return test;
        }
        else if (firstElement->type == CLOSURE_TYPE)
        {
            Object *function = firstElement;

            Frame *local = createNewFrameFrom(((Closure *)function)->frame);
            Object *bindingNames = ((Closure *)function)->paramNames;
            Object *args = cdr(tree);

            // Map args to parameter names
            while (!isNull(args))
            {
                if (isNull(bindingNames))
                {
                    printf("Evaluation Error: Too many arguments to function\n");
                    return evaluationError();
                }

                // Add binding to new local frame
                addBindingHelper(local, car(bindingNames), car(args));

                bindingNames = cdr(bindingNames);
                args = cdr(args);
            }
            if (!isNull(bindingNames))
            {
                printf("Evaluation Error: Not enough arguments to function\n");
                return evaluationError();
            }

            Object *body = ((Closure *)function)->functionCode;
            Object *result = makeNull();

            // Evaluate every line in body
            while (!isNull(body))
            {
                result = eval(car(body), local);
                body = cdr(body);
            }
            // Return last line's result
            return result;
        }
        else if (firstElement->type == CONS_TYPE)
        {
            // Replace the Cons cell with corresponding function and evaluate the whole tree
            return eval(cons(eval(firstElement, frame), cdr(tree)), frame);
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
    //  START OF DAVE CODE
    case CLOSURE_TYPE:
        printf("#<procedure>");
        break;
    // END OF DAVE CODE
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
    case VOID_TYPE:
        return;
        break;
    default:
        // () open close not null
        printf("Unknown type ");
        printf("%i", obj->type);
        break;
    }

    printf("\n");
}

void initializePrimitives(Frame *frame)
{
    Primitive *nullPrimitive = talloc(sizeof(Primitive));
    nullPrimitive->type = PRIMITIVE_TYPE;
    nullPrimitive->pf = primitiveNull;
    addBindingHelper(frame, makeSymbolNew("null?"), (Object *)nullPrimitive);

    Primitive *plusPrimitive = talloc(sizeof(Primitive));
    plusPrimitive->type = PRIMITIVE_TYPE;
    plusPrimitive->pf = primitiveAdd;
    addBindingHelper(frame, makeSymbolNew("+"), (Object *)plusPrimitive);

    Primitive *consPrimitive = talloc(sizeof(Primitive));
    consPrimitive->type = PRIMITIVE_TYPE;
    consPrimitive->pf = primitiveCons;
    addBindingHelper(frame, makeSymbolNew("cons"), (Object *)consPrimitive);

    Primitive *carPrimitive = talloc(sizeof(Primitive));
    carPrimitive->type = PRIMITIVE_TYPE;
    carPrimitive->pf = primitiveCar;
    addBindingHelper(frame, makeSymbolNew("car"), (Object *)carPrimitive);

    Primitive *cdrPrimitive = talloc(sizeof(Primitive));
    cdrPrimitive->type = PRIMITIVE_TYPE;
    cdrPrimitive->pf = primitiveCdr;
    addBindingHelper(frame, makeSymbolNew("cdr"), (Object *)cdrPrimitive);
}

// Input tree: A cons cell representing the root of the abstract syntax tree for
// a Scheme program (which may contain multiple expressions).
// Evaluates the program, printing the result of each expression in it.
void interpret(Object *tree)
{
    // Evaluate the current expression in the global frame
    Frame *globalFrame = createNewFrameFrom(NULL);

    initializePrimitives(globalFrame);

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

// END OF THE CODE
#endif