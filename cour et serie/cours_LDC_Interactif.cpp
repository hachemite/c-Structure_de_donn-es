#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure d'un �l�ment
typedef struct Element {
    int donnee;                    // Donn�e stock�e dans le n�ud
    struct Element* ptr_precedent; // Pointeur vers le n�ud pr�c�dent dans la liste
    struct Element* ptr_suivant;   // Pointeur vers le n�ud suivant dans la liste
} Element;

//Fonction pour ins�rer un �l�ment au d�but de la liste
void insertAuDebut(Element** debut, int data) {
    // Allocation d'un nouvel �l�ment
    Element* nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = data;
    nouveau->ptr_precedent = NULL;

    // Si la liste est vide, le nouveau �l�ment devient le premier et le dernier �l�ment
    if (*debut == NULL) {
        nouveau->ptr_suivant = NULL;
        *debut = nouveau;
    } else {
        // Sinon, le nouveau �l�ment devient le premier �l�ment et le deuxi�me �l�ment pointe vers lui
        nouveau->ptr_suivant = *debut;
        (*debut)->ptr_precedent = nouveau;
        *debut = nouveau;
    }
}

// Ajout d'un �l�ment � la fin de la liste
void ajoutElementFin(Element** debutRef, int donnee) {
    // Allocation d'un nouvel �l�ment
    Element* nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = donnee;
    nouveau->ptr_suivant = NULL;

    // Si la liste est vide, le nouveau �l�ment devient le premier et le dernier �l�ment
    if (*debutRef == NULL) {
        nouveau->ptr_precedent = NULL;
        *debutRef = nouveau;
    } else {
        // Sinon, on parcourt la liste jusqu'� trouver le dernier �l�ment
        Element* temp = *debutRef;
        while (temp->ptr_suivant != NULL) {
            temp = temp->ptr_suivant;
        }

        // Le dernier �l�ment pointe vers le nouveau �l�ment et le nouveau �l�ment devient le dernier �l�ment
        temp->ptr_suivant = nouveau;
        nouveau->ptr_precedent = temp;
    }
}

// Fonction pour compter le nombre d'�l�ments dans la liste
int countElements(Element* debut, Element* fin) {
    int count = 0;
    Element* temp = debut;
    while (temp != NULL) {
        count++;
        temp = temp->ptr_suivant;
    }
    return count;
}

// Fonction pour ins�rer un �l�ment � une position donn�e
void insererPosition(Element** debut, Element** fin, int donnee, int position) {
    // Si la position est invalide, on ne fait rien
    if (position < 1 || position > countElements(*debut, *fin) + 1) {
        return;
    }
    // Si la position est 1, on ins�re l'�l�ment au d�but
    if (position == 1) {
        insertAuDebut(debut, donnee);
        return;
    }Q
    // Si la position est la fin de la liste, on utilise la fonction `ajoutElementFin`
    if (position == countElements(*debut, *fin) + 1) {
        ajoutElementFin(fin, donnee);
        return;
    }
    // Sinon, on parcourt la liste jusqu'� trouver la position d'insertion
    Element* temp = *debut;
    int i = 1;
    while (i < position) {
        temp = temp->ptr_suivant;
        i++;
    }
    // On ins�re le nouvel �l�ment apr�s l'�l�ment � la position `position - 1`
    Element* nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = donnee;
    nouveau->ptr_precedent = temp->ptr_precedent;
    nouveau->ptr_suivant = temp;
    temp->ptr_precedent->ptr_suivant = nouveau;
    temp->ptr_precedent = nouveau;
}

// Fonction pour supprimer le premier �l�ment de la liste
void supprimerDebut(Element** debut) {
    // Si la liste est vide, on ne fait rien
    if (*debut == NULL) {
        return;
    }
    // Si la liste ne contient qu'un seul �l�ment, on le supprime et la liste devient vide
    if ((*debut)->ptr_suivant == NULL) {
        free(*debut);
        *debut = NULL;
        return;
    }
    // Sinon, on d�place le pointeur de d�but vers le deuxi�me �l�ment
    Element* temp = *debut;
    *debut = (*debut)->ptr_suivant;
    (*debut)->ptr_precedent = NULL;
    // On lib�re la m�moire de l'ancien premier �l�ment
    free(temp);
}

