#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour générer une lettre majuscule de manière aléatoire
char genererLettreAleatoire() {
    return 'A' + rand() % 26;
}

// Fonction pour calculer la fréquence d'occurrence de chaque lettre
void calculerFrequence(char tableau[], int taille, int frequences[]) {
    for (int i = 0; i < taille; i++) {
        frequences[tableau[i] - 'A']++;
    }
}


int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Tableau pour stocker les lettres
    char tableau[101];

    // Remplissage du tableau avec des lettres majuscules de manière aléatoire
    for (int i = 0; i < 101; i++) {
        tableau[i] = genererLettreAleatoire();
    }

    // Tableau pour stocker les fréquences d'occurrence de chaque lettre
    int frequences[26] = {0};

    // Calcul des fréquences d'occurrence
    calculerFrequence(tableau, 101, frequences);

    // affichage des frequences d'occurrence de chaque lettre
    printf("Frequence d'occurrence de chaque lettre de l'alphabet :\n");
    for (int i = 0; i < 26; i++) {
        printf("%c : %d\n", 'A' + i, frequences[i]);
    }

    return 0;
}
