#include <stdio.h>
#include <stdbool.h>
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

// Fonction de tri du tableau (utilisant le tri par insertion)
void trierTableau(int tableau[], int taille) {
    for (int i = 1; i < taille; i++) {
        int temp = tableau[i];
        int j = i - 1;
        while (j >= 0 && tableau[j] > temp) {
            tableau[j + 1] = tableau[j];
            j--;
        }
        tableau[j + 1] = temp;
    }
}

// Fonction de recherche binaire dans le tableau trié
bool rechercherElement(int tableau[], int taille, int element) {
    int debut = 0;
    int fin = taille - 1;
    while (debut <= fin) {
        int milieu = (debut + fin) / 2;
        if (tableau[milieu] == element) {
            return true; // L'élément a été trouvé
        } else if (tableau[milieu] < element) {
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }
    return false; // L'élément n'a pas été trouvé
}

int main() {
    int tableau[MAX_SIZE];
    int taille, element;   
    printf("Entrez la taille du tableau (max %d) : ", MAX_SIZE);
    scanf("%d", &taille); 
    if (taille <= 0 || taille > MAX_SIZE) {
        printf("Taille invalide.\n");
        return 1; // Quitte le programme avec un code d'erreur
    } 
    saisirTableau(tableau, taille);
    trierTableau(tableau, taille);
    afficherTableau(tableau, taille);    
    printf("Entrez l'element a rechercher : ");
    scanf("%d", &element);    
    if (rechercherElement(tableau, taille, element)) {
        printf("L'element %d a ete trouve dans le tableau.\n", element);
    } else {
        printf("L'element %d n'a pas ete trouve dans le tableau.\n", element);
    }   
    return 0; // Fin normale du programme
}

