#include <stdio.h>
#include <string.h>

#define MAX_LIVRES 100

struct Livre {
    char titre[100];
    char auteur[100];
    int annee;
};

struct Bibliotheque {
    struct Livre livres[MAX_LIVRES];
    int nbLivres;
};

void ajouterLivre(struct Bibliotheque* biblio, char titre[], char auteur[], int annee) {
    if (biblio->nbLivres < MAX_LIVRES) {
        strcpy(biblio->livres[biblio->nbLivres].titre, titre);
        strcpy(biblio->livres[biblio->nbLivres].auteur, auteur);
        biblio->livres[biblio->nbLivres].annee = annee;
        biblio->nbLivres++;
        printf("Livre ajoute avec succes.\n");
    } else {
        printf("La bibliotheque est pleine.\n");
    }
}

void afficherLivres(struct Bibliotheque biblio) {
    printf("Liste des livres :\n");
    for (int i = 0; i < biblio.nbLivres; i++) {
        printf("Titre: %s, Auteur: %s, Annee: %d\n", biblio.livres[i].titre, biblio.livres[i].auteur, biblio.livres[i].annee);
    }
}

void rechercherLivreParTitre(struct Bibliotheque biblio, char titreRecherche[]) {
    int trouve = 0;
    for (int i = 0; i < biblio.nbLivres; i++) {
        if (strcmp(biblio.livres[i].titre, titreRecherche) == 0) {
            printf("Livre trouve :\n");
            printf("Titre: %s, Auteur: %s, Annee: %d\n", biblio.livres[i].titre, biblio.livres[i].auteur, biblio.livres[i].annee);
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("Aucun livre trouve avec ce titre.\n");
    }
}

int main() {
    struct Bibliotheque biblio;
    biblio.nbLivres = 0;

    int choix;
    char titre[100];
    char auteur[100];
    int annee;
    char titreRecherche[100];

    do {
        printf("\nMenu :\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher la liste des livres\n");
        printf("3. Rechercher un livre par titre\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le titre du livre : ");
                scanf("%s", titre);
                printf("Entrez le nom de l'auteur : ");
                scanf("%s", auteur);
                printf("Entrez l'annee de publication : ");
                scanf("%d", &annee);
                ajouterLivre(&biblio, titre, auteur, annee);
                break;

