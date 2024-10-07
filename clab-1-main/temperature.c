#include <stdio.h>

int main()
{
    float fahrenheit, celsius;
    const float LIMIT = -459.67;

    // Take user input
    printf("What is the temperature in Fahrenheit? ");
    scanf("%f", &fahrenheit);

    // Check if the input is below absolute zero
    if (fahrenheit < LIMIT)
    {
        printf("Invalid temperature.\n");
    }
    else
    {
        // Convert to Celsius
        celsius = (fahrenheit - 32) * 5 / 9;

        // Print the result
        printf("%.6f degrees Fahrenheit is equal to %.6f degrees Celsius.\n", fahrenheit, celsius);
    }

    return 0;
}
