#include <stdio.h>                            
#include <stdlib.h>                           
#include <string.h>


// D�finition de la structure pour un �tudiant.
typedef struct Etudiant {
    char nom[50];                                // Nom de l'�tudiant
    char prenom[50];                             // Pr�nom de l'�tudiant
    char infoComplementaires[100];               // Informations compl�mentaires facultatives
    struct Etudiant *suivant;                    // Pointeur vers le prochain �tudiant dans la liste
} Etudiant;

// D�finition de la structure pour une fili�re.
typedef struct Filiere {
    char nomFiliere[50];                         // Nom de la fili�re
    int nombreEtudiants;                         // Nombre total d'�tudiants dans la fili�re
    Etudiant *listeEtudiants;                    // Pointeur vers la t�te de la liste des �tudiants de cette fili�re
    struct Filiere *suivant;                     // Pointeur vers la fili�re suivante dans la liste
} Filiere;

// *************Fonctions de gestion des fili�res****************

// 1. Ajouter une fili�re � la liste avec les informations suivantes : 
//    nom de la fili�re, nombre d'�tudiants et liste des �tudiants. Retourne le nouveau pointeur de t�te de la liste des fili�res.

Filiere* ajouterFiliere(Filiere *head, char *nom, int nombreEtudiants, Etudiant *listeEtudiants) {
    // Allocation de m�moire pour la nouvelle fili�re
    Filiere *nouvelleFiliere = (Filiere*) malloc(sizeof(Filiere));
    if (nouvelleFiliere == NULL) {
        printf("Erreur d'allocation m�moire\n");          // Gestion d'erreur pour l'allocation de m�moire
        return head;                                      // Retourne la liste inchang�e en cas d'�chec de l'allocation
    }

    // Initialisation des champs de la nouvelle fili�re
    strcpy(nouvelleFiliere->nomFiliere, nom);             // Copier le nom dans la nouvelle fili�re
    nouvelleFiliere->nombreEtudiants = nombreEtudiants;   // D�finir le nombre d'�tudiants
    nouvelleFiliere->listeEtudiants = listeEtudiants;     // D�finir la liste des �tudiants

    // Ins�rer la nouvelle fili�re au d�but de la liste des fili�res
    nouvelleFiliere->suivant = head;                      // Le suivant de la nouvelle fili�re devient l'ancienne t�te
    return nouvelleFiliere;                               // La nouvelle fili�re est maintenant la t�te de la liste
}


// 2. Afficher la liste des fili�res avec leurs informations (nom, nombre d'�tudiants).
void afficherFilieres(Filiere *head) {
    Filiere *current = head;                    // Initialiser le pointeur pour parcourir la liste des fili�res
    while (current != NULL) {                   // Continuer tant qu'il y a des fili�res � traiter
        printf("Fili�re: %s, Nombre d'�tudiants: %d\n", current->nomFiliere, current->nombreEtudiants); // Afficher les informations de base de chaque fili�re

        Etudiant *etudiant = current->listeEtudiants; // Parcourir et afficher les informations des �tudiants de la fili�re
        if (etudiant == NULL) {                 // V�rifier si la liste des �tudiants est vide
            printf("  Pas d'�tudiants inscrits dans cette fili�re.\n");
        } else {
            printf("  Liste des �tudiants :\n");
            while (etudiant != NULL) {          // Continuer tant qu'il y a des �tudiants � afficher
                printf("    Nom: %s, Pr�nom: %s, Infos: %s\n", etudiant->nom, etudiant->prenom, etudiant->infoComplementaires); // Afficher les d�tails de chaque �tudiant
                etudiant = etudiant->suivant;
            }
        }      
        current = current->suivant;            // Passer � la fili�re suivante
    }
}



// 3. Trier les fili�res par nombre d'�tudiants.

void permuterValeur(Filiere *f1, Filiere *f2) {
    // �change des noms des fili�res
    char nomTemp[50];
    strcpy(nomTemp, f1->nomFiliere);
    strcpy(f1->nomFiliere, f2->nomFiliere);
    strcpy(f2->nomFiliere, nomTemp);

    // �change des nombres d'�tudiants
    int nombreEtudiantsTemp = f1->nombreEtudiants;
    f1->nombreEtudiants = f2->nombreEtudiants;
    f2->nombreEtudiants = nombreEtudiantsTemp;

    // �change des listes d'�tudiants
    Etudiant *listeEtudiantsTemp = f1->listeEtudiants;
    f1->listeEtudiants = f2->listeEtudiants;
    f2->listeEtudiants = listeEtudiantsTemp;
}

