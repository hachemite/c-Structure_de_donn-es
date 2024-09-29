#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

float calculateAverage(Node* head) {
    Node* current = head;
    int sum = 0;
    int count = 0;
    while (current != NULL) {
        sum += current->data;
        count++;
        current = current->next;
    }
    return (float)sum / count;
}

Node* squareList(Node* head) {
    Node* current = head;
    Node* result = NULL;
    while (current != NULL) {
        insertAtBeginning(&result, current->data * current->data);
        current = current->next;
    }
    return result;
}

char* findLongestWord(Node* head) {
    Node* current = head;
    char* longestWord = "";
    while (current != NULL) {
        if (strlen(longestWord) < strlen((char*)current->data)) {
            longestWord = (char*)current->data;
        }
        current = current->next;
    }
    return longestWord;
}

void removeFirstElement(Node** head) {
    if (*head != NULL) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void removeLastElement(Node* head) {
    Node* current = head;
    if (current == NULL) {
        return;
    }
    if (current->next == NULL) {
        free(current);
        return;
    }
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

Node* concatenateLists(Node* list1, Node* list2) {
    Node* current = list1;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = list2;
    return list1;
}

int main() {
    Node* list = NULL;

    // Création d'une liste décroissante des 10 premiers entiers
    for (int i = 10; i > 0; i--) {
        insertAtBeginning(&list, i);
    }

    // Affichage de la liste
    printf("Liste initiale : ");
    printList(list);

    // Calcul de la moyenne des éléments de la liste
    float average = calculateAverage(list);
    printf("Moyenne des éléments : %.2f\n", average);

    // Création d'une liste contenant les carrés des éléments de la liste initiale
    Node* squaredList = squareList(list);
    printf("Liste des carrés : ");
    printList(squaredList);

    // Recherche du mot le plus long dans une liste de mots
    Node* wordList = NULL;
    insertAtBeginning(&wordList, (int)strdup("apple"));
    insertAtBeginning(&wordList, (int)strdup("banana"));
    insertAtBeginning(&wordList, (int)strdup("cherry"));
    insertAtBeginning(&wordList, (int)strdup("date"));
    char* longestWord = findLongestWord(wordList);
    printf("Mot le plus long : %s\n", longestWord);

    // Suppression du premier élément de la liste
    removeFirstElement(&list);
    printf("Liste après suppression du premier élément : ");
    printList(list);

    // Suppression du dernier élément de la liste
    removeLastElement(list);
    printf("Liste après suppression du dernier élément : ");
    printList(list);

    // Concaténation de deux listes
    Node* list2 = NULL;
    insertAtBeginning(&list2, 11);
    insertAtBeginning(&list2, 12);
    insertAtBeginning(&list2, 13);
    Node* concatenatedList = concatenateLists(list, list2);
    printf("Liste après concaténation : ");
    printList(concatenatedList);

    // Libération de la mémoire allouée pour les listes
    freeList(list);
    freeList(squaredList);
    freeList(wordList);
    freeList(list2);
    freeList(concatenatedList);

    return 0;
}