// Fonction pour supprimer le dernier �l�ment de la liste
void supprimerFin(Element** debut) {
    // Si la liste est vide, on ne fait rien
    if (*debut == NULL) {
        return;
    }
    // Si la liste ne contient qu'un seul �l�ment, on le supprime et la liste devient vide
    if ((*debut)->ptr_suivant == NULL) {
        free(*debut);
        *debut = NULL;
        return;
    }
    // On parcourt la liste jusqu'� trouver l'�l�ment pr�c�dent du dernier �l�ment
    Element* temp = *debut;
    while (temp->ptr_suivant->ptr_suivant != NULL) {
        temp = temp->ptr_suivant;
    }
    // On lib�re la m�moire du dernier �l�ment et on met � jour les pointeurs
    free(temp->ptr_suivant);
    temp->ptr_suivant = NULL;
}

// Fonction pour supprimer un �l�ment � une position donn�e
void suppremerPosition(Element** debut, int position) {
    // Si la position est invalide, on ne fait rien
    if (position < 1 || position > countElements(*debut, NULL) + 1) {
        return;
    }
    // Si la position est 1, on supprime le premier �l�ment
    if (position == 1) {
        supprimerDebut(debut);
        return;
    }
    // Si la position est la fin de la liste, on supprime le dernier �l�ment
    if (position == countElements(*debut, NULL) + 1) {
        supprimerFin(debut);
        return;
    }
    // Sinon, on parcourt la liste jusqu'� trouver l'�l�ment � supprimer
    Element* temp = *debut;
    int i = 1;
    while (i < position) {
        temp = temp->ptr_suivant;
        i++;
    }
    // On retire l'�l�ment de la liste et on lib�re sa m�moire
    temp->ptr_precedent->ptr_suivant = temp->ptr_suivant;
    temp->ptr_suivant->ptr_precedent = temp->ptr_precedent;
    free(temp);
}

// Affichage de la liste
void afficherListe(Element* debut) {
    Element* temp = debut;
    while (temp != NULL) {
        printf("%d<=>", temp->donnee);
        temp = temp->ptr_suivant;
    }
    printf("NULL");
    printf("\n");
}

// Fonction principale
int main() {
    Element* debut = NULL;
    Element* fin = NULL;
    int choix, donnee, position;

    do {
        // Menu d'options
        printf("\nMenu :\n");
        printf("1. Ins�rer un �l�ment au d�but\n");
        printf("2. Ajouter un �l�ment � la fin\n");
        printf("3. Ins�rer un �l�ment � une position donn�e\n");
        printf("4. Supprimer le premier �l�ment\n");
        printf("5. Supprimer le dernier �l�ment\n");
        printf("6. Supprimer un �l�ment � une position donn�e\n");
        printf("7. Afficher la liste\n");
        printf("8. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez la valeur � ins�rer au d�but : ");
                scanf("%d", &donnee);
                insertAuDebut(&debut, donnee);
                break;
            case 2:
                printf("Entrez la valeur � ajouter � la fin : ");
                scanf("%d", &donnee);
                ajoutElementFin(&debut, donnee);
                break;
            case 3:
                printf("Entrez la valeur � ins�rer : ");
                scanf("%d", &donnee);
                printf("Entrez la position : ");
                scanf("%d", &position);
                insererPosition(&debut, &fin, donnee, position);
                break;
            case 4:
                supprimerDebut(&debut);
                break;
            case 5:
                supprimerFin(&debut);
                break;
            case 6:
                printf("Entrez la position de l'�l�ment � supprimer : ");
                scanf("%d", &position);
                suppremerPosition(&debut, position);
                break;
            case 7:
                printf("Liste : ");
                afficherListe(debut);
                break;
            case 8:
                printf("Programme termin�.\n");
                break;
            default:
                printf("Choix invalide. Veuillez entrer un choix valide.\n");
        }
    } while (choix != 8);

    return 0;
}

