#include <stdio.h>
#include <string.h>

#define MAX_ETUDIANTS 100

struct Etudiant {
    char nom[100];
    char prenom[100];
    char dateNaissance[20];
};

struct Inscriptions {
    struct Etudiant etudiants[MAX_ETUDIANTS];
    int nbEtudiants;
};

void ajouterEtudiant(struct Inscriptions* inscriptions, char nom[], char prenom[], char dateNaissance[]) {
    if (inscriptions->nbEtudiants < MAX_ETUDIANTS) {
        strcpy(inscriptions->etudiants[inscriptions->nbEtudiants].nom, nom);
        strcpy(inscriptions->etudiants[inscriptions->nbEtudiants].prenom, prenom);
        strcpy(inscriptions->etudiants[inscriptions->nbEtudiants].dateNaissance, dateNaissance);
        inscriptions->nbEtudiants++;
        printf("Etudiant ajoute avec succes.\n");
    } else {
        printf("La liste des etudiants est pleine.\n");
    }
}

void afficherEtudiants(struct Inscriptions inscriptions) {
    printf("Liste des etudiants inscrits :\n");
    for (int i = 0; i < inscriptions.nbEtudiants; i++) {
        printf("Nom: %s, Prenom: %s, Date de naissance: %s\n", inscriptions.etudiants[i].nom, inscriptions.etudiants[i].prenom, inscriptions.etudiants[i].dateNaissance);
    }
}

void rechercherEtudiantParNom(struct Inscriptions inscriptions, char nomRecherche[]) {
    int trouve = 0;
    for (int i = 0; i < inscriptions.nbEtudiants; i++) {
        if (strcmp(inscriptions.etudiants[i].nom, nomRecherche) == 0) {
            printf("Etudiant trouve :\n");
            printf("Nom: %s, Prenom: %s, Date de naissance: %s\n", inscriptions.etudiants[i].nom, inscriptions.etudiants[i].prenom, inscriptions.etudiants[i].dateNaissance);
            trouve = 1;
            break;
        }
    }
    if (!trouve) {
        printf("Aucun etudiant trouve avec ce nom.\n");
    }
}

int main() {
    struct Inscriptions inscriptions;
    inscriptions.nbEtudiants = 0;

    int choix;
    char nom[100];
    char prenom[100];
    char dateNaissance[20];
    char nomRecherche[100];

    do {
        printf("\nMenu :\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher la liste des etudiants\n");
        printf("3. Rechercher un etudiant par nom\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le nom de l'etudiant : ");
                scanf("%s", nom);
                printf("Entrez le prenom de l'etudiant : ");
                scanf("%s", prenom);
                printf("Entrez la date de naissance de l'etudiant (jj/mm/aaaa) : ");
                scanf("%s", dateNaissance);
                ajouterEtudiant(&inscriptions, nom, prenom, dateNaissance);
                break;
            case 2:
                afficherEtudiants(inscriptions);
                break;
            case 3:
                printf("Entrez le nom de l'etudiant a rechercher : ");
                scanf("%s", nomRecherche);
                rechercherEtudiantParNom(inscriptions, nomRecherche);
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 4);

    return 0;
}
