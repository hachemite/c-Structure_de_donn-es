#include <stdio.h>
#include <stdlib.h>

int main() {
    int size;
    // Ask the user to enter the size of an array of integers
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    // Dynamically allocate memory for this array
    int *arr = (int *)malloc(size * sizeof(int));
    // Check if memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1;
    }
    // Fill the array with numbers entered by the user
    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }
    // Display the contents of the array
    printf("Contents of the array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    // Free the dynamically allocated memory
    free(arr);
    return 0;
}

