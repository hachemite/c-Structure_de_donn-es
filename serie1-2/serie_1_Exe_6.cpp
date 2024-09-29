#include <stdio.h>

// Function to swap the values of two integers using pointers
void swap(int *ptr1, int *ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

int main() {
    int num1, num2;
    // Ask the user to enter two integers
    printf("Enter the first integer: ");
    scanf("%d", &num1);
    printf("Enter the second integer: ");
    scanf("%d", &num2);
    // Display the values before swapping
    printf("Before swapping:\n");
    printf("First integer: %d\n", num1);
    printf("Second integer: %d\n", num2);
    // Call the swap function to swap the values
    swap(&num1, &num2);
    // Display the values after swapping
    printf("\nAfter swapping:\n");
    printf("First integer: %d\n", num1);
    printf("Second integer: %d\n", num2);
    return 0;
}

