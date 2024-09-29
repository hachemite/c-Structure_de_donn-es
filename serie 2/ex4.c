#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY_SIZE 1000
#define MAX_BLOCKS 100

// Structure pour représenter un bloc de mémoire
typedef struct {
    int start;
    int end;
} MemoryBlock;

// Pile pour suivre les allocations et les libérations
MemoryBlock memoryStack[MAX_BLOCKS];
int top = -1;

// Fonction pour allouer un bloc de mémoire
void allocateMemory(int size) {
    if (top < MAX_BLOCKS - 1) {
        MemoryBlock block = {top > -1 ? memoryStack[top].end + 1 : 0, top > -1 ? memoryStack[top].end + size : size - 1};
        memoryStack[++top] = block;
        printf("Bloc de mémoire alloué : [%d, %d]\n", block.start, block.end);
    } else {
        printf("Erreur : Pas assez d'espace mémoire disponible.\n");
    }
}

// Fonction pour libérer un bloc de mémoire
void freeMemory() {
    if (top > -1) {
        MemoryBlock block = memoryStack[top--];
        printf("Bloc de mémoire libéré : [%d, %d]\n", block.start, block.end);
    } else {
        printf("Erreur : Aucun bloc de mémoire à libérer.\n");
    }
}

// Fonction pour afficher la mémoire allouée
void displayMemory() {
    printf("Mémoire allouée :\n");
    for (int i = 0; i <= top; i++) {
        printf("[%d, %d]\n", memoryStack[i].start, memoryStack[i].end);
    }
}

// Fonction pour calculer et afficher le niveau de fragmentation de la mémoire
void displayFragmentation() {
    int totalMemory = 0;
    for (int i = 0; i <= top; i++) {
        totalMemory += memoryStack[i].end - memoryStack[i].start + 1;
    }
    int fragmentation = MAX_MEMORY_SIZE - totalMemory;
    printf("Niveau de fragmentation : %d\n", fragmentation);
}

// Fonction pour afficher le menu et gérer les interactions avec l'utilisateur
void displayMenu() {
    int choice, size;
    do {
        printf("\nGestionnaire de mémoire\n");
        printf("1. Allouer de la mémoire\n");
        printf("2. Libérer de la mémoire\n");
        printf("3. Afficher la mémoire allouée\n");
        printf("4. Afficher la fragmentation de la mémoire\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Taille du bloc à allouer : ");
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
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 0);
}

int main() {
    displayMenu();
    return 0;
}
