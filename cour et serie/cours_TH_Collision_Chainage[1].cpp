#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure d'un élément de la table de hachage
typedef struct element {
    char* cle;              // Clé de l'élément
    void* valeur;           // Valeur associée à la clé (déclaration d'une variable nommée valeur de type void*)
    /*void: Ce mot-clé indique que la variable ne stocke aucune valeur spécifique. En d'autres termes, elle est un pointeur générique 
	qui peut pointer vers n'importe quel type de données.
	===> void* est un type de pointeur générique.
	===> Il peut pointer vers n'importe quel type de données.
	===> Il est important de convertir le pointeur générique en pointeur du type de données 
	approprié avant de l'utiliser pour accéder à la valeur stockée
	*/
    struct element* suivant;// Pointeur vers le prochain élément en cas de collision
} Element;

// Définition de la structure de la table de hachage
/*
Dans ce contexte, l'utilisation d'un pointeur vers un pointeur offre une certaine flexibilité dans la gestion de la table de hachage. 
Le pointeur externe (table) peut être facilement réaffecté pour pointer vers un autre 
tableau d'éléments si nécessaire. Cela permet de redimensionner la table de hachage dynamiquement 
si les collisions deviennent fréquentes.
*/
typedef struct table_hachage {
    Element** table;    // Tableau de pointeurs d'éléments: La variable table est déclarée comme un pointeur qui pointe vers un autre pointeur.
    int taille_table;               // Taille de la table
    unsigned int (*fonction_hachage)(char*);  // Pointeur vers la fonction de hachage utilisée
} TableHachage;

// Fonction de hachage simple
unsigned int hachage_simple(char* cle) {
    unsigned int hash = 0;
    while (*cle) {
        hash = (hash * 31) + *cle;  // Formule de hachage simple
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

    Element* nouvel_element = (Element*)malloc(sizeof(Element));
    if (nouvel_element == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour l'élément de la table de hachage.\n");
        exit(EXIT_FAILURE);
    }

    nouvel_element->cle = strdup(cle);
    nouvel_element->valeur = valeur;
    nouvel_element->suivant = NULL;

    // Gestion des collisions par chaînage
    if (table->table[index] == NULL) {
        table->table[index] = nouvel_element;
    } else {
        Element* actuel = table->table[index];
        while (actuel->suivant != NULL) {
            actuel = actuel->suivant;
        }
        actuel->suivant = nouvel_element;
    }
}

void* rechercher_element(TableHachage* table, char* cle) {
    unsigned int index = table->fonction_hachage(cle) % table->taille_table;

    Element* actuel = table->table[index];
    while (actuel != NULL) {
        if (strcmp(actuel->cle, cle) == 0) {
            return actuel->valeur;
        }
        actuel = actuel->suivant;
    }

    return NULL; // L'élément n'est pas trouvé
}

void supprimer_element(TableHachage* table, char* cle) {
    unsigned int index = table->fonction_hachage(cle) % table->taille_table;

    Element* actuel = table->table[index];
    Element* precedent = NULL;

    while (actuel != NULL) {
        if (strcmp(actuel->cle, cle) == 0) {
            if (precedent == NULL) {
                table->table[index] = actuel->suivant;
            } else {
                precedent->suivant = actuel->suivant;
            }
            free(actuel->cle);
            free(actuel);
            return;
        }
        precedent = actuel;
        actuel = actuel->suivant;
    }
}

void liberer_table_hachage(TableHachage* table) {
    if (table == NULL) return;

    for (int i = 0; i < table->taille_table; i++) {
        Element* actuel = table->table[i];
        while (actuel != NULL) {
            Element* suivant = actuel->suivant;
            free(actuel->cle);
            free(actuel);
            actuel = suivant;
        }
    }

    free(table->table);
    free(table);
}
void afficher_table_hachage(TableHachage* table) {
    printf("Table de hachage :\n");
    for (int i = 0; i < table->taille_table; i++) {
        printf("[%d] -> ", i);
        Element* actuel = table->table[i];
        while (actuel != NULL) {
            printf("(%s, %s) -> ", actuel->cle, (char*)actuel->valeur);
            actuel = actuel->suivant;
        }
        printf("NULL\n");
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

