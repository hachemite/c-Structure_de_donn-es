#include <stdio.h>
#include <stdlib.h>

// D�finition de la liste cha�n�e
struct Noeud {
    int donnee;
    struct Noeud* suivant;
};

// Fonction pour cr�er un nouveau n�ud avec la donn�e donn�e
struct Noeud* creerNoeud(int donnee) {
    struct Noeud* nouveauNoeud = (struct Noeud*)malloc(sizeof(struct Noeud));
    if (nouveauNoeud == NULL) {
        printf("Allocation m�moire a �chou�\n");
        exit(1);
    }
    nouveauNoeud->donnee = donnee;
    nouveauNoeud->suivant = NULL;
    return nouveauNoeud;
}

// Fonction pour ins�rer un nouveau n�ud au d�but de la liste
void insererAuDebut(struct Noeud** teteRef, int donnee) {
    struct Noeud* nouveauNoeud = creerNoeud(donnee);
    nouveauNoeud->suivant = *teteRef;
    *teteRef = nouveauNoeud;
}

// Fonction pour ins�rer un nouveau n�ud � la fin de la liste
void insererALaFin(struct Noeud** teteRef, int donnee) {
    struct Noeud* nouveauNoeud = creerNoeud(donnee);
    if (*teteRef == NULL) {
        *teteRef = nouveauNoeud;
        return;
    }
    struct Noeud* courant = *teteRef;
    while (courant->suivant != NULL) {
        courant = courant->suivant;
    }
    courant->suivant = nouveauNoeud;
}

// Fonction pour afficher les �l�ments de la liste
void afficher(struct Noeud* tete) {
    struct Noeud* courant = tete;
    while (courant != NULL) {
        printf("%d ", courant->donnee);
        courant = courant->suivant;
    }
    printf("\n");
}

// Fonction pour obtenir la taille de la liste
int getTaille(struct Noeud* tete) {
    int taille = 0;
    struct Noeud* courant = tete;
    while (courant != NULL) {
        taille++;
        courant = courant->suivant;
    }
    return taille;
}

// Fonction pour consulter un �l�ment de la liste en fonction de son index
int getElementAtIndex(struct Noeud* tete, int index) {
    int i = 0;
    struct Noeud* courant = tete;
    while (courant != NULL) {
        if (i == index) {
            return courant->donnee;
        }
        i++;
        courant = courant->suivant;
    }
    printf("Index hors limites\n");
    exit(1);
}

// Fonction pour inverser le contenu de la liste
void inverserListe(struct Noeud** teteRef) {
    struct Noeud* precedent = NULL;
    struct Noeud* courant = *teteRef;
    struct Noeud* suivant = NULL;
    while (courant != NULL) {
        suivant = courant->suivant;
        courant->suivant = precedent;
        precedent = courant;
        courant = suivant;
    }
    *teteRef = precedent;
}

// Fonction pour purger les doublons de la liste
void PurgerDoublons(struct Noeud** head)
{
    struct Noeud *ptr1, *ptr2, *dup;
    ptr1 = *head;

    /* Pick elements one by one */
    while (ptr1 != NULL && ptr1->suivant != NULL) {
        ptr2 = ptr1;

        /* Compare the picked element with rest
           of the elements */
        while (ptr2->suivant != NULL) {
            /* If duplicate then delete it */
            if (ptr1->donnee == ptr2->suivant->donnee) {
                /* sequence of steps is important here */
                dup = ptr2->suivant;
                ptr2->suivant = ptr2->suivant->suivant;
                free(dup);
            }
            else /* This is tricky */
                ptr2 = ptr2->suivant;
        }
        ptr1 = ptr1->suivant;
    }
}



// Fonction pour copier la liste source dans une liste de destination
void copierListe(struct Noeud* source, struct Noeud** destination) {
    struct Noeud* courant = source;
    while (courant != NULL) {
        insererALaFin(destination, courant->donnee);
        courant = courant->suivant;
    }
}

int main() {
    struct Noeud* tete = NULL;

    insererALaFin(&tete, 10);
    insererALaFin(&tete, 20);
    insererALaFin(&tete, 30);
    insererALaFin(&tete, 20);
    insererALaFin(&tete, 10);
    insererALaFin(&tete, 10);

    printf("Liste initiale : ");
    afficher(tete);

    printf("Taille de la liste : %d\n", getTaille(tete));

    int index = 1;
    printf("Element � l'index %d : %d\n", index, getElementAtIndex(tete, index));

    inverserListe(&tete);
    printf("Liste invers�e : ");
    afficher(tete);

    PurgerDoublons(&tete);
    printf("Liste apr�s suppression des doublons : ");
    afficher(tete);

    struct Noeud* listeCopiee = NULL;
    copierListe(tete, &listeCopiee);
    printf("Liste copi�e : ");
    afficher(listeCopiee);

    return 0;
}
