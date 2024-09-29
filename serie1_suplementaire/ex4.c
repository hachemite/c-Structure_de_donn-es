#include <stdio.h>

// fonction récursive pair(N) pour déterminer si un nombre est pair
int pair(int N) {
    // cas de base
    if (N == 0) {
        return 1; // N est pair
    }
    // cas récursif
    return impair(N - 1);
}

// Fonction récursive impair(N) pour déterminer si un nombre est impair
int impair(int N) {
    // cas de base
    if (N == 0) {
        return 0; // N est impair
    }
    // Cas récursif
    return pair(N - 1);
}

int main() {
    int nombre;

    printf("Entrez un nombre entier : ");
    scanf("%d", &nombre);

    if (pair(nombre)) {
        printf("%d est pair.\n", nombre);
    } else {
        printf("%d est impair.\n", nombre);
    }

    return 0;
}
