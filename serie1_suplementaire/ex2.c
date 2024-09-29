#include <stdio.h>
#include <stdlib.h>

int main() {
    int taille;
    printf("Entrez la taille du tableau : ");
    scanf("%d", &taille);

    // Allocation dynamique du tableau
    int *tableau = (int *)malloc(taille * sizeof(int));

    // Remplissage du tableau avec des entiers saisis par l'utilisateur
    for (int i = 0; i < taille; i++) {
        printf("Entrez la valeur pour la case %d : ", i);
        scanf("%d", tableau + i);
    }

    // Affichage du contenu du tableau en utilisant des pointeurs
    printf("Contenu du tableau :\n");
    for (int i = 0; i < taille; i++) {
        printf("%d ", *(tableau + i));
    }
    printf("\n");

    // Affichage des adresses correspondant aux différentes cases du tableau
    printf("Adresses des cases du tableau :\n");
    for (int i = 0; i < taille; i++) {
        printf("%p\n", (tableau + i));
    }

    // Libération de la mémoire allouée pour le tableau
    free(tableau);

    return 0;
}
