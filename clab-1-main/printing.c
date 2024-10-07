/* Program demonstrating how to use printf */

#include <stdio.h> // required for printf

int main()
{
    char c = 'a';
    int i = 5;
    long l = (1 << 16) + 1;
    float f = 42.67;
    double d = 109.2;
    char *s = "hello";
    int *p = &i; // more on the & and * symbols later

    printf("Here is an int %i and a char %c and a long %li\n", i, c, l);
    printf("and a float %f and a double %f\n", f, d);
    printf("and a string %s and a pointer %p\n", s, p);

    // Subtract 15 from 87 and print the result
    int result = 87 - 15;
    printf("The result of subtracting 15 from 87 is: %d\n", result);

    return 0;
}