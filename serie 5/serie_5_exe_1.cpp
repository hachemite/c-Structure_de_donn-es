#include <stdio.h>
#include <stdlib.h>

// Structure représentant un nœud de la liste
struct Node {
    int data;
    struct Node* next;
};

// Fonction pour créer un nouveau nœud avec la valeur spécifiée
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour insérer un nœud à la fin de la liste
void insertAtEnd(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
    if (*head == NULL) {
        // Si la liste est vide, le nouveau nœud devient la tête de liste
        *head = newNode;
    } else {
        // Sinon, on parcourt la liste jusqu'à la fin et on insère le nouveau nœud
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void supprimerElement(Node **head, int data) {
    if (*head == NULL) {
        // La liste est vide, donc rien à supprimer
        return;
    }
    // Cas spécial si l'élément à supprimer est à la tête de la liste
    if ((*head)->data == data) {
        Node *aSupprimer = *head;             // Sauvegarder le noeud à supprimer
        *head = (*head)->next;                   // Avancer la tête de la liste
        free(aSupprimer);                        // Libérer la mémoire de l'ancien noeud tête
        return;
    }
    // Recherche de l'élément à supprimer
    Node *current = *head;                   // Initialiser le pointeur pour parcourir la liste
    while (current->next != NULL && current->next->data != data) {
        current = current->next;                // Avancer dans la liste pour trouver l'élément
    }
    // Supprimer l'élément trouvé, s'il existe
    if (current->next != NULL) {
        Node *aSupprimer = current->next;    // Noeud à supprimer
        current->next = aSupprimer->next;       // Relier le noeud précédent au noeud suivant
        free(aSupprimer);                       // Libérer la mémoire du noeud supprimé
    }
	// Si l'élément n'est pas trouvé, informer l'utilisateur
	else {
        printf("Element not found in the list.\n");
    }
}



Node* purgerListe(Node *head) {
    if (head == NULL || head->next == NULL) {
        return head;                                        // Retourner directement la liste si elle est vide ou contient un seul élément
    }

    Node *tmp = head;
    while (tmp != NULL) {                               // Parcourir chaque élément de la liste
        Node *cmp = tmp;                          // Initialiser cmp au noeud courant pour vérifier les doublons suivants
        while (cmp->next != NULL) {                      // Tant qu'il reste des noeuds à vérifier après le cmp
            if (cmp->next->data == tmp->data) {      // Vérifier si le noeud suivant est un doublon
                Node *aSupprimer = cmp->next;         // Noeud à supprimer
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

// Fonction pour afficher les éléments de la liste
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

// Fonction pour rechercher un élément donné dans la liste
int searchList(struct Node* head, int key) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1; // L'élément a été trouvé
        }
        current = current->next;
    }
    return 0; // L'élément n'a pas été trouvé
}

int main() {
    struct Node* head = NULL;
    struct Node* head2 = NULL;


    // Construire la liste simplement chaînée avec les données fournies
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

    // Rechercher un élément spécifique dans la liste
    int searchKey = 7;
    int isFound = searchList(head, searchKey);

    // Afficher la liste résultante et le résultat de la recherche
    displayList(head);
    displayList(purgerListe(head));
    supprimerElement(&head,1);
    displayList(head);
    if (isFound) {
        printf("L'élément %d a été trouvé dans la liste.\n", searchKey);
    } else {
        printf("L'élément %d n'a pas été trouvé dans la liste.\n", searchKey);
    }

    return 0;
}
