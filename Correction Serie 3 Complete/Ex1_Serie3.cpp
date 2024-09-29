#include <stdio.h>
#include <stdlib.h>

// Structure pour un �l�ment de la liste
typedef struct Element{
	int valeur;
	struct Element *suivant;
}Element;


// Fonction pour ajouter un �l�ment au d�but d'une liste
void AjoutDebut(Element **head, int valeur){
	Element *newElement = (Element*) malloc(sizeof(Element));
	newElement->valeur = valeur;
	newElement->suivant = *head;
	*head = newElement;
}

// Fonction pour supprimer le premier �l�ment d'une liste
void suppDebut(Element *(*head)){
	if(*head == NULL){
		printf("la liste est vide aucun element a supprime !!! \n");
		return;
	}
	Element *temp = (*head);
	*head = (*head)->suivant;
	free(temp);	
}

// Fonction pour supprimer un �l�ment ayant une valeur sp�cifique dans la liste

void suppVal(Element **head, int valeurSupprimer) {
    if (*head == NULL) {                                                         // V�rifier si la liste est vide.
        printf("La liste est vide.\n");
        return;                                                                  // La liste est d�j� vide.
    }
    if ((*head)->valeur == valeurSupprimer) {                                    // V�rifier si la valeur � supprimer est dans le premier �l�ment.
        suppDebut(head);                                                         // Utilise suppDebut pour supprimer le premier �l�ment.
        return;
    }
    Element *current = *head;                                                    // Initialiser le pointeur courant pour parcourir la liste.
    while (current->suivant != NULL && current->suivant->valeur != valeurSupprimer) { // Parcourir la liste jusqu'� trouver l'�l�ment � supprimer.
        current = current->suivant;
    }
    if (current->suivant != NULL) {                                              // Si l'�l�ment � supprimer est trouv� (pas en fin de liste : current->suivant != NULL et current->suivant->valeur = valeurSupprimer),
        Element *temp = current->suivant;                                        // Temporairement stocker l'�l�ment � supprimer.
        current->suivant = current->suivant->suivant;                            // Retirer l'�l�ment de la liste.
        free(temp);                                                              // Lib�rer la m�moire de l'�l�ment supprim�.
    } else {                                                                     // Si l'�l�ment � supprimer n'est pas trouv� (on arrive � la fin de la liste : current->suivant = NULL et current->suivant->valeur != valeurSupprimer),
        printf("Element avec la valeur %d n'existe pas dans la liste.\n", valeurSupprimer); // Informer l'utilisateur que l'�l�ment n'existe pas.
    }
}


// Fonction pour trier une liste simplement cha�n�e en utilisant l'algorithme de tri par insertion.

void Tri_Insertion(Element **head) {                                          
    Element *listeTriee = NULL;                                               // Liste tri�e temporaire, initialement vide.
    Element *current;                                                         // Pointeur pour parcourir la liste.
    int max;                                                                  // Variable pour stocker le maximum trouv� dans la liste.
    while (*head != NULL) {                                                   // Continue tant que la liste originale n'est pas vide.
        current = *head;                                                      // Initialise current au d�but de la liste.
        max = current->valeur;                                                // Initialise max avec la valeur du premier �l�ment.
        while (current != NULL) {                                             // Parcourt toute la liste pour trouver le maximum.
            if (max < current->valeur) {                                      // Si un maximum plus grand est trouv�,
                max = current->valeur;                                        // met � jour le maximum.
            }
            current = current->suivant;                                       // Avance � l'�l�ment suivant dans la liste.
        }        
        AjoutDebut(&listeTriee, max);                                         // Ajoute le maximum trouv� au d�but de la nouvelle liste tri�e.
        suppVal(head, max);                                                   // Supprime le maximum de la liste originale.
    }   
    *head = listeTriee;                                                       // Remet les �l�ments tri�s dans la liste originale.
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

�tape 1 : 

Trouver le Maximum et Construire la Nouvelle Liste
On cherche le maximum dans la liste initiale, qui est 8.
On retire 8 de la liste initiale, qui devient maintenant [5, 3, 1, 2].
On ajoute 8 au d�but de la nouvelle liste, qui est pour l'instant [8].

�tape 2 : 

R�p�ter le Processus
On cherche le nouveau maximum dans la liste initiale, qui est 5.
On retire 5 de la liste initiale, qui devient [3, 1, 2].
On ajoute 5 au d�but de la nouvelle liste, qui devient [5, 8].

�tape 3
Maximum trouv� : 3
Liste initiale devient : [1, 2]
Nouvelle liste devient : [3, 5, 8]

�tape 4
Maximum trouv� : 2
Liste initiale devient : [1]
Nouvelle liste devient : [2, 3, 5, 8]

�tape 5
Maximum trouv� : 1
Liste initiale est maintenant vide.
Nouvelle liste devient : [1, 2, 3, 5, 8]*/
