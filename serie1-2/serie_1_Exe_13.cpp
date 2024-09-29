#include <stdio.h>
#include <stdlib.h>

int main() {
    char *str;
    int length;

    // Ask the user to enter a string
    printf("Enter the length of string: ");
    scanf("%d", &length);

    // Dynamically allocate memory for the string
    str = (char *)malloc((length + 1) * sizeof(char));

    // Check if memory allocation was successful
    if (str == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        return 1; // Exit with error
    }

    // Ask the user to enter the string
    printf("Enter the string: ");
    scanf("%s", str);

    // Display the entered string
    printf("Entered string: %s\n", str);

    // Free dynamically allocated memory
    free(str);

    return 0;
}

