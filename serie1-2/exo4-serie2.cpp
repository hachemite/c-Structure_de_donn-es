#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000 // Taille totale de la m�moire simul�e

// Structure de donn�es pour un bloc de m�moire
typedef struct {
    void *ptr;      // Pointeur vers le bloc de m�moire allou�
    size_t size;    // Taille du bloc de m�moire
} MemoryBlock;

MemoryBlock memory[MEMORY_SIZE]; // Tableau pour stocker les blocs de m�moire
int top = -1;                     // Indice du sommet de la pile



// Fonction pour allouer un bloc de m�moire et l'ajouter � la pile
void allocateMemory(size_t size) {
    void *ptr = malloc(size); // Allocation de m�moire
    if (ptr == NULL) { // V�rification si l'allocation a r�ussi
        printf("Erreur : Impossible d'allouer de la m�moire.\n");
        return;
    }
    if (top < MEMORY_SIZE - 1) { // V�rification si la pile est pleine
        top++; // Incr�ment de l'indice du sommet de la pile
        memory[top].ptr = ptr; // Stockage du pointeur du bloc de m�moire
        memory[top].size = size; // Stockage de la taille du bloc de m�moire
        printf("M�moire allou�e avec succ�s.\n");
    } else {
        printf("Erreur : M�moire pleine, impossible d'allouer plus de m�moire.\n");
        free(ptr); // Lib�ration de la m�moire allou�e
    }
}

// Fonction pour lib�rer un bloc de m�moire et le retirer de la pile
void freeMemory() {
    if (top >= 0) { // V�rification si la pile contient des blocs de m�moire allou�e
        free(memory[top].ptr); // Lib�ration de la m�moire du dernier bloc allou�
        printf("M�moire lib�r�e avec succ�s.\n");
        top--; // D�cr�ment de l'indice du sommet de la pile
    } else {
        printf("Erreur : Aucune m�moire allou�e � lib�rer.\n");
    }
}

// Fonction pour afficher l'�tat actuel de la pile de m�moire allou�e
void displayAllocatedMemory() {
    if (top >= 0) { // V�rification si la pile contient des blocs de m�moire allou�e
        printf("M�moire allou�e :\n");
        for (int i = 0; i <= top; i++) { // Parcours de la pile
            printf("Bloc %d : Adresse = %p, Taille = %zu\n", i+1, memory[i].ptr, memory[i].size);
        }
    } else {
        printf("Aucune m�moire allou�e pour le moment.\n");
    }
}

// Fonction pour calculer et afficher le niveau de fragmentation de la m�moire
void displayFragmentation() {
    size_t total_allocated = 0; // Variable pour stocker la taille totale de m�moire allou�e
    for (int i = 0; i <= top; i++) { // Parcours de la pile de m�moire allou�e
        total_allocated += memory[i].size; // Accumulation de la taille de chaque bloc allou�
    }
    size_t fragmentation = MEMORY_SIZE - total_allocated; // Calcul de la fragmentation
    printf("Niveau de fragmentation : %zu\n", fragmentation); // Affichage de la fragmentation
}

// Fonction principale pour l'interface utilisateur
int main() {
    int choice;
    size_t size;

    do {
        printf("\nMenu :\n");
        printf("1. Allouer de la m�moire\n");
        printf("2. Lib�rer de la m�moire\n");
        printf("3. Afficher la m�moire allou�e\n");
        printf("4. Afficher la fragmentation\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Taille de la m�moire � allouer : ");
                scanf("%zu", &size);
                allocateMemory(size);
                break;
            case 2:
                freeMemory();
                break;
            case 3:
                displayAllocatedMemory();
                break;
            case 4:
                displayFragmentation();
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 0);

    return 0;
}

