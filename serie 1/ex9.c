#include <stdio.h>

int sommeChiffres(int n) {
    if (n == 0) {
        return 0;
    } else {
        return (n % 10) + sommeChiffres(n / 10);
    }
}

int main() {
    int entier;

    printf("Entrez un entier positif : ");
    scanf("%d", &entier);

    if (entier < 0) {
        printf("L'entier doit être positif.\n");
    } else {
        int somme = sommeChiffres(entier);
        printf("La somme des chiffres de %d est : %d\n", entier, somme);
    }

    return 0;
}
