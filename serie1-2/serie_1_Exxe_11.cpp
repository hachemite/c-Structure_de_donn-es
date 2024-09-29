#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function prototype
int isPalindrome(char *str, int start, int end);

int main() {
    char str[100];
    
    printf("Enter a string: ");
    scanf("%s", str); // Utilisation de %s, scanf("%99[^\n]", str); 

    if (isPalindrome(str, 0, strlen(str) - 1)) {
        printf("%s is a palindrome.\n", str);
    } else {
        printf("%s is not a palindrome.\n", str);
    }
    
    return 0;
}

// Recursive function to check if a string is a palindrome
int isPalindrome(char *str, int start, int end) {
    // Base case: if start index exceeds end index, it's a palindrome
    if (start >= end) {
        return 1;
    }
    // If characters at start and end index don't match, it's not a palindrome
    if (tolower(str[start]) != tolower(str[end])) {
        return 0;
    }
    // Recursively check if the substring excluding start and end indices is a palindrome
    return isPalindrome(str, start + 1, end - 1);
}

