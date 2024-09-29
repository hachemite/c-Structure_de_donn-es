#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Etudiant {
    char nom[50];
    char prenom[50];
    char infosComplementaires[100]; // Informations complémentaires
    struct Etudiant* suivant;
} Etudiant;

typedef struct Filiere {
    char nom[50];
    int nbEtudiants;
    Etudiant* etudiants; // Liste des étudiants
    struct Filiere* suivante;
} Filiere;

// Fonction pour ajouter une filière à la liste
void ajouterFiliere(Filiere** tete, char nom[], int nbEtudiants) {
    Filiere* nouvelleFiliere = (Filiere*)malloc(sizeof(Filiere));
    if (!nouvelleFiliere) {
        printf("Erreur d'allocation de mémoire!\n");
        return;
    }

    strcpy(nouvelleFiliere->nom, nom);
    nouvelleFiliere->nbEtudiants = nbEtudiants;
    nouvelleFiliere->etudiants = NULL;
    nouvelleFiliere->suivante = *tete;
    *tete = nouvelleFiliere;
}

// Fonction pour afficher les filières
void afficherFilieres(Filiere* tete) {
    Filiere* actuelle = tete;
    while (actuelle != NULL) {
        printf("Nom de la filiere : %s\n", actuelle->nom);
        printf("Nombre d'etudiants : %d\n", actuelle->nbEtudiants);
        printf("\n");
        actuelle = actuelle->suivante;
    }
}

// Fonction pour trier les filières par nombre d'étudiants (tri à bulles)
void trierFilieres(Filiere* tete) {
    int echange;
    Filiere* actuelle;
    Filiere* suivante = NULL;
    do {
        echange = 0;
        actuelle = tete;
        while (actuelle->suivante != suivante) {
            if (actuelle->nbEtudiants > actuelle->suivante->nbEtudiants) {
                // Permuter les filières
                char tempNom[50];
                int tempNbEtudiants;

                strcpy(tempNom, actuelle->nom);
                strcpy(actuelle->nom, actuelle->suivante->nom);
                strcpy(actuelle->suivante->nom, tempNom);

                tempNbEtudiants = actuelle->nbEtudiants;
                actuelle->nbEtudiants = actuelle->suivante->nbEtudiants;
                actuelle->suivante->nbEtudiants = tempNbEtudiants;

                echange = 1;
            }
            actuelle = actuelle->suivante;
        }
        suivante = actuelle;
    } while (echange);
}

// Fonction pour rechercher un étudiant dans une filière
Etudiant* rechercherEtudiant(Filiere* tete, char nomRecherche[]) {
    Filiere* actuelle = tete;
    while (actuelle != NULL) {
        Etudiant* etudiantActuel = actuelle->etudiants;
        while (etudiantActuel != NULL) {
            if (strcmp(etudiantActuel->nom, nomRecherche) == 0) {
                return etudiantActuel; // L'étudiant a été trouvé
            }
            etudiantActuel = etudiantActuel->suivant;
        }
        actuelle = actuelle->suivante;
    }
    return NULL; // L'étudiant n'a pas été trouvé
}

// Fonction pour modifier les informations d'un étudiant
void modifierEtudiant(Etudiant* etudiant) {
    printf("Modifier les informations de l'etudiant :\n");
    printf("Nouveau nom : ");
    scanf("%s", etudiant->nom);
    printf("Nouveau prenom : ");
    scanf("%s", etudiant->prenom);
    printf("Nouvelles informations complementaires : ");
    scanf("%s", etudiant->infosComplementaires);
}

int main() {
    Filiere* filieres = NULL;

    // Exemple d'ajout de filières
    ajouterFiliere(&filieres, "Informatique", 100);
    ajouterFiliere(&filieres, "Electronique", 80);
    ajouterFiliere(&filieres, "Mecanique", 120);

    // Affichage initial des filières
    printf("FILIERES AVANT LE TRI :\n");
    afficherFilieres(filieres);

    // Tri des filières par nombre d'étudiants
    trierFilieres(filieres);

    // Affichage des filières après le tri
    printf("\nFILIERES APRES LE TRI :\n");
    afficherFilieres(filieres);

    // Exemple de recherche et de modification d'un étudiant
    char nomRecherche[50] = "Dupont";
    Etudiant* etudiantRecherche = rechercherEtudiant(filieres, nomRecherche);
    if (etudiantRecherche != NULL) {
        modifierEtudiant(etudiantRecherche);
        printf("Informations de l'etudiant modifiees avec succes.\n");
    } else {
        printf("Etudiant non trouve.\n");
    }

    return 0;
}
