#include <stdio.h>
#include <stdlib.h>
//Fonction pour allouer de la m�moire dynamiquement et stocker une valeur
void allouerMemoire(int **ptr) {
    *ptr = (int *)malloc(sizeof(int)); //Allocation de m�moire pour un entier
    if (*ptr == NULL) {
        printf("Erreur lors de l'allocation de m�moire.\n");
        exit(1); //Quitte le programme en cas d'erreur d'allocation
    }
    **ptr = 42; // Stockage de la valeur 42 dans la m�moire allou�e
}
int main() {
    int *ptr = NULL; // Pointeur initialis� � NULL
    // Appel de la fonction pour allouer de la m�moire dynamiquement
    allouerMemoire(&ptr);
    // V�rification que la m�moire a �t� allou�e et que la valeur a �t� stock�e
    if (ptr != NULL) {
        printf("La valeur stock�e dans la m�moire allou�e est : %d\n", *ptr);
        free(ptr); //Lib�ration de la m�moire allou�e
    }
    return 0;
}

