#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un élément
typedef struct Element {
    int donnee;                    // Donnée stockée dans le nœud
    struct Element* ptr_precedent; // Pointeur vers le nœud précédent dans la liste
    struct Element* ptr_suivant;   // Pointeur vers le nœud suivant dans la liste
} Element;

//Fonction pour insérer un élément au début de la liste
void insertAuDebut(Element** debut, int data) {
    // Allocation d'un nouvel élément
    Element* nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = data;
    nouveau->ptr_precedent = NULL;

    // Si la liste est vide, le nouveau élément devient le premier et le dernier élément
    if (*debut == NULL) {
        nouveau->ptr_suivant = NULL;
        *debut = nouveau;
    } else {
        // Sinon, le nouveau élément devient le premier élément et le deuxième élément pointe vers lui
        nouveau->ptr_suivant = *debut;
        (*debut)->ptr_precedent = nouveau;
        *debut = nouveau;
    }
}

// Ajout d'un élément à la fin de la liste
void ajoutElementFin(Element** debutRef, int donnee) {
    // Allocation d'un nouvel élément
    Element* nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = donnee;
    nouveau->ptr_suivant = NULL;

    // Si la liste est vide, le nouveau élément devient le premier et le dernier élément
    if (*debutRef == NULL) {
        nouveau->ptr_precedent = NULL;
        *debutRef = nouveau;
    } else {
        // Sinon, on parcourt la liste jusqu'à trouver le dernier élément
        Element* temp = *debutRef;
        while (temp->ptr_suivant != NULL) {
            temp = temp->ptr_suivant;
        }

        // Le dernier élément pointe vers le nouveau élément et le nouveau élément devient le dernier élément
        temp->ptr_suivant = nouveau;
        nouveau->ptr_precedent = temp;
    }
}

// Fonction pour compter le nombre d'éléments dans la liste
int countElements(Element* debut, Element* fin) {
    int count = 0;
    Element* temp = debut;
    while (temp != NULL) {
        count++;
        temp = temp->ptr_suivant;
    }
    return count;
}

// Fonction pour insérer un élément à une position donnée
void insererPosition(Element** debut, Element** fin, int donnee, int position) {
    // Si la position est invalide, on ne fait rien
    if (position < 1 || position > countElements(*debut, *fin) + 1) {
        return;
    }
    // Si la position est 1, on insère l'élément au début
    if (position == 1) {
        insertAuDebut(debut, donnee);
        return;
    }Q
    // Si la position est la fin de la liste, on utilise la fonction `ajoutElementFin`
    if (position == countElements(*debut, *fin) + 1) {
        ajoutElementFin(fin, donnee);
        return;
    }
    // Sinon, on parcourt la liste jusqu'à trouver la position d'insertion
    Element* temp = *debut;
    int i = 1;
    while (i < position) {
        temp = temp->ptr_suivant;
        i++;
    }
    // On insère le nouvel élément après l'élément à la position `position - 1`
    Element* nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = donnee;
    nouveau->ptr_precedent = temp->ptr_precedent;
    nouveau->ptr_suivant = temp;
    temp->ptr_precedent->ptr_suivant = nouveau;
    temp->ptr_precedent = nouveau;
}

// Fonction pour supprimer le premier élément de la liste
void supprimerDebut(Element** debut) {
    // Si la liste est vide, on ne fait rien
    if (*debut == NULL) {
        return;
    }
    // Si la liste ne contient qu'un seul élément, on le supprime et la liste devient vide
    if ((*debut)->ptr_suivant == NULL) {
        free(*debut);
        *debut = NULL;
        return;
    }
    // Sinon, on déplace le pointeur de début vers le deuxième élément
    Element* temp = *debut;
    *debut = (*debut)->ptr_suivant;
    (*debut)->ptr_precedent = NULL;
    // On libère la mémoire de l'ancien premier élément
    free(temp);
}

// Fonction pour supprimer le dernier élément de la liste
void supprimerFin(Element** debut) {
    // Si la liste est vide, on ne fait rien
    if (*debut == NULL) {
        return;
    }
    // Si la liste ne contient qu'un seul élément, on le supprime et la liste devient vide
    if ((*debut)->ptr_suivant == NULL) {
        free(*debut);
        *debut = NULL;
        return;
    }
    // On parcourt la liste jusqu'à trouver l'élément précédent du dernier élément
    Element* temp = *debut;
    while (temp->ptr_suivant->ptr_suivant != NULL) {
        temp = temp->ptr_suivant;
    }
    // On libère la mémoire du dernier élément et on met à jour les pointeurs
    free(temp->ptr_suivant);
    temp->ptr_suivant = NULL;
}

// Fonction pour supprimer un élément à une position donnée
void suppremerPosition(Element** debut, int position) {
    // Si la position est invalide, on ne fait rien
    if (position < 1 || position > countElements(*debut, NULL) + 1) {
        return;
    }
    // Si la position est 1, on supprime le premier élément
    if (position == 1) {
        supprimerDebut(debut);
        return;
    }
    // Si la position est la fin de la liste, on supprime le dernier élément
    if (position == countElements(*debut, NULL) + 1) {
        supprimerFin(debut);
        return;
    }
    // Sinon, on parcourt la liste jusqu'à trouver l'élément à supprimer
    Element* temp = *debut;
    int i = 1;
    while (i < position) {
        temp = temp->ptr_suivant;
        i++;
    }
    // On retire l'élément de la liste et on libère sa mémoire
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
        printf("1. Insérer un élément au début\n");
        printf("2. Ajouter un élément à la fin\n");
        printf("3. Insérer un élément à une position donnée\n");
        printf("4. Supprimer le premier élément\n");
        printf("5. Supprimer le dernier élément\n");
        printf("6. Supprimer un élément à une position donnée\n");
        printf("7. Afficher la liste\n");
        printf("8. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez la valeur à insérer au début : ");
                scanf("%d", &donnee);
                insertAuDebut(&debut, donnee);
                break;
            case 2:
                printf("Entrez la valeur à ajouter à la fin : ");
                scanf("%d", &donnee);
                ajoutElementFin(&debut, donnee);
                break;
            case 3:
                printf("Entrez la valeur à insérer : ");
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
                printf("Entrez la position de l'élément à supprimer : ");
                scanf("%d", &position);
                suppremerPosition(&debut, position);
                break;
            case 7:
                printf("Liste : ");
                afficherListe(debut);
                break;
            case 8:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide. Veuillez entrer un choix valide.\n");
        }
    } while (choix != 8);

    return 0;
}

