#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    double real;
    double imaginary;
} Complex;

Complex multiplyComplex(Complex c1, Complex c2)
{
    Complex result;
    result.real = c1.real * c2.real - c1.imaginary * c2.imaginary;
    result.imaginary = c1.real * c2.imaginary + c1.imaginary * c2.real;
    return result;
}

int main()
{
    Complex c1, c2, c3;

    // Enter 1st complex number
    printf("Enter real part of c1: ");
    if (scanf("%lf", &c1.real) != 1)
    {
        printf("Invalid input. Exiting the program.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter imaginary part of c1: ");
    if (scanf("%lf", &c1.imaginary) != 1)
    {
        printf("Invalid input. Exiting the program.\n");
        exit(EXIT_FAILURE);
    }

    // Enter 2nd complex number
    printf("Enter real part of c2: ");
    if (scanf("%lf", &c2.real) != 1)
    {
        printf("Invalid input. Exiting the program.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter imaginary part of c2: ");
    if (scanf("%lf", &c2.imaginary) != 1)
    {
        printf("Invalid input. Exiting the program.\n");
        exit(EXIT_FAILURE);
    }

    // Multiply the two complex numbers
    c3 = multiplyComplex(c1, c2);

    printf("Answer = %10.2f + %10.2f i\n", c3.real, c3.imaginary);

    return 0;
}
