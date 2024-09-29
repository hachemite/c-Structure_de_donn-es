#include <stdio.h>
#include <stdlib.h>

struct Noeud {
    int donnee;
    struct Noeud* suivant;
};

typedef struct Noeud Noeud;

Noeud* creerNoeud(int donnee) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud != NULL) {
        nouveauNoeud->donnee = donnee;
        nouveauNoeud->suivant = NULL;
    }
    return nouveauNoeud;
}



void insererDebut(Noeud** tete, int donnee) {
    Noeud* nouveau = creerNoeud(donnee);
    if (nouveau == NULL) {
        printf("Erreur: impossible d'allouer de la mémoire\n");
        return;
    }
    nouveau->suivant = *tete;
    *tete = nouveau;
}

void insererFin(Noeud** tete, int donnee) {
    Noeud* nouveau = creerNoeud(donnee);
    if (nouveau == NULL) {
        printf("Erreur: impossible d'allouer de la mémoire\n");
        return;
    }
    if (*tete == NULL) {
        *tete = nouveau;
        return;
    }
    Noeud* actuel = *tete;
    while (actuel->suivant != NULL) {
        actuel = actuel->suivant;
    }
    actuel->suivant = nouveau;
}

void insererApres(Noeud* apres, int donnee) {
    if (apres == NULL) {
        printf("Erreur: le noeud spécifié est NULL\n");
        return;
    }
    Noeud* nouveau = creerNoeud(donnee);
    if (nouveau == NULL) {
        printf("Erreur: impossible d'allouer de la mémoire\n");
        return;
    }
    nouveau->suivant = apres->suivant;
    apres->suivant = nouveau;
}

void supprimerDebut(Noeud** tete) {
    if (*tete == NULL) {
        printf("Erreur: la liste est vide\n");
        return;
    }
    Noeud* temp = *tete;
    *tete = (*tete)->suivant;
    free(temp);
}

void supprimerFin(Noeud** tete) {
    if (*tete == NULL) {
        printf("Erreur: la liste est vide\n");
        return;
    }
    if ((*tete)->suivant == NULL) {
        free(*tete);
        *tete = NULL;
        return;
    }
    Noeud* actuel = *tete;
    Noeud* precedent = NULL;
    while (actuel->suivant != NULL) {
        precedent = actuel;
        actuel = actuel->suivant;
    }
    free(actuel);
    precedent->suivant = NULL;
}

void supprimerElement(Noeud** tete, int donnee) {
    Noeud* actuel = *tete;
    Noeud* precedent = NULL;
    while (actuel != NULL && actuel->donnee != donnee) {
        precedent = actuel;
        actuel = actuel->suivant;
    }
    if (actuel == NULL) {
        printf("Erreur: élément non trouvé\n");
        return;
    }
    if (precedent == NULL) {
        *tete = actuel->suivant;
    } else {
        precedent->suivant = actuel->suivant;
    }
    free(actuel);
}


void afficherListe(Noeud* tete) {
    Noeud* actuel = tete;
    while (actuel != NULL) {
        printf("%d -> ", actuel->donnee);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

int tailleListe(Noeud* tete) {
    int taille = 0;
    Noeud* actuel = tete;
    while (actuel != NULL) {
        taille++;
        actuel = actuel->suivant;
    }
    return taille;
}

int consulterElement(Noeud* tete, int index) {
    int i = 0;
    Noeud* actuel = tete;
    while (actuel != NULL && i < index) {
        actuel = actuel->suivant;
        i++;
    }
    if (actuel == NULL) {
        printf("Erreur: index hors limites\n");
        return -1; // ou une valeur spéciale pour indiquer une erreur
    } else {
        return actuel->donnee;
    }
}

void inverserListe(Noeud** tete) {
    Noeud* precedent = NULL;
    Noeud* actuel = *tete;
    Noeud* suivant = NULL;
    while (actuel != NULL) {
        suivant = actuel->suivant;
        actuel->suivant = precedent;
        precedent = actuel;
        actuel = suivant;
    }
    *tete = precedent;
}

void PurgerDoublons(struct Noeud** head)
{
    struct Noeud *ptr1, *ptr2, *dup;
    ptr1 = *head;

    while (ptr1 != NULL && ptr1->suivant != NULL) {
        ptr2 = ptr1;


        while (ptr2->suivant != NULL) {

            if (ptr1->donnee == ptr2->suivant->donnee) {
                dup = ptr2->suivant;
                ptr2->suivant = ptr2->suivant->suivant;
                free(dup);
            }
            else ptr2 = ptr2->suivant;
        }
        ptr1 = ptr1->suivant;
    }
}

void copierListe(struct Noeud* source, struct Noeud** destination) {
    struct Noeud* courant = source;
    while (courant != NULL) {
        insererFin(destination, courant->donnee);
        courant = courant->suivant;
    }
}

int main() {
    Noeud* liste = NULL;

    //qst :1  ajouter des élement à la liste
    insererDebut(&liste, 10);
    insererDebut(&liste, 20);
    insererFin(&liste, 30);
    insererFin(&liste, 40);
    insererFin(&liste, 50);
    insererFin(&liste, 60);


    //qst 8: copier la liste avant la modifier
    struct Noeud* listeCopiee = NULL;
    copierListe(liste, &listeCopiee);
    printf("Liste copiée : ");


    //qst4: taille de la liste
    printf("\n Taille de la liste : %d\n", tailleListe(liste));

    afficherListe(liste);

    supprimerDebut(&liste);
    afficherListe(liste);

    supprimerFin(&liste);
    afficherListe(liste);

    //qst 3: afficher la liste final
    supprimerElement(&liste, 30);
    afficherListe(liste);

    printf("\nTaille de la liste : %d\n", tailleListe(liste));

    //qst5: montre la valeur de l'index 2 qui est 50
    int index = 2;
    int valeur = consulterElement(liste, index);
    if (valeur != -1) {
        printf("Element a l'index %d : %d\n", index, valeur);
    }

    //qst6: afficher la liste avant et aprés l'inversion
    printf("Liste avant inversion: \t");
    afficherListe(liste);

    inverserListe(&liste);

    printf("Liste apres inversion:\t");
    afficherListe(liste);


    //qst1: ajouter une valeur aprés la premiere valeur de la liste chainé qui est 40 et l'afficher
    Noeud* noeudAInsererApres = liste->suivant;
    insererApres(noeudAInsererApres, 25);
    insererApres(noeudAInsererApres, 25);


    printf("Liste après insertion après:\n");
    afficherListe(liste);

    //qst7: afficher la liste aprés la supression les valeur doublée
    PurgerDoublons(&liste);
    printf("\nListe après suppression des doublons : ");
    afficherListe(liste);





    printf("\naffichage de la Liste avant la modifier par copier la premiere liste  au debut: \n ");
    afficherListe(listeCopiee);



    return 0;
}
