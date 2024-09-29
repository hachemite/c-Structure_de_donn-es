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
        printf("Allocation de mémoire échouée.\n");
        return 1;
    }

    printf("Entrez les valeurs du tableau :\n");
    for (int i = 0; i < taille; i++) {
        scanf("%d", &tableau[i]);
    }




    free(tableau);

    return 0;
}
