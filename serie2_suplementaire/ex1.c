#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un nœud dans la liste chaînée
struct Node {
    int data;
    struct Node* next;
};

// Fonction pour créer un nouveau nœud avec la donnée donnée
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Allocation mémoire a échoué\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour insérer un nouveau nœud au début de la liste
void insertAtBeginning(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *headRef;
    *headRef = newNode;
}

// Fonction pour insérer un nouveau nœud à la fin de la liste
void insertAtEnd(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    struct Node* current = *headRef;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Fonction pour afficher les éléments de la liste
void display(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour obtenir la taille de la liste
int getSize(struct Node* head) {
    int size = 0;
    struct Node* current = head;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

// Fonction pour consulter un élément de la liste en fonction de son index
int getElementAtIndex(struct Node* head, int index) {
    int i = 0;
    struct Node* current = head;
    while (current != NULL) {
        if (i == index) {
            return current->data;
        }
        i++;
        current = current->next;
    }
    printf("Index hors limites\n");
    exit(1);
}

// Fonction pour inverser le contenu de la liste
void reverseList(struct Node** headRef) {
    struct Node* prev = NULL;
    struct Node* current = *headRef;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *headRef = prev;
}

// Fonction pour purger les doublons de la liste
void purgeDuplicates(struct Node** headRef) {
    struct Node* current = *headRef;
    struct Node* temp = NULL;
    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

// Fonction pour copier la liste source dans une liste de destination
void copyList(struct Node* source, struct Node** destination) {
    struct Node* current = source;
    while (current != NULL) {
        insertAtEnd(destination, current->data);
        current = current->next;
    }
}

int main() {
    struct Node* head = NULL;

    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);

    printf("Liste initiale : ");
    display(head);

    printf("Taille de la liste : %d\n", getSize(head));

    int index = 1;
    printf("Element à l'index %d : %d\n", index, getElementAtIndex(head, index));

    reverseList(&head);
    printf("Liste inversée : ");
    display(head);

    purgeDuplicates(&head);
    printf("Liste après suppression des doublons : ");
    display(head);

    struct Node* copiedList = NULL;
    copyList(head, &copiedList);
    printf("Liste copiée : ");
    display(copiedList);

    return 0;
}
