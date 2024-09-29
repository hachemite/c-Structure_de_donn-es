#include <stdio.h>
#include <stdlib.h>

// Structure représentant un nœud de la liste doublement chaînée
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Fonction pour créer un nouveau nœud avec la valeur spécifiée
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
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
        newNode->prev = current;
    }
}

// Fonction pour afficher les éléments de la liste
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        if (current->next != NULL) {
            printf("<--> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;

    // Construire la liste doublement chaînée avec les données fournies
    insertAtEnd(&head, 6);
    insertAtEnd(&head, 8);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 9);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 7);
    insertAtEnd(&head, 5);

    // Afficher la liste résultante
    displayList(head);

    return 0;
}
