#include <stdio.h>
//Fonction pour modifier la valeur pointée par un pointeur en utilisant un pointeur de pointeur
void modifierValeur(int **ptr) {
    **ptr = 20; // Modification de la valeur pointée par le pointeur
}
int main() {
    int valeur = 10;
    int *ptr = &valeur; //Pointeur pointant vers la variable valeur
    printf("Avant la modification : valeur = %d\n", *ptr);
    //Appel de la fonction pour modifier la valeur pointée par le pointeur
    modifierValeur(&ptr);
    printf("Après la modification : valeur = %d\n", *ptr);
    return 0;
}

