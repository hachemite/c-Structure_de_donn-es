#include <stdio.h>
#include <stdlib.h>

// Définition de la structure Node pour chaque élément de la table de hachage
struct Node {
    int data;
    struct Node* next;
};

// Fonction de hachage simple
int hashFunction(int value, int tableSize) {
    return value % tableSize;
}

// Fonction pour créer un nouveau nœud avec la valeur spécifiée
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour insérer un élément dans la table de hachage en gérant les collisions par chaînage
void insertIntoHashTable(struct Node** hashTable, int value, int tableSize) {
    int index = hashFunction(value, tableSize);
    struct Node* newNode = createNode(value);
    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct Node* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Fonction pour afficher les éléments de la table de hachage
void displayHashTable(struct Node** hashTable, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        printf("%d -> ", i);
        struct Node* current = hashTable[i];
        while (current != NULL) {
            printf("%d -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main() {
    // Initialisation des données fournies
    int data[] = {6, 8, 3, 1, 4, 9, 2, 7, 5};
    int dataSize = sizeof(data) / sizeof(data[0]);
    int tableSize = 3;

    // Création de la table de hachage
    struct Node** hashTable = (struct Node**)malloc(tableSize * sizeof(struct Node*));
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = NULL;
    }

    // Insertion des données dans la table de hachage
    for (int i = 0; i < dataSize; i++) {
        insertIntoHashTable(hashTable, data[i], tableSize);
    }

    // Affichage de la table de hachage résultante
    displayHashTable(hashTable, tableSize);

    // Libération de la mémoire allouée pour la table de hachage
    for (int i = 0; i < tableSize; i++) {
        struct Node* current = hashTable[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);

    return 0;
}

