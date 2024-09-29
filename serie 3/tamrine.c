#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure de données pour stocker les informations d'un matériel
struct materiel {
    int id;
    char nom[50];
    float prix;
    int quantite;
    struct materiel *precedent;
    struct materiel *suivant;
};

// Structure de la liste doublement chaînée pour stocker les matériels
struct liste {
    struct materiel *debut;
    struct materiel *fin;
    int taille;
};

// Initialise une liste vide
void initialiser_liste(struct liste *lst) {
    lst->debut = NULL;
    lst->fin = NULL;
    lst->taille = 0;
}

// Insère un élément au début de la liste
void inserer_debut(struct liste *lst, struct materiel *m) {
    m->precedent = NULL;
    m->suivant = lst->debut;
    if (lst->debut != NULL) {
        lst->debut->precedent = m;
    } else {
        lst->fin = m;
    }
    lst->debut = m;
    lst->taille++;
}

// Insère un élément à la fin de la liste
void inserer_fin(struct liste *lst, struct materiel *m) {
    m->suivant = NULL;
    m->precedent = lst->fin;
    if (lst->fin != NULL) {
        lst->fin->suivant = m;
    } else {
        lst->debut = m;
    }
    lst->fin = m;
    lst->taille++;
}

// Affiche les éléments de la liste
void afficher_liste(struct liste *lst) {
    struct materiel *m = lst->debut;
    while (m != NULL) {
        printf("ID: %d, Nom: %s, Prix: %.2f, Quantité: %d\n", m->id, m->nom, m->prix, m->quantite);
        m = m->suivant;
    }
}

// Ajoute un nouveau matériel à la liste
void ajouter_materiel(struct liste *lst, struct materiel *m) {
    inserer_fin(lst, m);
}

// Modifie un matériel existant dans la liste
void modifier_materiel(struct liste *lst, int id) {
    struct materiel *m = lst->debut;
    while (m != NULL) {
        if (m->id == id) {
            printf("Nouveau nom pour le matériel avec l'ID %d : ", id);
            scanf("%s", m->nom);
            printf("Nouveau prix pour le matériel avec l'ID %d : ", id);
            scanf("%f", &(m->prix));
            printf("Nouvelle quantité pour le matériel avec l'ID %d : ", id);
            scanf("%d", &(m->quantite));
            break;
        }
        m = m->suivant;
    }
}

// Supprime un matériel de la liste
void supprimer_materiel(struct liste *lst, int id) {
    struct materiel *m = lst->debut;
    while (m != NULL) {
        if (m->id == id) {
            if (m->precedent != NULL) {
                m->precedent->suivant = m->suivant;
            } else {
                lst->debut = m->suivant;
            }
            if (m->suivant != NULL) {
                m->suivant->precedent = m->precedent;
            } else {
                lst->fin = m->precedent;
            }
            free(m);
            lst->taille--;
            break;
        }
        m = m->suivant;
    }
}

// Recherche un matériel dans la liste par son identifiant
struct materiel* rechercher_materiel(struct liste *lst, int id) {
    struct materiel *m = lst->debut;
    while (m != NULL) {
        if (m->id == id) {
            return m;
        }
        m = m->suivant;
    }
    return NULL;
}

int main() {
    struct liste lst;
    initialiser_liste(&lst);

    // Exemple d'utilisation
    struct materiel m1 = {1, "Stylo", 1.5, 100, NULL, NULL};
    struct materiel m2 = {2, "Cahier", 3.0, 50, NULL, NULL};
    struct materiel m3 = {3, "Crayon", 0.5, 200, NULL, NULL};

    ajouter_materiel(&lst, &m1);
    ajouter_materiel(&lst, &m2);
    ajouter_materiel(&lst, &m3);

    printf("Liste des matériels :\n");
    afficher_liste(&lst);

    int id = 2;
    printf("\nRecherche du matériel avec l'ID %d :\n", id);
    struct materiel *m = rechercher_materiel(&lst, id);
    if (m != NULL) {
        printf("ID: %d, Nom: %s, Prix: %.2f, Quantité: %d\n", m->id, m->nom, m->prix, m->quantite);
    } else {
        printf("Matériel non trouvé.\n");
    }

    printf("\nModification du matériel avec l'ID %d :\n", id);
    modifier_materiel(&lst, id);
    afficher_liste(&lst);

    printf("\nSuppression du matériel avec l'ID %d :\n", id);
    supprimer_materiel(&lst, id);
    afficher_liste(&lst);

    return 0;
}
