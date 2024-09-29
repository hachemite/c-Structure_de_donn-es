#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure Node pour chaque �l�ment de la table de hachage
struct Node {
    int data;
    struct Node* next;
};

// Fonction de hachage simple
int hashFunction(int value, int tableSize) {
    return value % tableSize;
}

// Fonction pour cr�er un nouveau n�ud avec la valeur sp�cifi�e
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Fonction pour ins�rer un �l�ment dans la table de hachage en g�rant les collisions par cha�nage
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

// Fonction pour afficher les �l�ments de la table de hachage
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
    // Initialisation des donn�es fournies
    int data[] = {6, 8, 3, 1, 4, 9, 2, 7, 5};
    int dataSize = sizeof(data) / sizeof(data[0]);
    int tableSize = 3;

    // Cr�ation de la table de hachage
    struct Node** hashTable = (struct Node**)malloc(tableSize * sizeof(struct Node*));
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = NULL;
    }

    // Insertion des donn�es dans la table de hachage
    for (int i = 0; i < dataSize; i++) {
        insertIntoHashTable(hashTable, data[i], tableSize);
    }

    // Affichage de la table de hachage r�sultante
    displayHashTable(hashTable, tableSize);

    // Lib�ration de la m�moire allou�e pour la table de hachage
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

