#include <stdio.h>

int main() {
    // Declare an array of integers named 'scores' of size 5 and initialize it with values of your choice
    int scores[5] = {85, 90, 75, 88, 92};
    // Calculate the sum of all elements in the array
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += scores[i];
    }
    // Display the sum on the screen
    printf("The sum of all elements in the array is: %d\n", sum);
    return 0;
}

