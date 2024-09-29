#include <stdio.h>
#include <stdlib.h>

// Structure repr�sentant un n�ud de la liste doublement cha�n�e
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Fonction pour cr�er un nouveau n�ud avec la valeur sp�cifi�e
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->prev = NULL;
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
        newNode->prev = current;
    }
}

// Fonction pour afficher les �l�ments de la liste
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

    // Construire la liste doublement cha�n�e avec les donn�es fournies
    insertAtEnd(&head, 6);
    insertAtEnd(&head, 8);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 9);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 7);
    insertAtEnd(&head, 5);

    // Afficher la liste r�sultante
    displayList(head);

    return 0;
}
