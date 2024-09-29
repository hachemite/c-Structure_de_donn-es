#include <stdio.h>

#define TAILLE_TABLEAU 5

// fonction pour afficher le contenu du tableau dans l'ordre direct
void afficherTableauDirect(int *tableau, int taille) {
    printf("contenu du tableau dans l'ordre direct :\n");
    for (int i = 0; i < taille; i++) {
        printf("%d ", *(tableau + i));
    }
    printf("\n");
}

// fonction pour afficher le contenu du tableau dans l'ordre inverse
void afficherTableauInverse(int *tableau, int taille) {
    printf("Contenu du tableau dans l'ordre inverse :\n");
    for (int i = taille - 1; i >= 0; i--) {
        printf("%d ", *(tableau + i));
    }
    printf("\n");
}

int main() {
    int tableau[TAILLE_TABLEAU] = {1, 2, 3, 4, 5};

    // appel de la fonction pour afficher le contenu dans l'ordre direct
    afficherTableauDirect(tableau, TAILLE_TABLEAU);

    // appel de la fonction pour afficher le contenu dans l'ordre inverse
    afficherTableauInverse(tableau, TAILLE_TABLEAU);

    return 0;
}
