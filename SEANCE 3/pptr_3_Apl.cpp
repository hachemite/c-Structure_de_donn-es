#include <stdio.h>
//Fonction pour changer l'adresse pointée par un pointeur en utilisant un pointeur de pointeur
void changerAdresse(int **ptr, int *nouvelleAdresse) {
    *ptr = nouvelleAdresse; // Changement de l'adresse pointée par le pointeur
}
int main() {
    int valeur1 = 10;
    int valeur2 = 20;
    int *ptr = &valeur1; //Pointeur pointant vers la variable valeur1
    printf("Avant le changement d'adresse : *ptr = %d\n", *ptr);
    printf("Adresse pointée par ptr : %p\n", (void *)ptr);
    //Appel de la fonction pour changer l'adresse pointée par le pointeur
    changerAdresse(&ptr, &valeur2);
    printf("Après le changement d'adresse : *ptr = %d\n", *ptr);
    printf("Adresse pointée par ptr : %p\n", (void *)ptr);
    return 0;
}

