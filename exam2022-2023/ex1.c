#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jouet {
    char* nom;
    float prix;
    int quantite;
    struct jouet* next;
} Jouet;

typedef struct pile {
    Jouet* top;
} Pile;

// Prototypes des fonctions
void ajouterJouet(Pile* pile);
void supprimerJouet(Pile* pile);
void afficherJouets(Pile* pile);
void viderPile(Pile* pile);

int main() {
    Pile pile;
    pile.top = NULL;
    int choix;

    do {
        printf("\nMenu de gestion de la pile :\n");
        printf("1. Ajouter un produit\n");
        printf("2. Supprimer un produit\n");
        printf("3. Afficher tous les produits\n");
        printf("4. Vider la pile\n");
        printf("5. Quitter le programme\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterJouet(&pile);
                break;
            case 2:
                supprimerJouet(&pile);
                break;
            case 3:
                afficherJouets(&pile);
                break;
            case 4:
                viderPile(&pile);
                break;
            case 5:
                break;
            default:
                printf("Choix invalide. Veuillez choisir un nombre entre 1 et 5.\n");
        }
    } while (choix != 5);

    return 0;
}

void ajouterJouet(Pile* pile) {
    Jouet* nouveauJouet = (Jouet*)malloc(sizeof(Jouet));
    nouveauJouet->nom = (char*)malloc(50 * sizeof(char));

    printf("Entrez le nom du jouet : ");
    scanf("%s", nouveauJouet->nom);
    printf("Entrez le prix du jouet : ");
    scanf("%f", &(nouveauJouet->prix));
    printf("Entrez la quantite du jouet : ");
    scanf("%d", &(nouveauJouet->quantite));

    nouveauJouet->next = pile->top;
    pile->top = nouveauJouet;

    printf("Le jouet a ete ajoute avec succes.\n");
}

void supprimerfirstJouet(Pile* pile) {
    if (pile->top == NULL) {
        printf("La pile est vide.\n");
        return;
    }

    Jouet* jouetASupprimer = pile->top;
    pile->top = jouetASupprimer->next;
    free(jouetASupprimer->nom);
    free(jouetASupprimer);

    printf("Le jouet a ete supprime avec succes.\n");
}

void supprimer_jouet(Pile *pile, char *nom) {
    if (pile == NULL || pile->top == NULL) {
        return; // La pile est vide, ou le nom n'est pas trouvé, rien à supprimer
    }

    Jouet *current = pile->top;
    Jouet *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->nom, nom) == 0) {
            if (previous == NULL) {
                pile->top = current->next; // Le jouet à supprimer est en haut de la pile
            } else {
                previous->next = current->next; // Le jouet à supprimer est au milieu ou en bas de la pile
            }
            free(current); // Libérer la mémoire du jouet supprimé
            return;
        }
        previous = current;
        current = current->next;
    }

    // Le nom n'a pas été trouvé dans la pile
    printf("Le jouet '%s' n'a pas été trouvé dans la pile.\n", nom);
}

void afficherJouets(Pile* pile) {
    if (pile->top == NULL) {
        printf("La pile est vide.\n");
        return;
    }

    Jouet* current = pile->top;
    printf("Liste des jouets :\n");
    while (current != NULL) {
        printf("Nom : %s, Prix : %.2f, Quantite : %d\n", current->nom, current->prix, current->quantite);
        current = current->next;
    }
}

void viderPile(Pile* pile) {
    Jouet* current = pile->top;
    Jouet* nextJouet;

    while (current != NULL) {
        nextJouet = current;
        current = current->next;
        free(nextJouet->nom);
        free(nextJouet);
    }

    pile->top = NULL;

    printf("La pile a ete videe avec succes.\n");
}
