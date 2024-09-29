#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IntNode{                       // D�finir la structure pour les noeuds de la liste
	int data;                                // Donn�e enti�re stock�e dans le noeud
	struct IntNode *next;                    // Pointeur vers le prochain noeud
}IntNode;

// Fonction pour cr�er un nouveau noeud
IntNode* createNode(int data){
	IntNode* newNode = (IntNode*) malloc(sizeof(IntNode)); // Allouer de la m�moire pour le nouveau noeud
	if(newNode == NULL){                      // V�rifier si l'allocation m�moire a r�ussi
		printf("erreur allocation de memoire!!\n");
		exit(EXIT_FAILURE);                   // Terminer le programme si l'allocation �choue
	}
	newNode->data = data;                     // Initialiser la donn�e du noeud
	newNode->next = NULL;                     // Initialiser le pointeur suivant � NULL
	return newNode;                           // Retourner le nouveau noeud cr��
}


//1. Ins�rer un entier dans la liste
//   Nous avons d�j� vu des fonctions pour ins�rer des entiers au d�but et � la fin de la liste.
//   Voici comment vous pourriez ins�rer un entier apr�s un certain �l�ment sp�cifi� :


IntNode* insererApres(IntNode *head, int cible, int data) {
    IntNode *current = head;                                  // Initialiser le pointeur pour parcourir la liste
    while (current != NULL && current->data != cible) {       // Parcourir pour trouver le noeud cible
        current = current->next;                              // Avancer au prochain noeud
    }
    if (current != NULL) {                                    // V�rifier si le noeud cible a �t� trouv�
        IntNode *newNode = createNode(data);                  // Cr�er un nouveau noeud avec la donn�e sp�cifi�e
        newNode->next = current->next;                        // Faire pointer le nouveau noeud vers le suivant du noeud cible
        current->next = newNode;                              // Ins�rer le nouveau noeud apr�s le noeud cible
    }
    return head;                                              // Retourner la t�te de la liste
}

// 2. Supprimer un �l�ment de la liste
//    Nous avons �galement les fonctions pour supprimer le premier et le dernier �l�ment.
//    Voici comment supprimer un �l�ment sp�cifique :

void supprimerElement(IntNode **head, int data) {
    if (*head == NULL) {
        // La liste est vide, donc rien � supprimer
        return;
    }
    // Cas sp�cial si l'�l�ment � supprimer est � la t�te de la liste
    if ((*head)->data == data) {
        IntNode *aSupprimer = *head;             // Sauvegarder le noeud � supprimer
        *head = (*head)->next;                   // Avancer la t�te de la liste
        free(aSupprimer);                        // Lib�rer la m�moire de l'ancien noeud t�te
        return;
    }
    // Recherche de l'�l�ment � supprimer
    IntNode *current = *head;                   // Initialiser le pointeur pour parcourir la liste
    while (current->next != NULL && current->next->data != data) {
        current = current->next;                // Avancer dans la liste pour trouver l'�l�ment
    }
    // Supprimer l'�l�ment trouv�, s'il existe
    if (current->next != NULL) {
        IntNode *aSupprimer = current->next;    // Noeud � supprimer
        current->next = aSupprimer->next;       // Relier le noeud pr�c�dent au noeud suivant
        free(aSupprimer);                       // Lib�rer la m�moire du noeud supprim�
    }
	// Si l'�l�ment n'est pas trouv�, informer l'utilisateur
	else {
        printf("Element not found in the list.\n");
    }
}


// 4. Donner la taille de la liste

int tailleListe(IntNode *head) {
    int count = 0;                                   // Initialiser le compteur � z�ro
    IntNode *current = head;                         // Initialiser le pointeur pour parcourir la liste
    while (current != NULL) {
        count++;                                     // Incr�menter le compteur pour chaque �l�ment
        current = current->next;                     // Avancer au noeud suivant
    }
    return count;                                    // Retourner le nombre total d'�l�ments
}


