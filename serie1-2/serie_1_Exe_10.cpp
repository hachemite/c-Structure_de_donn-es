#include <stdio.h>

// Function prototype
unsigned long long factorial(int n);

int main() {
    int n;
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("Factorial is not defined for negative numbers.\n");
    } else {
        printf("Factorial of %d is %llu\n", n, factorial(n));
    }
    
    return 0;
}

// Recursive function to calculate factorial
unsigned long long factorial(int n) {
    // Base case: factorial of 0 is 1
    if (n == 0) {
        return 1;
    }
    // Recursive case: factorial of n is n times factorial of (n-1)
    else {
        return n * factorial(n - 1);
    }
}

