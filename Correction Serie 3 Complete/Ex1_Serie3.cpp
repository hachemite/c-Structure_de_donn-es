#include <stdio.h>
#include <stdlib.h>

// Structure pour un élément de la liste
typedef struct Element{
	int valeur;
	struct Element *suivant;
}Element;


// Fonction pour ajouter un élément au début d'une liste
void AjoutDebut(Element **head, int valeur){
	Element *newElement = (Element*) malloc(sizeof(Element));
	newElement->valeur = valeur;
	newElement->suivant = *head;
	*head = newElement;
}

// Fonction pour supprimer le premier élément d'une liste
void suppDebut(Element *(*head)){
	if(*head == NULL){
		printf("la liste est vide aucun element a supprime !!! \n");
		return;
	}
	Element *temp = (*head);
	*head = (*head)->suivant;
	free(temp);	
}

// Fonction pour supprimer un élément ayant une valeur spécifique dans la liste

void suppVal(Element **head, int valeurSupprimer) {
    if (*head == NULL) {                                                         // Vérifier si la liste est vide.
        printf("La liste est vide.\n");
        return;                                                                  // La liste est déjà vide.
    }
    if ((*head)->valeur == valeurSupprimer) {                                    // Vérifier si la valeur à supprimer est dans le premier élément.
        suppDebut(head);                                                         // Utilise suppDebut pour supprimer le premier élément.
        return;
    }
    Element *current = *head;                                                    // Initialiser le pointeur courant pour parcourir la liste.
    while (current->suivant != NULL && current->suivant->valeur != valeurSupprimer) { // Parcourir la liste jusqu'à trouver l'élément à supprimer.
        current = current->suivant;
    }
    if (current->suivant != NULL) {                                              // Si l'élément à supprimer est trouvé (pas en fin de liste : current->suivant != NULL et current->suivant->valeur = valeurSupprimer),
        Element *temp = current->suivant;                                        // Temporairement stocker l'élément à supprimer.
        current->suivant = current->suivant->suivant;                            // Retirer l'élément de la liste.
        free(temp);                                                              // Libérer la mémoire de l'élément supprimé.
    } else {                                                                     // Si l'élément à supprimer n'est pas trouvé (on arrive à la fin de la liste : current->suivant = NULL et current->suivant->valeur != valeurSupprimer),
        printf("Element avec la valeur %d n'existe pas dans la liste.\n", valeurSupprimer); // Informer l'utilisateur que l'élément n'existe pas.
    }
}


// Fonction pour trier une liste simplement chaînée en utilisant l'algorithme de tri par insertion.

void Tri_Insertion(Element **head) {                                          
    Element *listeTriee = NULL;                                               // Liste triée temporaire, initialement vide.
    Element *current;                                                         // Pointeur pour parcourir la liste.
    int max;                                                                  // Variable pour stocker le maximum trouvé dans la liste.
    while (*head != NULL) {                                                   // Continue tant que la liste originale n'est pas vide.
        current = *head;                                                      // Initialise current au début de la liste.
        max = current->valeur;                                                // Initialise max avec la valeur du premier élément.
        while (current != NULL) {                                             // Parcourt toute la liste pour trouver le maximum.
            if (max < current->valeur) {                                      // Si un maximum plus grand est trouvé,
                max = current->valeur;                                        // met à jour le maximum.
            }
            current = current->suivant;                                       // Avance à l'élément suivant dans la liste.
        }        
        AjoutDebut(&listeTriee, max);                                         // Ajoute le maximum trouvé au début de la nouvelle liste triée.
        suppVal(head, max);                                                   // Supprime le maximum de la liste originale.
    }   
    *head = listeTriee;                                                       // Remet les éléments triés dans la liste originale.
}


// Fonction pour afficher le contenu d'une liste

void afficherListe(Element *head) {
    Element *current = head;
    while (current != NULL) {
        printf("%d ", current->valeur);
        current = current->suivant;
    }
}

void libererListe(Element **head) {
    Element *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->suivant;
        free(temp);
    }
}

int main() {
    Element *liste = NULL;
    AjoutDebut(&liste, 2);
    AjoutDebut(&liste, 1);
    AjoutDebut(&liste, 8);
    AjoutDebut(&liste, 3);
    AjoutDebut(&liste, 5);

    printf("Liste avant tri : ");
    afficherListe(liste);

    Tri_Insertion(&liste);

    printf("Liste apres tri : ");
    afficherListe(liste);

    libererListe(&liste);

    return 0;
}







/*Liste Initiale
Supposons que notre liste initiale soit : [5, 3, 8, 1, 2]

Étape 1 : 

Trouver le Maximum et Construire la Nouvelle Liste
On cherche le maximum dans la liste initiale, qui est 8.
On retire 8 de la liste initiale, qui devient maintenant [5, 3, 1, 2].
On ajoute 8 au début de la nouvelle liste, qui est pour l'instant [8].

Étape 2 : 

Répéter le Processus
On cherche le nouveau maximum dans la liste initiale, qui est 5.
On retire 5 de la liste initiale, qui devient [3, 1, 2].
On ajoute 5 au début de la nouvelle liste, qui devient [5, 8].

Étape 3
Maximum trouvé : 3
Liste initiale devient : [1, 2]
Nouvelle liste devient : [3, 5, 8]

Étape 4
Maximum trouvé : 2
Liste initiale devient : [1]
Nouvelle liste devient : [2, 3, 5, 8]

Étape 5
Maximum trouvé : 1
Liste initiale est maintenant vide.
Nouvelle liste devient : [1, 2, 3, 5, 8]*/
