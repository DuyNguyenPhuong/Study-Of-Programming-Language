#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "object.h"
#include "linkedlist.h"
#include "talloc.h"

#ifndef _TOKENIZER
#define _TOKENIZER

#define MAX_TOKEN_LENGTH 300

Object *makeObject(int type)
{
    Object *newObject = talloc(sizeof(Object));
    newObject->type = type;
    return newObject;
}

// Input: integer to assignt
// Return: Object with inputted value of INT_TYPE
Object *makeInteger(int value)
{
    Integer *newInt = talloc(sizeof(Integer));
    newInt->type = INT_TYPE;
    newInt->value = value;

    return (Object *)newInt;
}

// Input: double to assignt
// Return: Object with inputted value of DOUBLE_TYPE
Object *makeDouble(double value)
{
    Double *newDoub = talloc(sizeof(Double));
    newDoub->type = DOUBLE_TYPE;
    newDoub->value = value;

    return (Object *)newDoub;
}

// Input: string to assignt
// Return: Object with inputted value of STR_TYPE
Object *makeString(char *value)
{
    String *newString = talloc(sizeof(String));
    newString->type = STR_TYPE;
    newString->value = talloc(sizeof(char) * (strlen(value) + 1));
    strcpy(newString->value, value);

    return (Object *)newString;
}

Object *makeBoolean(int value)
{
    Boolean *newBoolean = talloc(sizeof(Boolean));
    newBoolean->type = BOOL_TYPE;
    newBoolean->value = value;
    return (Object *)newBoolean;
}

Object *makeSymbol(char *value)
{
    String *newSymbol = talloc(sizeof(Symbol));
    newSymbol->type = SYMBOL_TYPE;
    newSymbol->value = talloc(sizeof(char) * (strlen(value) + 1));
    strcpy(newSymbol->value, value);

    return (Object *)newSymbol;
}

