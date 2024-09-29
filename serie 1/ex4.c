#include <stdio.h>

int main() {
    int taille = 5;
    int tableau[taille];
    int somme = 0;
    int max;

    printf("Veuillez saisir 5 nombres entiers :\n");
    for (int i = 0; i < taille; i++) {
        scanf("%d", &tableau[i]);
        somme += tableau[i];
        if (i == 0 || tableau[i] > max) {
            max = tableau[i];
        }
    }

    printf("La somme des nombres est : %d\n", somme);

    printf("Le plus grand nombre dans le tableau est : %d\n", max);

    return 0;
}
