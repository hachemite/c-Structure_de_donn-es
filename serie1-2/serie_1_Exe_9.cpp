#include <stdio.h>

// Recursive function to calculate the sum of digits of a positive integer
int sumDigits(int n) {
    // Base case: if the number is less than 10, return the number itself
    if (n < 10) {
        return n;
    } else {
        // Recursive case: sum the last digit with the sum of the digits of the number without the last digit
        return n % 10 + sumDigits(n / 10);
    }
}

int main() {
    int num;
    // Ask the user to enter a positive integer
    printf("Enter a positive integer: ");
    scanf("%d", &num);
    // Check if the number is positive
    if (num < 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    // Call the sumDigits function and display the result
    printf("Sum of digits of %d is: %d\n", num, sumDigits(num));
    return 0;
}

