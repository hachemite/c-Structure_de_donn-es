#include <stdio.h>                            
#include <stdlib.h>                           
#include <string.h>


// Définition de la structure pour un étudiant.
typedef struct Etudiant {
    char nom[50];                                // Nom de l'étudiant
    char prenom[50];                             // Prénom de l'étudiant
    char infoComplementaires[100];               // Informations complémentaires facultatives
    struct Etudiant *suivant;                    // Pointeur vers le prochain étudiant dans la liste
} Etudiant;

// Définition de la structure pour une filière.
typedef struct Filiere {
    char nomFiliere[50];                         // Nom de la filière
    int nombreEtudiants;                         // Nombre total d'étudiants dans la filière
    Etudiant *listeEtudiants;                    // Pointeur vers la tête de la liste des étudiants de cette filière
    struct Filiere *suivant;                     // Pointeur vers la filière suivante dans la liste
} Filiere;

// *************Fonctions de gestion des filières****************

// 1. Ajouter une filière à la liste avec les informations suivantes : 
//    nom de la filière, nombre d'étudiants et liste des étudiants. Retourne le nouveau pointeur de tête de la liste des filières.

Filiere* ajouterFiliere(Filiere *head, char *nom, int nombreEtudiants, Etudiant *listeEtudiants) {
    // Allocation de mémoire pour la nouvelle filière
    Filiere *nouvelleFiliere = (Filiere*) malloc(sizeof(Filiere));
    if (nouvelleFiliere == NULL) {
        printf("Erreur d'allocation mémoire\n");          // Gestion d'erreur pour l'allocation de mémoire
        return head;                                      // Retourne la liste inchangée en cas d'échec de l'allocation
    }

    // Initialisation des champs de la nouvelle filière
    strcpy(nouvelleFiliere->nomFiliere, nom);             // Copier le nom dans la nouvelle filière
    nouvelleFiliere->nombreEtudiants = nombreEtudiants;   // Définir le nombre d'étudiants
    nouvelleFiliere->listeEtudiants = listeEtudiants;     // Définir la liste des étudiants

    // Insérer la nouvelle filière au début de la liste des filières
    nouvelleFiliere->suivant = head;                      // Le suivant de la nouvelle filière devient l'ancienne tête
    return nouvelleFiliere;                               // La nouvelle filière est maintenant la tête de la liste
}


// 2. Afficher la liste des filières avec leurs informations (nom, nombre d'étudiants).
void afficherFilieres(Filiere *head) {
    Filiere *current = head;                    // Initialiser le pointeur pour parcourir la liste des filières
    while (current != NULL) {                   // Continuer tant qu'il y a des filières à traiter
        printf("Filière: %s, Nombre d'étudiants: %d\n", current->nomFiliere, current->nombreEtudiants); // Afficher les informations de base de chaque filière

        Etudiant *etudiant = current->listeEtudiants; // Parcourir et afficher les informations des étudiants de la filière
        if (etudiant == NULL) {                 // Vérifier si la liste des étudiants est vide
            printf("  Pas d'étudiants inscrits dans cette filière.\n");
        } else {
            printf("  Liste des étudiants :\n");
            while (etudiant != NULL) {          // Continuer tant qu'il y a des étudiants à afficher
                printf("    Nom: %s, Prénom: %s, Infos: %s\n", etudiant->nom, etudiant->prenom, etudiant->infoComplementaires); // Afficher les détails de chaque étudiant
                etudiant = etudiant->suivant;
            }
        }      
        current = current->suivant;            // Passer à la filière suivante
    }
}



// 3. Trier les filières par nombre d'étudiants.

void permuterValeur(Filiere *f1, Filiere *f2) {
    // Échange des noms des filières
    char nomTemp[50];
    strcpy(nomTemp, f1->nomFiliere);
    strcpy(f1->nomFiliere, f2->nomFiliere);
    strcpy(f2->nomFiliere, nomTemp);

    // Échange des nombres d'étudiants
    int nombreEtudiantsTemp = f1->nombreEtudiants;
    f1->nombreEtudiants = f2->nombreEtudiants;
    f2->nombreEtudiants = nombreEtudiantsTemp;

    // Échange des listes d'étudiants
    Etudiant *listeEtudiantsTemp = f1->listeEtudiants;
    f1->listeEtudiants = f2->listeEtudiants;
    f2->listeEtudiants = listeEtudiantsTemp;
}

