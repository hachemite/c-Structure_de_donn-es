#include <stdio.h>

int main() {
    // Declare an array of integers of size 5
    int numbers[5];

    // Ask the user to enter 5 integers
    printf("Enter 5 integers:\n");
    for (int i = 0; i < 5; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &numbers[i]);
    }

    // Calculate the sum of these numbers
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }

    // Find the largest number in the array
    int largest = numbers[0];
    for (int i = 0; i < 5; i++) {
        if (numbers[i] > largest) {
            largest = numbers[i];
        }
    }

    // Display the sum and the largest number
    printf("Sum of the numbers: %d\n", sum);
    printf("Largest number: %d\n", largest);

    return 0;
}