void Tri_Bulles(Filiere* head) {
    if (head == NULL) {
    	return; // Si la liste est vide, il n'y a rien � trier.
	}
    Filiere *tmp;  // Pointeur temporaire pour parcourir la liste des fili�res
    Filiere *cmp;  // Pointeur pour comparer les �l�ments
    for (tmp = head; tmp->suivant != NULL; tmp = tmp->suivant) { // Parcourir la liste jusqu'� l'avant-dernier �l�ment
        for (cmp = tmp->suivant; cmp != NULL; cmp = cmp->suivant) { // Parcourir la liste depuis l'�l�ment apr�s tmp jusqu'� la fin
            if (tmp->nombreEtudiants > cmp->nombreEtudiants) { // Comparer le nombre d'�tudiants
                permuterValeur(tmp, cmp); // Permuter les fili�res si le nombre d'�tudiants de tmp est sup�rieur � celui de cmp
            }
        }
    }
}



// *************Fonctions de gestion des �tudiants****************

// Fonction pour ajouter un nouvel �tudiant � la fili�re sp�cifi�e.
void ajouterEtudiant(Filiere *filiere, Etudiant etudiant) {
    // Allouer de la m�moire pour un nouvel �tudiant
    Etudiant *nouvelEtudiant = (Etudiant*) malloc(sizeof(Etudiant));
    if (nouvelEtudiant == NULL) {                     // V�rifier si l'allocation a r�ussi
        printf("Erreur d'allocation m�moire pour l'�tudiant\n");
        return;                                       // Quitter la fonction en cas d'�chec de l'allocation
    }
    // Copier les informations de l'�tudiant fourni dans le nouvel �tudiant
    strcpy(nouvelEtudiant->nom, etudiant.nom);        // Copier le nom
    strcpy(nouvelEtudiant->prenom, etudiant.prenom);  // Copier le pr�nom
    strcpy(nouvelEtudiant->infoComplementaires, etudiant.infoComplementaires); // Copier les informations compl�mentaires

    // Ins�rer le nouvel �tudiant au d�but de la liste des �tudiants de la fili�re
    nouvelEtudiant->suivant = filiere->listeEtudiants; // Faire pointer le nouvel �tudiant vers l'ancienne t�te de liste
    filiere->listeEtudiants = nouvelEtudiant;          // Faire devenir le nouvel �tudiant la nouvelle t�te de liste

    // Incr�menter le nombre d'�tudiants dans la fili�re
    filiere->nombreEtudiants++;
}


// 1. Rechercher un �tudiant par son nom dans la fili�re choisie.
Etudiant* rechercherEtudiantDansFiliere(Filiere *filiere, char *nomEtudiant) {
    if (filiere == NULL) {                                                  // V�rifier si la fili�re fournie est valide
        printf("Aucune fili�re fournie.\n");
        return NULL;                                                       // Retourner NULL si la fili�re n'est pas fournie
    }

    Etudiant *current = filiere->listeEtudiants;                          // Initialiser le pointeur pour parcourir la liste des �tudiants
    while (current != NULL && strcmp(current->nom, nomEtudiant) != 0) {  // Continuer tant qu'il y a des �tudiants et que le nom ne correspond pas
        current = current->suivant;                                     // Passer � l'�tudiant suivant dans la liste
    }

    if (current != NULL) {
        return current;                                                 // Retourner le pointeur vers l'�tudiant si trouv�
    } 
	else {
        return NULL;                                                    // Retourner NULL si aucun �tudiant avec ce nom n'est trouv�
    }
}



// 2. Fonction pour afficher les informations d'un �tudiant sp�cifique dans une fili�re donn�e.