// 5. Fonction pour consulter un �l�ment par index dans une liste simplement cha�n�e
// Note: cette fonction peut �tre utilis�e de mani�re similaire pour les listes doublement cha�n�es.
int getElement(IntNode *head, int index) {
    if (index < 0) {
        printf("Index invalide (n�gatif).\n");          // G�rer le cas d'un index n�gatif
        return -1;                                      // Retourner une valeur d'erreur pour index n�gatif
    }

    int count = 0;
    IntNode *current = head;                           // Initialiser le pointeur pour parcourir la liste
    while (current != NULL && count < index) {         // Parcourir la liste jusqu'� l'index souhait� ou la fin de la liste
        current = current->next;                       // Avancer au noeud suivant
        count++;                                       // Incr�menter le compteur d'index
    }

    if (current != NULL) {
        return current->data;                          // Retourner la valeur de l'�l�ment � l'index sp�cifi� si trouv�
    } else {
        printf("Index hors limites\n");                // Informer l'utilisateur si l'index est hors limites
        return -1;                                     // Retourner une valeur d'erreur si l'index est invalide
    }
}



// 7. Fonction pour purger les doublons dans la liste
// 7. Solution 1 :
IntNode* purgerListe(IntNode *head) {
    if (head == NULL || head->next == NULL) {
        return head;                                        // Retourner directement la liste si elle est vide ou contient un seul �l�ment
    }

    IntNode *tmp = head;
    while (tmp != NULL) {                               // Parcourir chaque �l�ment de la liste
        IntNode *cmp = tmp;                          // Initialiser cmp au noeud courant pour v�rifier les doublons suivants
        while (cmp->next != NULL) {                      // Tant qu'il reste des noeuds � v�rifier apr�s le cmp
            if (cmp->next->data == current->data) {      // V�rifier si le noeud suivant est un doublon
                IntNode *aSupprimer = cmp->next;         // Noeud � supprimer
                cmp->next = aSupprimer->next;            // �liminer le noeud doublon de la liste
                free(aSupprimer);                           // Lib�rer la m�moire du noeud doublon
            } else {
                cmp = cmp->next;                      // Avancer au prochain noeud si pas de doublon
            }
        }
        tmp = tmp->next;                            // Avancer au prochain noeud � v�rifier
    }
    return head;                                            // Retourner la t�te de la liste purg�e
}

// 7. Solution 2 (inspir�e de la m�thode du tri � bulle):

IntNode* purgerListe(IntNode *head) {
    if (head == NULL || head->next == NULL) {
        return head; // Pas besoin de purger si la liste est vide ou a un seul �l�ment
    }

    // Boucle externe : parcourt chaque �l�ment de la liste
    for (IntNode *tmp = head; tmp != NULL; tmp = tmp->next) {
        // Boucle interne : parcourt les �l�ments suivants tmp pour chercher et �liminer les doublons
        for (IntNode *cmp = tmp; cmp->next != NULL; ) {
            if (cmp->next->data == tmp->data) { // Si le noeud suivant est un doublon
                IntNode *aSupprimer = cmp->next; // Sauvegarder le noeud � supprimer
                cmp->next = aSupprimer->next;    // Supprimer le noeud doublon de la liste
                free(aSupprimer);                // Lib�rer la m�moire du noeud doublon
            } else {
                cmp = cmp->next; // Avancer au prochain noeud si pas de doublon
            }
        }
    }
    return head; // Retourner la t�te de la liste purg�e
}


// 8. Fonction pour copier la liste
IntNode* copierListe(IntNode *head) {
    IntNode *newHead = NULL;                             // Initialiser la nouvelle t�te de liste � NULL
    IntNode *current = head;                             // Utiliser current pour parcourir la liste originale

    while (current != NULL) {                            // Tant que le parcours de la liste originale n'est pas termin�
        newHead = insererFin(newHead, current->data);    // Ins�rer les donn�es de current � la fin de la nouvelle liste
        current = current->next;                         // Avancer au prochain n�ud dans la liste originale
    }
    return newHead;                                      // Retourner la nouvelle t�te de la liste copi�e
}










