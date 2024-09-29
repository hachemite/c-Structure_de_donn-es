#include <stdio.h>
#define MAX_SIZE 100
// Fonction pour saisir les éléments du tableau
void saisirTableau(int tableau[], int taille) {
    printf("Entrez les elements du tableau :\n");
    for (int i = 0; i < taille; i++) {
        printf("Element %d : ", i + 1);
        scanf("%d", &tableau[i]);
    }
}
// Fonction pour afficher le tableau
void afficherTableau(int tableau[], int taille) {
    printf("Le tableau est : ");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

// Fonction pour rechercher un élément dans le tableau
int rechercherElement(int tableau[], int taille, int element) {
    for (int i = 0; i < taille; i++) {
        if (tableau[i] == element) {
            return i; // Retourne l'indice si l'élément est trouvé
        }
    }
    return -1; // Retourne -1 si l'élément n'est pas trouvé
}

int main() {
    int tableau[MAX_SIZE];
    int taille, element, position;
    printf("Entrez la taille du tableau (max %d) : ", MAX_SIZE);
    scanf("%d", &taille);
    if (taille <= 0 || taille > MAX_SIZE) {
        printf("Taille invalide.\n");
        return 1; // Quitte le programme avec un code d'erreur
    }
    saisirTableau(tableau, taille);
    afficherTableau(tableau, taille);
    printf("Entrez l'element à rechercher : ");
    scanf("%d", &element);
    position = rechercherElement(tableau, taille, element);
    if (position != -1) {
        printf("L'element %d a ete trouve a la position %d dans le tableau.\n", element, position);
    } else {
        printf("L'element %d n'a pas ete trouve dans le tableau.\n", element);
    }

    return 0; // Fin normale du programme
}

