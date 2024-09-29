#include <stdio.h>

int main() {
    // Declare an integer variable x and initialize it to 15
    int x = 15;
    // Create a pointer ptr and assign it the address of variable x
    int *ptr = &x;
    // Using the pointer, double the value of x
    *ptr *= 2;
    // Display the new value of x on the screen
    printf("The new value of x is: %d\n", x);
    return 0;
}

