#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter un nœud de la liste
typedef struct Node {
    int data; // Donnée stockée dans le nœud
    struct Node *next; // Pointeur vers le nœud suivant
} Node;

// Fonction pour insérer un nouvel élément au début de la liste
void insertAtBeginning(Node **head, int newData) {
    Node *newNode = (Node *)malloc(sizeof(Node)); // Allouer de la mémoire pour le nouveau nœud
    if (newNode == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = newData; // Affecter la nouvelle donnée
    newNode->next = *head; // Mettre le nouveau nœud au début de la liste
    *head = newNode;
    printf("Nouvel élément inséré au début de la liste.\n");
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
    Node *head = NULL; // Initialiser la liste comme étant vide
    int choice, data;

    do {
        // Afficher le menu
        printf("\nMenu :\n");
        printf("1. Insérer un nouvel élément au début de la liste\n");
        printf("2. Afficher le contenu de la liste\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Entrez la donnée du nouvel élément : ");
                scanf("%d", &data);
                insertAtBeginning(&head, data); // Insérer un nouvel élément au début de la liste
                break;
            case 2:
                displayList(head); // Afficher le contenu de la liste
                break;
            case 3:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 3);

    // Libérer la mémoire allouée pour la liste
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