void afficherInformationsEtudiant(Filiere *filiere, char *nom) {
    Etudiant *etudiant = rechercherEtudiantDansFiliere(filiere, nom);  // Rechercher l'�tudiant par nom dans la fili�re sp�cifi�e

    if (etudiant != NULL) {                                           // V�rifier si l'�tudiant a �t� trouv�
        printf("Nom: %s\n", etudiant->nom);                           // Afficher le nom de l'�tudiant
        printf("Pr�nom: %s\n", etudiant->prenom);                     // Afficher le pr�nom de l'�tudiant
        printf("Informations compl�mentaires: %s\n", etudiant->infoComplementaires); // Afficher les informations compl�mentaires
    } else {
        printf("�tudiant non trouv� dans la fili�re %s.\n", filiere->nomFiliere);     // Informer si aucun �tudiant n'a �t� trouv�
    }
}


// 3. Fonction pour modifier les informations d'un �tudiant sp�cifique dans une fili�re donn�e.

void modifierInformationsEtudiant(Filiere *filiere, char *nomEtudiantAModifier, Etudiant nouveauEtudiant) {
    Etudiant *etudiant = rechercherEtudiantDansFiliere(filiere, nomEtudiantAModifier); // Rechercher l'�tudiant par son nom

    if (etudiant != NULL) {                                      // V�rifier si l'�tudiant a �t� trouv�
        strcpy(etudiant->nom, nouveauEtudiant.nom);             // Mettre � jour le nom de l'�tudiant
        strcpy(etudiant->prenom, nouveauEtudiant.prenom);       // Mettre � jour le pr�nom de l'�tudiant
        strcpy(etudiant->infoComplementaires, nouveauEtudiant.infoComplementaires); // Mettre � jour les informations compl�mentaires
        printf("Informations mises � jour pour l'�tudiant %s.\n", nouveauEtudiant.nom); // Afficher un message de confirmation
    } else {
        printf("�tudiant non trouv� dans la fili�re %s.\n", filiere->nomFiliere); // Informer si l'�tudiant n'a pas �t� trouv�
    }
}

// Fonction pour lib�rer la m�moire d'un �tudiant
void libererEtudiants(Etudiant *head) {
    Etudiant *current = head;
    while (current != NULL) {
        Etudiant *aSupprimer = current;
        current = aSupprimer->suivant;
        free(aSupprimer);
    }
}

// Fonction pour lib�rer la m�moire d'une liste de fili�res
void libererFilieres(Filiere *head) {
    Filiere *current = head;
    while (current != NULL) {
        Filiere *aSupprimer = current;
        current = aSupprimer->suivant;        
        
        // Lib�rer d'abord la liste des �tudiants de la fili�re
        libererEtudiants(aSupprimer->listeEtudiants);       
        
        // Puis lib�rer la fili�re elle-m�me
        free(aSupprimer);
    }
}


int main() {
    // Initialisation de la liste des fili�res
    Filiere *listeFiliere = NULL;

    // Ajout de fili�res � la liste
    listeFiliere = ajouterFiliere(listeFiliere, "Informatique", 0, NULL);
    listeFiliere = ajouterFiliere(listeFiliere, "Mathematiques", 0, NULL);

    // Ajout d'�tudiants � la fili�re Informatique
    Etudiant etudiant1 = {"Bensafi", "Chadia", "Pas d'infos suppl�mentaires", NULL};
    ajouterEtudiant(listeFiliere, etudiant1);

    Etudiant etudiant2 = {"Bentouil", "Youness", "Aime construire", NULL};
    ajouterEtudiant(listeFiliere, etudiant2);

    // Affichage de toutes les fili�res et de leurs �tudiants
    afficherFilieres(listeFiliere);

    // Recherche et affichage des informations d'un �tudiant sp�cifique
    char *nomRecherche = "Bensafi";
    afficherInformationsEtudiant(listeFiliere, nomRecherche);

    // Modification des informations d'un �tudiant
    Etudiant nouvelEtudiant = {"Bensafi", "Amina", "Etudiante en Informatique", NULL};
    modifierInformationsEtudiant(listeFiliere, "Bensafi", nouvelEtudiant);

    // Affichage des informations mises � jour de l'�tudiant
    afficherInformationsEtudiant(listeFiliere, "Bensafi");

    // Lib�ration de la m�moire allou�e
    libererFilieres(listeFiliere);

    return 0;
}




