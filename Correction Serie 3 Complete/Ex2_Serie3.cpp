#include <stdio.h>
#include <stdlib.h>

// Structure d'un �l�ment de la liste cha�n�e.

typedef struct Element {
    int donnee; 
    struct Element *suivant; 
} Element;


// Fonction pour �changer les valeurs entre deux �l�ments de la liste.

void permuteValeur(Element *elt1, Element *elt2) {          
    int temp = elt1->donnee;                             // Stocker temporairement la valeur de elt1 dans temp.
    elt1->donnee = elt2->donnee;                         // Copier la valeur de elt2 dans elt1.
    elt2->donnee = temp;                                 // Restaurer la valeur stock�e de elt1 dans elt2.
}

// Fonction pour trier une liste cha�n�e par tri rapide.

Element* quicksort(Element *head, Element *tail) {                  

    if (head == NULL || head == tail) {                             // Cas de base : si la liste est vide ou ne contient qu'un seul �l�ment.
        return head;
    }
    Element *pivot = head;                                          // Choisir le pivot comme le premier �l�ment de la liste.
    Element *current = head->suivant;                               // Initialiser le pointeur pour parcourir la liste, en commen�ant par l'�l�ment apr�s le pivot.
    Element *last_smaller = NULL;                                   // Pointeur pour suivre le dernier �l�ment plus petit que le pivot.

    while (current != NULL) {           
        if (current->donnee < pivot->donnee) {                      // Si l'�l�ment courant est plus petit que le pivot.
            last_smaller = (last_smaller == NULL) ? head->suivant : last_smaller->suivant; // Mettre � jour last_smaller.
            permuteValeur(current, last_smaller);                   // Et permuter la valeur de l'�l�ment courant avec last_smaller.
        }
        current = current->suivant;                                 // Passer � l'�l�ment suivant dans la liste.
    }
    
    if (last_smaller == NULL) {                                    // Si aucun �l�ment plus petit que le pivot n'a �t� trouv�, last_smaller reste au pivot qui est �gale au head dans notre cas.
        last_smaller = head;
    } else {
        permuteValeur(pivot, last_smaller);                        // Sinon, placer le pivot � sa position correcte en permutant avec last_smaller.      
    }
    quicksort(head, last_smaller);                                 // Appliquer r�cursivement le tri rapide � la sous-liste des �l�ments plus petits.
    quicksort(last_smaller->suivant, tail);                        // Appliquer r�cursivement le tri rapide � la sous-liste des �l�ments plus grands.

    return head;                                                   // Retourner le pointeur vers la t�te de la liste tri�e.
}


// Fonction pour afficher les �l�ments de la liste.
void afficherListe(Element *head) {
    Element *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->donnee);
        temp = temp->suivant;
    }
}

// Fonction pour lib�rer la m�moire allou�e � la liste.
void libererListe(Element **head) {
    Element *current = *head;
    while (current != NULL) {
        Element *next = current->suivant;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Fonction pour ajouter un �l�ment � la fin de la liste. Utile pour construire la liste initiale dans la fonction principale.
void ajouterFin(Element **head, int valeur) {
    Element *nouveau = (Element*)malloc(sizeof(Element));
    nouveau->donnee = valeur;
    nouveau->suivant = NULL;

    if (*head == NULL) {
        *head = nouveau;
    } 
	else {
        Element *current = *head;
        while (current->suivant != NULL) {
            current = current->suivant;
        }
        current->suivant = nouveau;
    }
}

int main() {
    Element *head = NULL;

    // Construire la liste [5, 3, 8, 1, 2]
    ajouterFin(&head, 5);
    ajouterFin(&head, 3);
    ajouterFin(&head, 8);
    ajouterFin(&head, 1);
    ajouterFin(&head, 2);

    printf("Liste avant le tri : ");
    afficherListe(head);

    // Trouver le dernier �l�ment de la liste pour le passer � quicksort. Sinon, donnez � tail la valeur NULL ; dans tous les cas, �a va marcher.
    Element *current = head;
    while (current->suivant != NULL) {
        current = current->suivant;
    }
    Element *tail = current;
    
    // Appliquer le tri rapide
    head= quicksort(head, tail);              //   ou utilisez simplement: head= quicksort(head, NULL); 

    printf("Liste apres le tri : ");
    afficherListe(head);

    libererListe(&head);

    return 0;
}
