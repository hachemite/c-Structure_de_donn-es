#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1000 // Taille totale de la mémoire simulée

// Structure de données pour un bloc de mémoire
typedef struct {
    void *ptr;      // Pointeur vers le bloc de mémoire alloué
    size_t size;    // Taille du bloc de mémoire
} MemoryBlock;

MemoryBlock memory[MEMORY_SIZE]; // Tableau pour stocker les blocs de mémoire
int top = -1;                     // Indice du sommet de la pile



// Fonction pour allouer un bloc de mémoire et l'ajouter à la pile
void allocateMemory(size_t size) {
    void *ptr = malloc(size); // Allocation de mémoire
    if (ptr == NULL) { // Vérification si l'allocation a réussi
        printf("Erreur : Impossible d'allouer de la mémoire.\n");
        return;
    }
    if (top < MEMORY_SIZE - 1) { // Vérification si la pile est pleine
        top++; // Incrément de l'indice du sommet de la pile
        memory[top].ptr = ptr; // Stockage du pointeur du bloc de mémoire
        memory[top].size = size; // Stockage de la taille du bloc de mémoire
        printf("Mémoire allouée avec succès.\n");
    } else {
        printf("Erreur : Mémoire pleine, impossible d'allouer plus de mémoire.\n");
        free(ptr); // Libération de la mémoire allouée
    }
}

// Fonction pour libérer un bloc de mémoire et le retirer de la pile
void freeMemory() {
    if (top >= 0) { // Vérification si la pile contient des blocs de mémoire allouée
        free(memory[top].ptr); // Libération de la mémoire du dernier bloc alloué
        printf("Mémoire libérée avec succès.\n");
        top--; // Décrément de l'indice du sommet de la pile
    } else {
        printf("Erreur : Aucune mémoire allouée à libérer.\n");
    }
}

// Fonction pour afficher l'état actuel de la pile de mémoire allouée
void displayAllocatedMemory() {
    if (top >= 0) { // Vérification si la pile contient des blocs de mémoire allouée
        printf("Mémoire allouée :\n");
        for (int i = 0; i <= top; i++) { // Parcours de la pile
            printf("Bloc %d : Adresse = %p, Taille = %zu\n", i+1, memory[i].ptr, memory[i].size);
        }
    } else {
        printf("Aucune mémoire allouée pour le moment.\n");
    }
}

// Fonction pour calculer et afficher le niveau de fragmentation de la mémoire
void displayFragmentation() {
    size_t total_allocated = 0; // Variable pour stocker la taille totale de mémoire allouée
    for (int i = 0; i <= top; i++) { // Parcours de la pile de mémoire allouée
        total_allocated += memory[i].size; // Accumulation de la taille de chaque bloc alloué
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
        printf("1. Allouer de la mémoire\n");
        printf("2. Libérer de la mémoire\n");
        printf("3. Afficher la mémoire allouée\n");
        printf("4. Afficher la fragmentation\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Taille de la mémoire à allouer : ");
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

