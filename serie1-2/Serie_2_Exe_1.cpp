#include <stdio.h>
#include <stdlib.h>

// Structure pour repr�senter un n�ud de la liste
typedef struct Node {
    int data; // Donn�e stock�e dans le n�ud
    struct Node *next; // Pointeur vers le n�ud suivant
} Node;

// Fonction pour ins�rer un nouvel �l�ment au d�but de la liste
void insertAtBeginning(Node **head, int newData) {
    Node *newNode = (Node *)malloc(sizeof(Node)); // Allouer de la m�moire pour le nouveau n�ud
    if (newNode == NULL) {
        printf("Erreur d'allocation m�moire.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = newData; // Affecter la nouvelle donn�e
    newNode->next = *head; // Mettre le nouveau n�ud au d�but de la liste
    *head = newNode;
    printf("Nouvel �l�ment ins�r� au d�but de la liste.\n");
}

// Fonction pour afficher le contenu de la liste
void displayList(Node *head) {
    if (head == NULL) {
        printf("La liste est vide.\n");
        return;
    }
    printf("Contenu de la liste : ");
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL; // Initialiser la liste comme �tant vide
    int choice, data;

    do {
        // Afficher le menu
        printf("\nMenu :\n");
        printf("1. Ins�rer un nouvel �l�ment au d�but de la liste\n");
        printf("2. Afficher le contenu de la liste\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Entrez la donn�e du nouvel �l�ment : ");
                scanf("%d", &data);
                insertAtBeginning(&head, data); // Ins�rer un nouvel �l�ment au d�but de la liste
                break;
            case 2:
                displayList(head); // Afficher le contenu de la liste
                break;
            case 3:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choice != 3);

    // Lib�rer la m�moire allou�e pour la liste
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

