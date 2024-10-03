/* This text, enclosed in a matching slash-asterisk pair, is a comment.

To use this program, you must first 'compile' it --- meaning, translate it into
the machine language of your computer. To do this, navigate in a Visual Studio Code
terminal to the directory where you have this file. Then enter

    clang 00mainHelloWorld.c

A file called a.out should appear. This is the executable program. Enter

    ./a.out

to run the program. Do all of this now. Observe the program's output. Then come back here
and study the code. */

/* This first line of code makes the program aware of some basic input and
output functions, defined in a file called stdio.h in the C standard library. */
#include <stdio.h>

/* This next block of code defines a function called 'main'. In a C program,
execution starts at this main function. It is the core of the program. As input
it takes no arguments, which is signaled by the keyword 'void'. As output it
returns an integer. The body of the function is enclosed in curly brackets. */
int main(void)
{
    /* This statement prints a message followed by a newline character. */
    printf("Hello, CS251!\n");
    /* Returning 0 signals 'no error' to the operating system. */
    return 0;
    /* Notice that every statement in the function body is terminated by a
    semicolon. */
}