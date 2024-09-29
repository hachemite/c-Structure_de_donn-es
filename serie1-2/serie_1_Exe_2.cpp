#include <stdio.h>

int main() {
    int num1, num2;
    float result;
    // Ask the user to enter two integers
    printf("Enter the first integer: ");
    scanf("%d", &num1);
    printf("Enter the second integer: ");
    scanf("%d", &num2);
    // Add the two numbers
    result = num1 + num2;
    // Multiply the result by 3
    result *= 3;
    // Divide the result by the first number
    result /= num1;
    // Display the results
    printf("Result: %.2f\n", result);
    return 0;
}

