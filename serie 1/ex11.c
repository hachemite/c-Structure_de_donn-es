#include <stdio.h>
#include <string.h>

int estPalindromeRecursive(char str[], int debut, int fin) {
    if (debut >= fin) {
        return 1;
    }
    if (str[debut] != str[fin]) {
        return 0;
    }
    return estPalindromeRecursive(str, debut + 1, fin - 1);
}

int estPalindrome(char str[]) {
    int longueur = strlen(str);
    return estPalindromeRecursive(str, 0, longueur - 1);
}

int main() {
    char str[100];
    printf("Entrez une chaine de caracteres : ");
    scanf("%s", str);
    if (estPalindrome(str)) {
        printf("La chaine \"%s\" est un palindrome.\n", str);
    } else {
        printf("La chaine \"%s\" n'est pas un palindrome.\n", str);
    }
    return 0;
}
