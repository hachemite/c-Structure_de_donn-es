#include <stdio.h>
#include <stdlib.h>

struct Noeud {
  int valeur;
  struct Noeud *suivant;
};

// Fonction pour afficher la liste
void afficher_liste(struct Noeud *tete) {
  while (tete != NULL) {
    printf("%d ", tete->valeur);
    tete = tete->suivant;
  }
  printf("\n");
}

// Fonction pour trouver le noeud du milieu
struct Noeud* trouver_milieu(struct Noeud *tete) {
  if (tete == NULL || tete->suivant == NULL) {
    return tete;
  }
  struct Noeud *lent = tete;
  struct Noeud *rapide = tete->suivant;
  while (rapide != NULL && rapide->suivant != NULL) {
    lent = lent->suivant;
    rapide = rapide->suivant->suivant;
  }
  return lent;
}

// Fonction de tri fusion récursive
struct Noeud* tri_fusion(struct Noeud *tete) {
  if (tete == NULL || tete->suivant == NULL) {
    return tete;
  }
  struct Noeud *milieu = trouver_milieu(tete);
  struct Noeud *droite = milieu->suivant;
  milieu->suivant = NULL; // Temporairement séparer les listes

  struct Noeud *gauche = tri_fusion(tete);
  droite = tri_fusion(droite);

  return fusionner(gauche, droite);
}

// Fonction pour fusionner deux listes triées
struct Noeud* fusionner(struct Noeud *gauche, struct Noeud *droite) {
  struct Noeud *resultat = NULL;
  if (gauche == NULL) {
    return droite;
  } else if (droite == NULL) {
    return gauche;
  }

  if (gauche->valeur <= droite->valeur) {
    resultat = gauche;
    gauche = gauche->suivant;
  } else {
    resultat = droite;
    droite = droite->suivant;
  }

  struct Noeud *temp = resultat;
  while (gauche != NULL && droite != NULL) {
    if (gauche->valeur <= droite->valeur) {
      temp->suivant = gauche;
      gauche = gauche->suivant;
    } else {
      temp->suivant = droite;
      droite = droite->suivant;
    }
    temp = temp->suivant;
  }

  if (gauche != NULL) {
    temp->suivant = gauche;
  } else if (droite != NULL) {
    temp->suivant = droite;
  }

  return resultat;
}

int main() {
  // Créer la liste
  struct Noeud *n1 = malloc(sizeof(struct Noeud));
  n1->valeur = 5;
  n1->suivant = malloc(sizeof(struct Noeud));

  struct Noeud *n2 = n1->suivant;
  n2->valeur = 2;
  n2->suivant = malloc(sizeof(struct Noeud));

  struct Noeud *n3 = n2->suivant;
  n3->valeur = 4;
  n3->suivant = malloc(sizeof(struct Noeud));

  struct Noeud *n4 = n3->suivant;
  n4->valeur = 6;
  n4->suivant = malloc(sizeof(struct Noeud));

  struct Noeud *n5 = n4->suivant;
  n5->valeur = 1;
  n5->suivant = malloc(sizeof(struct Noeud));

  struct Noeud *n6 = n5->suivant;
  n6->valeur = 3;
  n6->suivant = NULL;

  // Afficher la liste avant le tri
  printf("Liste avant le tri: ");
  afficher_liste(n1);

  // Tri fusion
  struct Noeud *tete_triee = tri_fusion(n1);

  // Afficher la liste après le tri
  printf("Liste après le tri: ");
  afficher_liste(
