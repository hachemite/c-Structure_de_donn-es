#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour g�n�rer une lettre majuscule de mani�re al�atoire
char genererLettreAleatoire() {
    return 'A' + rand() % 26;
}

// Fonction pour calculer la fr�quence d'occurrence de chaque lettre
void calculerFrequence(char tableau[], int taille, int frequences[]) {
    for (int i = 0; i < taille; i++) {
        frequences[tableau[i] - 'A']++;
    }
}


int main() {
    // Initialisation du g�n�rateur de nombres al�atoires
    srand(time(NULL));

    // Tableau pour stocker les lettres
    char tableau[101];

    // Remplissage du tableau avec des lettres majuscules de mani�re al�atoire
    for (int i = 0; i < 101; i++) {
        tableau[i] = genererLettreAleatoire();
    }

    // Tableau pour stocker les fr�quences d'occurrence de chaque lettre
    int frequences[26] = {0};

    // Calcul des fr�quences d'occurrence
    calculerFrequence(tableau, 101, frequences);

    // affichage des frequences d'occurrence de chaque lettre
    printf("Frequence d'occurrence de chaque lettre de l'alphabet :\n");
    for (int i = 0; i < 26; i++) {
        printf("%c : %d\n", 'A' + i, frequences[i]);
    }

    return 0;
}
