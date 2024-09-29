#include <stdio.h>
#include <stdlib.h>
//Fonction pour allouer de la mémoire dynamiquement et stocker une valeur
void allouerMemoire(int **ptr) {
    *ptr = (int *)malloc(sizeof(int)); //Allocation de mémoire pour un entier
    if (*ptr == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        exit(1); //Quitte le programme en cas d'erreur d'allocation
    }
    **ptr = 42; // Stockage de la valeur 42 dans la mémoire allouée
}
int main() {
    int *ptr = NULL; // Pointeur initialisé à NULL
    // Appel de la fonction pour allouer de la mémoire dynamiquement
    allouerMemoire(&ptr);
    // Vérification que la mémoire a été allouée et que la valeur a été stockée
    if (ptr != NULL) {
        printf("La valeur stockée dans la mémoire allouée est : %d\n", *ptr);
        free(ptr); //Libération de la mémoire allouée
    }
    return 0;
}

