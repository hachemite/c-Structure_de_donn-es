#include <stdio.h>
#include <stdlib.h>

// Structure repr�sentant un n�ud de la liste
struct Node {
    int data;
    struct Node* next;
};

// Fonction pour cr�er un nouveau n�ud avec la valeur sp�cifi�e
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour ins�rer un n�ud � la fin de la liste
void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        // Si la liste est vide, le nouveau n�ud devient la t�te de liste
        *head = newNode;
    } else {
        // Sinon, on parcourt la liste jusqu'� la fin et on ins�re le nouveau n�ud
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void supprimerElement(Node **head, int data) {
    if (*head == NULL) {
        // La liste est vide, donc rien � supprimer
        return;
    }
    // Cas sp�cial si l'�l�ment � supprimer est � la t�te de la liste
    if ((*head)->data == data) {
        Node *aSupprimer = *head;             // Sauvegarder le noeud � supprimer
        *head = (*head)->next;                   // Avancer la t�te de la liste
        free(aSupprimer);                        // Lib�rer la m�moire de l'ancien noeud t�te
        return;
    }
    // Recherche de l'�l�ment � supprimer
    Node *current = *head;                   // Initialiser le pointeur pour parcourir la liste
    while (current->next != NULL && current->next->data != data) {
        current = current->next;                // Avancer dans la liste pour trouver l'�l�ment
    }
    // Supprimer l'�l�ment trouv�, s'il existe
    if (current->next != NULL) {
        Node *aSupprimer = current->next;    // Noeud � supprimer
        current->next = aSupprimer->next;       // Relier le noeud pr�c�dent au noeud suivant
        free(aSupprimer);                       // Lib�rer la m�moire du noeud supprim�
    }
	// Si l'�l�ment n'est pas trouv�, informer l'utilisateur
	else {
        printf("Element not found in the list.\n");
    }
}



Node* purgerListe(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;                                        // Retourner directement la liste si elle est vide ou contient un seul �l�ment
    }

    Node *tmp = head;
    while (tmp != NULL) {                               // Parcourir chaque �l�ment de la liste
        Node *cmp = tmp;                          // Initialiser cmp au noeud courant pour v�rifier les doublons suivants
        while (cmp->next != NULL) {                      // Tant qu'il reste des noeuds � v�rifier apr�s le cmp
            if (cmp->next->data == tmp->data) {      // V�rifier si le noeud suivant est un doublon
                Node *aSupprimer = cmp->next;         // Noeud � supprimer
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

// Fonction pour afficher les �l�ments de la liste
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Fonction pour trier la liste dans l'ordre croissant
void sortList(struct Node** head) {
    struct Node* current = *head;
    struct Node* index = NULL;
    int temp;

    if (*head == NULL) {
        return;
    } else {
        while (current != NULL) {
            index = current->next;
            while (index != NULL) {
                if (current->data > index->data) {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }
}

// Fonction pour rechercher un �l�ment donn� dans la liste
int searchList(struct Node* head, int key) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1; // L'�l�ment a �t� trouv�
        }
        current = current->next;
    }
    return 0; // L'�l�ment n'a pas �t� trouv�
}

int main() {
    struct Node* head = NULL;
    struct Node* head2 = NULL;


    // Construire la liste simplement cha�n�e avec les donn�es fournies
    insertAtEnd(&head, 6);
    insertAtEnd(&head, 8);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 9);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 8);
    insertAtEnd(&head, 7);
    insertAtEnd(&head, 5);
    insertAtEnd(&head, 9);


    insertAtEnd(&head2, 8);
    insertAtEnd(&head2, 3);
    insertAtEnd(&head2, 1);
    insertAtEnd(&head2, 4);
    insertAtEnd(&head2, 9);
    insertAtEnd(&head2, 2);
    insertAtEnd(&head2, 7);
    insertAtEnd(&head2, 5);


    // Trier la liste
    sortList(&head);

    // Rechercher un �l�ment sp�cifique dans la liste
    int searchKey = 7;
    int isFound = searchList(head, searchKey);

    // Afficher la liste r�sultante et le r�sultat de la recherche
    displayList(head);
    displayList(purgerListe(head));
    supprimerElement(&head,1);
    displayList(head);
    if (isFound) {
        printf("L'�l�ment %d a �t� trouv� dans la liste.\n", searchKey);
    } else {
        printf("L'�l�ment %d n'a pas �t� trouv� dans la liste.\n", searchKey);
    }

    return 0;
}