// Return: A cons cell that is the head of a list. The list consists of the
// tokens read from standard input (stdin).
Object *tokenize()
{
    int ch;                      // int, not char; see fgetc documentation
    char buffer[300 + 1];        // based on 300-char limit plus terminating \0
    int index = 0;               // where in buffer to place the next char read
    objectType type = NULL_TYPE; // type of token being built in buffer
    Object *token;               // token being built
    Object *list = makeNull();
    ch = fgetc(stdin);

    while (ch != EOF)
    {
        char buffer[300 + 1];
        // If it's whitespace skip
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r')
        {
            ch = fgetc(stdin);
            continue;
        }

        // Begin comment, skip until we got the "\n"
        // Handle comments
        else if (ch == ';')
        {
            while (ch != EOF && ch != '\n')
            {
                ch = fgetc(stdin);
            }
            ch = fgetc(stdin); // Move past newline
            continue;
        }
        // Handle open parenthesis
        else if (ch == '(')
        {
            type = OPEN_TYPE;
            token = makeObject(type);
            list = cons(token, list);
            ch = fgetc(stdin);
            continue;
        }

        // Handle Booleans
        else if (ch == '#')
        {
            type = BOOL_TYPE;
            ch = fgetc(stdin);
            if (ch == 't')
            {
                token = makeBoolean(1);
            }
            else if (ch == 'f')
            {
                token = makeBoolean(0);
            }
            else
            {
                printf("Syntax error\n");
                texit(1);
            }
            list = cons(token, list);
            ch = fgetc(stdin);
            continue;
        }

        // Handle Strings
        else if (ch == '\"')
        {
            type = STR_TYPE;
            buffer[0] = '\"';
            int i = 1;
            ch = fgetc(stdin);
            while (ch != '\"' && ch != EOF && index < MAX_TOKEN_LENGTH)
            {
                buffer[i] = ch;
                i++;
                ch = fgetc(stdin);
                if (ch == EOF)
                {
                    printf("Syntax error: Unterminated string\n");
                    texit(1);
                }
            }
            buffer[i] = ch;
            i++;
            buffer[i++] = '\0';
            token = makeString(buffer);
            list = cons(token, list);
            // Ch right now will be the ch after the "
            ch = fgetc(stdin);
            continue;
        }

        // Hanlde either +, -  symbols, or number (integer or double)
        else if (ch == '+' || ch == '-')
        {
            int length = 0;
            buffer[0] = ch;
            length++;
            ch = fgetc(stdin);
            // If 1st character after +- is a digit or '.'
            if (isdigit(ch) || ch == '.')
            {
                bool isDouble = false;
                // if char is . --> make it a double
                if (ch == '.')
                {
                    isDouble = true;
                    buffer[length] = ch;
                    length++;
                    ch = fgetc(stdin);
                    if (!isdigit(ch))
                    {
                        printf("Syntax Error: Invalid Number\n");
                        texit(1);
                    }
                }

                // Turn first part of number into string
                while (isdigit(ch))
                {
                    buffer[length] = ch;
                    length++;
                    ch = fgetc(stdin);
                }

                // If number doesnt have any other part, finish adding to buffer
                if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ')' || ch == '}')
                {
                    buffer[length++] = '\0';
                    // Put character back into stream so it can be tokenized in the next token
                    ungetc(ch, stdin);
                }

                // If number has a '.', then it is a double and we should tokenize the rest
                else if (ch == '.')
                {
                    if (isDouble)
                    {
                        printf("Syntax Error: Invalid Number\n");
                        texit(1);
                    }
                    isDouble = true;
                    // ch is now "."
                    buffer[length] = ch;
                    length++;
                    ch = fgetc(stdin);
                    while (isdigit(ch))
                    {
                        buffer[length] = ch;
                        length++;
                        ch = fgetc(stdin);
                    }
                    // Check if number still ends with a ' ';
                    if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ')' || ch == '}')
                    {
                        buffer[length++] = '\0';
                        // Put character back into stream so it can be tokenized in the next token
                        ungetc(ch, stdin);
                    }
                    else
                    {
                        printf("Syntax Error: Invalid Number\n");
                        texit(1);
                    }
                }
                // If number doesn't end with a possible closing character, throw error
                else
                {
                    printf("Syntax Error: Invalid number\n");
                    texit(1);
                }

                // After full number is in buffer and there are no errors, tokenize it and move to the next character
                char *dummy;
                if (isDouble)
                {
                    list = cons(makeDouble(strtod(buffer, &dummy)), list);
                }
                else
                {
                    list = cons(makeInteger(strtol(buffer, &dummy, 10)), list);
                }
                ch = fgetc(stdin);
                continue;
            }

            // If first character after +- is whitespace or token closer, then it is a symbol
            else if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ')' || ch == '}')
            {
                buffer[1] = '\0';
                // Put character back into stream so it can be tokenized in the next token
                ungetc(ch, stdin);
                list = cons(makeSymbol(buffer), list);
                // Add continue just in case
                ch = fgetc(stdin);
                continue;
            }
            else
            {
                printf("Syntax Error: Invalid Symbol\n");
                texit(1);
            }
        }

        if (isdigit(ch) || ch == '.')
        {
            int length = 0;
            bool isDouble = false;
            // if char is . --> make it a doube
            if (ch == '.')
            {
                isDouble = true;
                buffer[length] = ch;
                length++;
                ch = fgetc(stdin);
                if (!isdigit(ch))
                {
                    printf("Syntax Error: Invalid Number\n");
                    texit(1);
                }
            }

            // Turn first part of number into string
            while (isdigit(ch))
            {
                buffer[length] = ch;
                length++;
                ch = fgetc(stdin);
            }

            // If number doesnt have any other part, finish adding to buffer
            if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ')' || ch == '}')
            {
                buffer[length++] = '\0';
                // Put character back into stream so it can be tokenized in the next token
                ungetc(ch, stdin);
            }

            // If number has a '.', then it is a double and we should tokenize the rest
            else if (ch == '.')
            {
                if (isDouble)
                {
                    printf("Syntax Error: Invalid Number\n");
                    texit(1);
                }
                isDouble = true;
                // ch is now "."
                buffer[length] = ch;
                length++;
                ch = fgetc(stdin);
                while (isdigit(ch))
                {
                    buffer[length] = ch;
                    length++;
                    ch = fgetc(stdin);
                }
                // Check if number still ends with a ' ';
                if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' || ch == ')' || ch == '}')
                {
                    buffer[length++] = '\0';
                    ungetc(ch, stdin);
                }
                else
                {
                    printf("Syntax Error: Invalid Number\n");
                    texit(1);
                }
            }
            // If number doesn't end with a valid token closer, throw error
            else
            {
                printf("Syntax Error: Invalid number\n");
                texit(1);
            }

            // After full number is in buffer and there are no errors, tokenize it and move to the next token
            char *dummy;
            if (isDouble)
            {
                list = cons(makeDouble(strtod(buffer, &dummy)), list);
            }
            else
            {
                list = cons(makeInteger(strtol(buffer, &dummy, 10)), list);
            }
            ch = fgetc(stdin);
            continue;
        }

        // Handle symbols
        else if (isalpha(ch) || strchr("!$%&*/:<=>?~_^", ch))
        {
            index = 0;
            while (isalpha(ch) || isdigit(ch) || strchr("!$%&*/:<=>?~_^+-.", ch))
            {
                buffer[index++] = ch;
                ch = fgetc(stdin);
                if (index >= MAX_TOKEN_LENGTH)
                {
                    printf("Syntax error: Symbol too long\n");
                    texit(1);
                }
            }
            buffer[index] = '\0';
            list = cons(makeSymbol(buffer), list);
            // As symbols don't end with ", we dont have to manually move to the next character"
            continue;
        }

        // Handle close parenthesis
        else if (ch == ')')
        {
            type = CLOSE_TYPE;
            token = makeObject(type);
            list = cons(token, list);
            ch = fgetc(stdin);
            continue;
        }

        // Handle closebrace
        else if (ch == '}')
        {
            type = CLOSEBRACE_TYPE;
            token = makeObject(type);
            list = cons(token, list);
            ch = fgetc(stdin);
            continue;
        }

        // If character was none of these options, it must be invalid character
        else
        {
            printf("Syntax Error: Invalid Symbolllll: %d\n", ch);
            texit(1);
        }
    }
    // first element of list (before reverse) is the last elment of the code
    return reverse(list);
}

// Print a tokenlist to the commandLine
void displayTokens(Object *list)
{
    Object *current = list;
    while (!isNull(current))
    {
        Object *token = car(current);
        if (token == NULL)
        {
            printf("Error Token is null");
            texit(1);
        }
        switch (token->type)
        {
        case OPEN_TYPE:
            printf("(:open\n");
            break;
        case CLOSE_TYPE:
            printf("):close\n");
            break;
        case CLOSEBRACE_TYPE:
            printf("}:closebrace\n");
            break;
        case BOOL_TYPE:
            printf("#%s:boolean\n", ((Boolean *)token)->value ? "t" : "f");
            break;
        case INT_TYPE:
            printf("%d:integer\n", ((Integer *)token)->value);
            break;
        case DOUBLE_TYPE:
            printf("%f:double\n", ((Double *)token)->value);
            break;
        case STR_TYPE:
            printf("%s:string\n", ((String *)token)->value);
            break;
        case SYMBOL_TYPE:
            printf("%s:symbol\n", ((Symbol *)token)->value);
            break;
        default:
            break;
        }
        current = cdr(current);
    }
}
// END OF THE CODE

#endif