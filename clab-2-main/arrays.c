/* Program demonstrating arrays in C. */

#include <stdio.h>

int main()
{
    int x = 0;
    int array[10];
    // Writing the elements of an array
    for (int i = 0; i < 10; i += 1)
    {
        array[i] = i;
    }
    // Reading from an array
    for (int i = 0; i < 10; i += 1)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
    // Writing past the array results in weirdness;
    printf("x value before writing to array[10]: %i\n", x);
    // array[10] = 5;
    printf("x value after writing to array[10]: %i\n", x);
    // Using pointer arithmetic to access the elements of an array
    printf("Array address: %p\n", array);
    for (int i = 0; i < 10; i += 1)
    {
        printf("Array element at address %p: %i\n", array + i, *(array + i));
    }
    int sum = 0;
    for (int i = 0; i < 10; i += 1)
    {
        sum += array[i];
    }
    printf("Sum of the array: %i\n", sum);
}
