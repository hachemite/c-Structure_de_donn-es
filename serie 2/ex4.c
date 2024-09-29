#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 1000
#define MAX_BLOCKS 100

// Structure pour repr�senter un bloc de m�moire
typedef struct {
    int start;
    int end;
} MemoryBlock;

// Pile pour suivre les allocations et les lib�rations
MemoryBlock memoryStack[MAX_BLOCKS];
int top = -1;

// Fonction pour allouer un bloc de m�moire
void allocateMemory(int size) {
    if (top < MAX_BLOCKS - 1) {
        MemoryBlock block = {top > -1 ? memoryStack[top].end + 1 : 0, top > -1 ? memoryStack[top].end + size : size - 1};
        memoryStack[++top] = block;
        printf("Bloc de m�moire allou� : [%d, %d]\n", block.start, block.end);
    } else {
        printf("Erreur : Pas assez d'espace m�moire disponible.\n");
    }
}

// Fonction pour lib�rer un bloc de m�moire
void freeMemory() {
    if (top > -1) {
        MemoryBlock block = memoryStack[top--];
        printf("Bloc de m�moire lib�r� : [%d, %d]\n", block.start, block.end);
    } else {
        printf("Erreur : Aucun bloc de m�moire � lib�rer.\n");
    }
}

// Fonction pour afficher la m�moire allou�e
void displayMemory() {
    printf("M�moire allou�e :\n");
    for (int i = 0; i <= top; i++) {
        printf("[%d, %d]\n", memoryStack[i].start, memoryStack[i].end);
    }
}

// Fonction pour calculer et afficher le niveau de fragmentation de la m�moire
void displayFragmentation() {
    int totalMemory = 0;
    for (int i = 0; i <= top; i++) {
        totalMemory += memoryStack[i].end - memoryStack[i].start + 1;
    }
    int fragmentation = MAX_MEMORY_SIZE - totalMemory;
    printf("Niveau de fragmentation : %d\n", fragmentation);
}

// Fonction pour afficher le menu et g�rer les interactions avec l'utilisateur
void displayMenu() {
    int choice, size;
    do {
        printf("\nGestionnaire de m�moire\n");
        printf("1. Allouer de la m�moire\n");
        printf("2. Lib�rer de la m�moire\n");
        printf("3. Afficher la m�moire allou�e\n");
        printf("4. Afficher la fragmentation de la m�moire\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Taille du bloc � allouer : ");
                scanf("%d", &size);
                allocateMemory(size);
                break;
            case 2:
                freeMemory();
                break;
            case 3:
                displayMemory();
                break;
            case 4:
                displayFragmentation();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choice != 0);
}

int main() {
    displayMenu();
    return 0;
}
