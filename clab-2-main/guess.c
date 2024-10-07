#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int seed;
    int target, guess;
    int attempts = 0;

    // Take users input
    printf("Enter a random seed: ");

    // Check if seed is an integer
    if (scanf("%d", &seed) != 1)
    {
        printf("Invalid input. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    // Seed the random number generator
    srandom(seed);

    // Generate a random number between 1 and 100
    target = random() % 100 + 1;

    // While loop
    do
    {
        printf("Guess a number: ");
        attempts++;
        // Check if guess a number
        if (scanf("%d", &guess) != 1)
        {
            printf("Invalid input. Exiting.\n");
        }

        if (guess > target)
        {
            printf("Too high!\n");
        }
        else if (guess < target)
        {
            printf("Too low!\n");
        }
        else
        {
            printf("Correct! Total guesses = %d\n", attempts);
        }
    } while (guess != target);

    return 0;
}