void Tri_Bulles(Filiere* head) {
    if (head == NULL) {
    	return; // Si la liste est vide, il n'y a rien à trier.
	}
    Filiere *tmp;  // Pointeur temporaire pour parcourir la liste des filières
    Filiere *cmp;  // Pointeur pour comparer les éléments
    for (tmp = head; tmp->suivant != NULL; tmp = tmp->suivant) { // Parcourir la liste jusqu'à l'avant-dernier élément
        for (cmp = tmp->suivant; cmp != NULL; cmp = cmp->suivant) { // Parcourir la liste depuis l'élément après tmp jusqu'à la fin
            if (tmp->nombreEtudiants > cmp->nombreEtudiants) { // Comparer le nombre d'étudiants
                permuterValeur(tmp, cmp); // Permuter les filières si le nombre d'étudiants de tmp est supérieur à celui de cmp
            }
        }
    }
}



// *************Fonctions de gestion des étudiants****************

// Fonction pour ajouter un nouvel étudiant à la filière spécifiée.
void ajouterEtudiant(Filiere *filiere, Etudiant etudiant) {
    // Allouer de la mémoire pour un nouvel étudiant
    Etudiant *nouvelEtudiant = (Etudiant*) malloc(sizeof(Etudiant));
    if (nouvelEtudiant == NULL) {                     // Vérifier si l'allocation a réussi
        printf("Erreur d'allocation mémoire pour l'étudiant\n");
        return;                                       // Quitter la fonction en cas d'échec de l'allocation
    }
    // Copier les informations de l'étudiant fourni dans le nouvel étudiant
    strcpy(nouvelEtudiant->nom, etudiant.nom);        // Copier le nom
    strcpy(nouvelEtudiant->prenom, etudiant.prenom);  // Copier le prénom
    strcpy(nouvelEtudiant->infoComplementaires, etudiant.infoComplementaires); // Copier les informations complémentaires

    // Insérer le nouvel étudiant au début de la liste des étudiants de la filière
    nouvelEtudiant->suivant = filiere->listeEtudiants; // Faire pointer le nouvel étudiant vers l'ancienne tête de liste
    filiere->listeEtudiants = nouvelEtudiant;          // Faire devenir le nouvel étudiant la nouvelle tête de liste

    // Incrémenter le nombre d'étudiants dans la filière
    filiere->nombreEtudiants++;
}


// 1. Rechercher un étudiant par son nom dans la filière choisie.
Etudiant* rechercherEtudiantDansFiliere(Filiere *filiere, char *nomEtudiant) {
    if (filiere == NULL) {                                                  // Vérifier si la filière fournie est valide
        printf("Aucune filière fournie.\n");
        return NULL;                                                       // Retourner NULL si la filière n'est pas fournie
    }

    Etudiant *current = filiere->listeEtudiants;                          // Initialiser le pointeur pour parcourir la liste des étudiants
    while (current != NULL && strcmp(current->nom, nomEtudiant) != 0) {  // Continuer tant qu'il y a des étudiants et que le nom ne correspond pas
        current = current->suivant;                                     // Passer à l'étudiant suivant dans la liste
    }

    if (current != NULL) {
        return current;                                                 // Retourner le pointeur vers l'étudiant si trouvé
    } 
	else {
        return NULL;                                                    // Retourner NULL si aucun étudiant avec ce nom n'est trouvé
    }
}



// 2. Fonction pour afficher les informations d'un étudiant spécifique dans une filière donnée.

