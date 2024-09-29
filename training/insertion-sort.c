#include <stdio.h>
#include <stdlib.h>

struct Element { // Element instead of Noeud
  int data;
  struct Element* suivant; // suivant remains for clarity
};

// Fonction pour inserer un nouvel element au debut de la liste chainee
void insererEnTete(struct Element** tete_ref, int nouvelle_valeur) {
  struct Element* nouveau_element = (struct Element*)malloc(sizeof(struct Element));
  nouveau_element->data = nouvelle_valeur;
  nouveau_element->suivant = (*tete_ref);
  (*tete_ref) = nouveau_element;
}

// Fonction pour afficher la liste chainee
void afficherListe(struct Element* element) {
  while (element != NULL) {
    printf("%d ", element->data);
    element = element->suivant;
  }
  printf("\n");
}

// Fonction pour inserer un element trie dans une liste chainee
void insererTrie(struct Element** tete_ref, struct Element* nouveau_element) {
  struct Element* courant;
  if (*tete_ref == NULL || (*tete_ref)->data >= nouveau_element->data) {
    nouveau_element->suivant = *tete_ref;
    *tete_ref = nouveau_element;
  } else {
    courant = *tete_ref;
    while (courant->suivant != NULL && courant->suivant->data < nouveau_element->data) {
      courant = courant->suivant;
    }
    nouveau_element->suivant = courant->suivant;
    courant->suivant = nouveau_element;
  }
}

// Fonction pour trier la liste chainee en utilisant le tri par insertion
void triParInsertion(struct Element** tete_ref) {
  struct Element* triee = NULL;
  struct Element* courant = *tete_ref;

  // Parcourir la liste fournie et inserer chaque element dans la liste chainee triee
  while (courant != NULL) {
    // Stocker l'element suivant pour eviter de casser la liste d'origine
    struct Element* suivant = courant->suivant;

    // Inserer l'element courant de maniere triee
    insererTrie(&triee, courant);

    // Passer a l'element suivant
    courant = suivant;
  }

  // Mettre a jour la reference de la tete pour pointer vers la liste triee
  *tete_ref = triee;
}

int main() {
  struct Element* tete = NULL;
  insererEnTete(&tete, 5);
  insererEnTete(&tete, 20);
  insererEnTete(&tete, 4);
  insererEnTete(&tete, 10);

  printf("Liste chainee avant le tri: ");
  afficherListe(tete);

  triParInsertion(&tete);

  printf("Liste chainee apres le tri: ");
  afficherListe(tete);

  return 0;
}
