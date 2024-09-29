#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IntNode{                       // Définir la structure pour les noeuds de la liste
	int data;                                // Donnée entière stockée dans le noeud
	struct IntNode *next;                    // Pointeur vers le prochain noeud
}IntNode;

// Fonction pour créer un nouveau noeud
IntNode* createNode(int data){
	IntNode* newNode = (IntNode*) malloc(sizeof(IntNode)); // Allouer de la mémoire pour le nouveau noeud
	if(newNode == NULL){                      // Vérifier si l'allocation mémoire a réussi
		printf("erreur allocation de memoire!!\n");
		exit(EXIT_FAILURE);                   // Terminer le programme si l'allocation échoue
	}
	newNode->data = data;                     // Initialiser la donnée du noeud
	newNode->next = NULL;                     // Initialiser le pointeur suivant à NULL
	return newNode;                           // Retourner le nouveau noeud créé
}


//1. Insérer un entier dans la liste
//   Nous avons déjà vu des fonctions pour insérer des entiers au début et à la fin de la liste.
//   Voici comment vous pourriez insérer un entier après un certain élément spécifié :


IntNode* insererApres(IntNode *head, int cible, int data) {
    IntNode *current = head;                                  // Initialiser le pointeur pour parcourir la liste
    while (current != NULL && current->data != cible) {       // Parcourir pour trouver le noeud cible
        current = current->next;                              // Avancer au prochain noeud
    }
    if (current != NULL) {                                    // Vérifier si le noeud cible a été trouvé
        IntNode *newNode = createNode(data);                  // Créer un nouveau noeud avec la donnée spécifiée
        newNode->next = current->next;                        // Faire pointer le nouveau noeud vers le suivant du noeud cible
        current->next = newNode;                              // Insérer le nouveau noeud après le noeud cible
    }
    return head;                                              // Retourner la tête de la liste
}

// 2. Supprimer un élément de la liste
//    Nous avons également les fonctions pour supprimer le premier et le dernier élément.
//    Voici comment supprimer un élément spécifique :

void supprimerElement(IntNode **head, int data) {
    if (*head == NULL) {
        // La liste est vide, donc rien à supprimer
        return;
    }
    // Cas spécial si l'élément à supprimer est à la tête de la liste
    if ((*head)->data == data) {
        IntNode *aSupprimer = *head;             // Sauvegarder le noeud à supprimer
        *head = (*head)->next;                   // Avancer la tête de la liste
        free(aSupprimer);                        // Libérer la mémoire de l'ancien noeud tête
        return;
    }
    // Recherche de l'élément à supprimer
    IntNode *current = *head;                   // Initialiser le pointeur pour parcourir la liste
    while (current->next != NULL && current->next->data != data) {
        current = current->next;                // Avancer dans la liste pour trouver l'élément
    }
    // Supprimer l'élément trouvé, s'il existe
    if (current->next != NULL) {
        IntNode *aSupprimer = current->next;    // Noeud à supprimer
        current->next = aSupprimer->next;       // Relier le noeud précédent au noeud suivant
        free(aSupprimer);                       // Libérer la mémoire du noeud supprimé
    }
	// Si l'élément n'est pas trouvé, informer l'utilisateur
	else {
        printf("Element not found in the list.\n");
    }
}


// 4. Donner la taille de la liste

int tailleListe(IntNode *head) {
    int count = 0;                                   // Initialiser le compteur à zéro
    IntNode *current = head;                         // Initialiser le pointeur pour parcourir la liste
    while (current != NULL) {
        count++;                                     // Incrémenter le compteur pour chaque élément
        current = current->next;                     // Avancer au noeud suivant
    }
    return count;                                    // Retourner le nombre total d'éléments
}


// 5. Fonction pour consulter un élément par index dans une liste simplement chaînée
// Note: cette fonction peut être utilisée de manière similaire pour les listes doublement chaînées.
int getElement(IntNode *head, int index) {
    if (index < 0) {
        printf("Index invalide (négatif).\n");          // Gérer le cas d'un index négatif
        return -1;                                      // Retourner une valeur d'erreur pour index négatif
    }

    int count = 0;
    IntNode *current = head;                           // Initialiser le pointeur pour parcourir la liste
    while (current != NULL && count < index) {         // Parcourir la liste jusqu'à l'index souhaité ou la fin de la liste
        current = current->next;                       // Avancer au noeud suivant
        count++;                                       // Incrémenter le compteur d'index
    }

    if (current != NULL) {
        return current->data;                          // Retourner la valeur de l'élément à l'index spécifié si trouvé
    } else {
        printf("Index hors limites\n");                // Informer l'utilisateur si l'index est hors limites
        return -1;                                     // Retourner une valeur d'erreur si l'index est invalide
    }
}



// 7. Fonction pour purger les doublons dans la liste
// 7. Solution 1 :
IntNode* purgerListe(IntNode *head) {
    if (head == NULL || head->next == NULL) {
        return head;                                        // Retourner directement la liste si elle est vide ou contient un seul élément
    }

    IntNode *tmp = head;
    while (tmp != NULL) {                               // Parcourir chaque élément de la liste
        IntNode *cmp = tmp;                          // Initialiser cmp au noeud courant pour vérifier les doublons suivants
        while (cmp->next != NULL) {                      // Tant qu'il reste des noeuds à vérifier après le cmp
            if (cmp->next->data == current->data) {      // Vérifier si le noeud suivant est un doublon
                IntNode *aSupprimer = cmp->next;         // Noeud à supprimer
                cmp->next = aSupprimer->next;            // Éliminer le noeud doublon de la liste
                free(aSupprimer);                           // Libérer la mémoire du noeud doublon
            } else {
                cmp = cmp->next;                      // Avancer au prochain noeud si pas de doublon
            }
        }
        tmp = tmp->next;                            // Avancer au prochain noeud à vérifier
    }
    return head;                                            // Retourner la tête de la liste purgée
}

// 7. Solution 2 (inspirée de la méthode du tri à bulle):

IntNode* purgerListe(IntNode *head) {
    if (head == NULL || head->next == NULL) {
        return head; // Pas besoin de purger si la liste est vide ou a un seul élément
    }

    // Boucle externe : parcourt chaque élément de la liste
    for (IntNode *tmp = head; tmp != NULL; tmp = tmp->next) {
        // Boucle interne : parcourt les éléments suivants tmp pour chercher et éliminer les doublons
        for (IntNode *cmp = tmp; cmp->next != NULL; ) {
            if (cmp->next->data == tmp->data) { // Si le noeud suivant est un doublon
                IntNode *aSupprimer = cmp->next; // Sauvegarder le noeud à supprimer
                cmp->next = aSupprimer->next;    // Supprimer le noeud doublon de la liste
                free(aSupprimer);                // Libérer la mémoire du noeud doublon
            } else {
                cmp = cmp->next; // Avancer au prochain noeud si pas de doublon
            }
        }
    }
    return head; // Retourner la tête de la liste purgée
}


// 8. Fonction pour copier la liste
IntNode* copierListe(IntNode *head) {
    IntNode *newHead = NULL;                             // Initialiser la nouvelle tête de liste à NULL
    IntNode *current = head;                             // Utiliser current pour parcourir la liste originale

    while (current != NULL) {                            // Tant que le parcours de la liste originale n'est pas terminé
        newHead = insererFin(newHead, current->data);    // Insérer les données de current à la fin de la nouvelle liste
        current = current->next;                         // Avancer au prochain nœud dans la liste originale
    }
    return newHead;                                      // Retourner la nouvelle tête de la liste copiée
}










