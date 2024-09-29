#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;
    int *arr;
    int sum = 0;
    // Ask the user to specify the size of an array of integers
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    // Dynamically allocate memory for this array
    arr = (int *)malloc(size * sizeof(int));
    // Check if memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }
    // Ask the user to enter the values
    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    // Calculate the sum of the values in the array
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    // Display the result
    printf("Sum of the values in the array: %d\n", sum);
    // Free the dynamically allocated memory
    free(arr);
    return 0;
}

