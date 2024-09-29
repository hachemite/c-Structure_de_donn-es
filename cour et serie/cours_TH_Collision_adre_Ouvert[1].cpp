#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
    char* cle;
    void* valeur;
} Element;

typedef struct table_hachage {
    Element** table;
    int taille_table;
    unsigned int (*fonction_hachage)(char*);
} TableHachage;

unsigned int hachage_simple(char* cle) {
    unsigned int hash = 0;
    while (*cle) {
        hash = (hash * 31) + *cle;
        cle++;
    }
    return hash;
}

TableHachage* initialiser_table_hachage(int taille_table) {
    TableHachage* table = (TableHachage*)malloc(sizeof(TableHachage));
    if (table == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour la table de hachage.\n");
        exit(EXIT_FAILURE);
    }

    table->table = (Element**)malloc(taille_table * sizeof(Element*));
    if (table->table == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour le tableau de la table de hachage.\n");
        exit(EXIT_FAILURE);
    }

    table->taille_table = taille_table;
    table->fonction_hachage = hachage_simple;

    // Initialiser chaque élément de la table à NULL
    for (int i = 0; i < taille_table; i++) {
        table->table[i] = NULL;
    }

    return table;
}

void ajouter_element(TableHachage* table, char* cle, void* valeur) {
    unsigned int index = table->fonction_hachage(cle) % table->taille_table;

    // Si la case est vide, ajouter l'élément
    if (table->table[index] == NULL) {
        Element* nouvel_element = (Element*)malloc(sizeof(Element));
        if (nouvel_element == NULL) {
            printf("Erreur : Impossible d'allouer de la mémoire pour l'élément de la table de hachage.\n");
            exit(EXIT_FAILURE);
        }
        nouvel_element->cle = strdup(cle);
        nouvel_element->valeur = valeur;
        table->table[index] = nouvel_element;
    } else {
        // Si la case est occupée, chercher une case vide en parcourant la table
        int i = (index + 1) % table->taille_table;
        while (i != index) {
            if (table->table[i] == NULL) {
                Element* nouvel_element = (Element*)malloc(sizeof(Element));
                if (nouvel_element == NULL) {
                    printf("Erreur : Impossible d'allouer de la mémoire pour l'élément de la table de hachage.\n");
                    exit(EXIT_FAILURE);
                }
                nouvel_element->cle = strdup(cle);
                nouvel_element->valeur = valeur;
                table->table[i] = nouvel_element;
                return;
            }
            i = (i + 1) % table->taille_table;
        }
        // Si aucune case vide n'est trouvée
        printf("Erreur : La table de hachage est pleine.\n");
        exit(EXIT_FAILURE);
    }
}

void* rechercher_element(TableHachage* table, char* cle) {
    unsigned int index = table->fonction_hachage(cle) % table->taille_table;

    int i = index;
    while (table->table[i] != NULL) {
        if (strcmp(table->table[i]->cle, cle) == 0) {
            return table->table[i]->valeur;
        }
        i = (i + 1) % table->taille_table;
        if (i == index) {
            break; // On a parcouru toute la table sans trouver l'élément
        }
    }

    return NULL; // L'élément n'est pas trouvé
}

void supprimer_element(TableHachage* table, char* cle) {
    unsigned int index = table->fonction_hachage(cle) % table->taille_table;

    int i = index;
    while (table->table[i] != NULL) {
        if (strcmp(table->table[i]->cle, cle) == 0) {
            free(table->table[i]->cle);
            free(table->table[i]);
            table->table[i] = NULL;
            // Réorganiser la table pour conserver la cohérence de l'adressage ouvert
            int j = (i + 1) % table->taille_table;
            while (table->table[j] != NULL) {
                unsigned int h = table->fonction_hachage(table->table[j]->cle) % table->taille_table;
                if ((j > i && (h <= i || h > j)) || (j < i && (h <= i && h > j))) {
                    table->table[i] = table->table[j];
                    table->table[j] = NULL;
                    i = j;
                }
                j = (j + 1) % table->taille_table;
            }
            return;
        }
        i = (i + 1) % table->taille_table;
        if (i == index) {
            break; // On a parcouru toute la table sans trouver l'élément
        }
    }
}

void liberer_table_hachage(TableHachage* table) {
    if (table == NULL) return;

    for (int i = 0; i < table->taille_table; i++) {
        if (table->table[i] != NULL) {
            free(table->table[i]->cle);
            free(table->table[i]);
        }
    }

    free(table->table);
    free(table);
}
void afficher_table_hachage(TableHachage* table) {
    printf("Table de hachage :\n");
    for (int i = 0; i < table->taille_table; i++) {
        if (table->table[i] != NULL) {
            printf("[%d] -> (%s, %s)\n", i, table->table[i]->cle, (char*)table->table[i]->valeur);
        } else {
            printf("[%d] -> NULL\n", i);
        }
    }
}

int main() {
    TableHachage* table = initialiser_table_hachage(10);

    ajouter_element(table, (char*)"key1", (char*)"value1");
    ajouter_element(table, (char*)"key2", (char*)"value2");
    ajouter_element(table, (char*)"key3", (char*)"value3");
	afficher_table_hachage(table);
	printf("\n----------------------------------------------\n");
    printf("Recherche de key2 : %s\n", (char*)rechercher_element(table, (char*)"key2"));
    printf("Recherche de key4 : %s\n", (char*)rechercher_element(table, (char*)"key4"));
	printf("\n----------------------------------------------\n");
    supprimer_element(table, (char*)"key2");
	afficher_table_hachage(table);
	printf("\n----------------------------------------------\n");
    printf("Recherche de key2 après suppression : %s\n", (char*)rechercher_element(table, (char*)"key2"));

    liberer_table_hachage(table);

    return 0;
}

