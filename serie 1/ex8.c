#include <stdio.h>
#include <stdlib.h>

int main() {
    int taille;
    int* tableau;
    int somme = 0;

    printf("Entrez la taille du tableau : ");
    scanf("%d", &taille);

    tableau = (int*)malloc(taille * sizeof(int));

    if (tableau == NULL) {
        printf("Allocation de m�moire �chou�e.\n");
        return 1;
    }

    printf("Entrez les valeurs du tableau :\n");
    for (int i = 0; i < taille; i++) {
        scanf("%d", &tableau[i]);
    }

    for (int i = 0; i < taille; i++) {
        somme += tableau[i];
    }

    printf("La somme des valeurs du tableau est : %d\n", somme);

    free(tableau);

    return 0;
}