void afficherInformationsEtudiant(Filiere *filiere, char *nom) {
    Etudiant *etudiant = rechercherEtudiantDansFiliere(filiere, nom);  // Rechercher l'étudiant par nom dans la filière spécifiée

    if (etudiant != NULL) {                                           // Vérifier si l'étudiant a été trouvé
        printf("Nom: %s\n", etudiant->nom);                           // Afficher le nom de l'étudiant
        printf("Prénom: %s\n", etudiant->prenom);                     // Afficher le prénom de l'étudiant
        printf("Informations complémentaires: %s\n", etudiant->infoComplementaires); // Afficher les informations complémentaires
    } else {
        printf("Étudiant non trouvé dans la filière %s.\n", filiere->nomFiliere);     // Informer si aucun étudiant n'a été trouvé
    }
}


// 3. Fonction pour modifier les informations d'un étudiant spécifique dans une filière donnée.

void modifierInformationsEtudiant(Filiere *filiere, char *nomEtudiantAModifier, Etudiant nouveauEtudiant) {
    Etudiant *etudiant = rechercherEtudiantDansFiliere(filiere, nomEtudiantAModifier); // Rechercher l'étudiant par son nom

    if (etudiant != NULL) {                                      // Vérifier si l'étudiant a été trouvé
        strcpy(etudiant->nom, nouveauEtudiant.nom);             // Mettre à jour le nom de l'étudiant
        strcpy(etudiant->prenom, nouveauEtudiant.prenom);       // Mettre à jour le prénom de l'étudiant
        strcpy(etudiant->infoComplementaires, nouveauEtudiant.infoComplementaires); // Mettre à jour les informations complémentaires
        printf("Informations mises à jour pour l'étudiant %s.\n", nouveauEtudiant.nom); // Afficher un message de confirmation
    } else {
        printf("Étudiant non trouvé dans la filière %s.\n", filiere->nomFiliere); // Informer si l'étudiant n'a pas été trouvé
    }
}

// Fonction pour libérer la mémoire d'un étudiant
void libererEtudiants(Etudiant *head) {
    Etudiant *current = head;
    while (current != NULL) {
        Etudiant *aSupprimer = current;
        current = aSupprimer->suivant;
        free(aSupprimer);
    }
}

// Fonction pour libérer la mémoire d'une liste de filières
void libererFilieres(Filiere *head) {
    Filiere *current = head;
    while (current != NULL) {
        Filiere *aSupprimer = current;
        current = aSupprimer->suivant;        
        
        // Libérer d'abord la liste des étudiants de la filière
        libererEtudiants(aSupprimer->listeEtudiants);       
        
        // Puis libérer la filière elle-même
        free(aSupprimer);
    }
}


int main() {
    // Initialisation de la liste des filières
    Filiere *listeFiliere = NULL;

    // Ajout de filières à la liste
    listeFiliere = ajouterFiliere(listeFiliere, "Informatique", 0, NULL);
    listeFiliere = ajouterFiliere(listeFiliere, "Mathematiques", 0, NULL);

    // Ajout d'étudiants à la filière Informatique
    Etudiant etudiant1 = {"Bensafi", "Chadia", "Pas d'infos supplémentaires", NULL};
    ajouterEtudiant(listeFiliere, etudiant1);

    Etudiant etudiant2 = {"Bentouil", "Youness", "Aime construire", NULL};
    ajouterEtudiant(listeFiliere, etudiant2);

    // Affichage de toutes les filières et de leurs étudiants
    afficherFilieres(listeFiliere);

    // Recherche et affichage des informations d'un étudiant spécifique
    char *nomRecherche = "Bensafi";
    afficherInformationsEtudiant(listeFiliere, nomRecherche);

    // Modification des informations d'un étudiant
    Etudiant nouvelEtudiant = {"Bensafi", "Amina", "Etudiante en Informatique", NULL};
    modifierInformationsEtudiant(listeFiliere, "Bensafi", nouvelEtudiant);

    // Affichage des informations mises à jour de l'étudiant
    afficherInformationsEtudiant(listeFiliere, "Bensafi");

    // Libération de la mémoire allouée
    libererFilieres(listeFiliere);

    return 0;
}




