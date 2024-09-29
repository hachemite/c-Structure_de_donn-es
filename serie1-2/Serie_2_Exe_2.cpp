#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure d'un nœud de la liste chaînée pour stocker des entiers
typedef struct IntNode {
    int data;
    struct IntNode* next;
} IntNode;

// Structure d'un nœud de la liste chaînée pour stocker des chaînes de caractères
typedef struct StringNode {
    char* data;
    struct StringNode* next;
} StringNode;

// Fonction pour créer un nouveau nœud avec une donnée donnée (entier)
IntNode* create_int_node(int data) {
    IntNode* new_node = (IntNode*)malloc(sizeof(IntNode));
    if (new_node == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Fonction pour créer un nouveau nœud avec une donnée donnée (chaîne de caractères)
StringNode* create_string_node(char* data) {
    StringNode* new_node = (StringNode*)malloc(sizeof(StringNode));
    if (new_node == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = strdup(data);
    new_node->next = NULL;
    return new_node;
}

// Fonction pour insérer un nouveau nœud au début de la liste chaînée (entiers)
void insert_int_node_beginning(IntNode** head, int data) {
    IntNode* new_node = create_int_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Fonction pour insérer un nouveau nœud au début de la liste chaînée (chaînes de caractères)
void insert_string_node_beginning(StringNode** head, char* data) {
    StringNode* new_node = create_string_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Fonction pour trouver le mot le plus grand suivant l'ordre alphanumérique
char* find_longest_word(StringNode* head) {
    char* longest_word = NULL;
    StringNode* current = head;
    while (current != NULL) {
        if (longest_word == NULL || strcmp(current->data, longest_word) > 0) {
            longest_word = current->data;
        }
        current = current->next;
    }
    return longest_word;
}

// Fonction pour supprimer le premier élément de la liste (entiers)
void remove_first_int_element(IntNode** head) {
    if (*head != NULL) {
        IntNode* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Fonction pour supprimer le dernier élément de la liste (chaînes de caractères)
// Fonction pour supprimer le dernier élément d'une liste chaînée de chaînes de caractères



// Fonction pour concaténer deux listes (entiers)
// Fonction pour concaténer deux listes d'entiers
void concatenate_int_lists(IntNode** first, IntNode* second) {
    // Vérifier si la première liste est vide
    if (*first == NULL) {
        *first = second; // Si oui, simplement assigner la deuxième liste à la première
    } else {
        // La première liste n'est pas vide
        IntNode* current = *first;

        // Parcourir la première liste jusqu'à la fin
        while (current->next != NULL) {
            current = current->next;
        }

        // À ce stade, current pointe vers le dernier élément de la première liste
        // Concaténer la deuxième liste à la fin de la première liste
        current->next = second;
    }
}


// Fonction pour afficher les éléments de la liste (entiers)
void print_int_list(IntNode* head) {
    IntNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour afficher les éléments de la liste (chaînes de caractères)
void print_string_list(StringNode* head) {
    StringNode* current = head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire allouée à la liste (entiers)
void free_int_list(IntNode* head) {
    IntNode* current = head;
    while (current != NULL) {
        IntNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Fonction pour libérer la mémoire allouée à la liste (chaînes de caractères)
void free_string_list(StringNode* head) {
    StringNode* current = head;
    while (current != NULL) {
        StringNode* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}


int main() {
    IntNode* int_list = NULL;

    StringNode* string_list = NULL;

    // Insertion d'entiers dans la première liste
    insert_int_node_beginning(&int_list, 3);
    insert_int_node_beginning(&int_list, 31);
    insert_int_node_beginning(&int_list, 49);
    insert_int_node_beginning(&int_list, 53);
// Liste des carrés des éléments

    // Insertion de mots dans la deuxième liste
    insert_string_node_beginning(&string_list, (char*)"Ahmed");
    insert_string_node_beginning(&string_list, (char*)"Mostapha");
    insert_string_node_beginning(&string_list, (char*)"Mounir");
    insert_string_node_beginning(&string_list, (char*)"Safae");

    printf("Liste d'entiers initiale : ");
    print_int_list(int_list);

    printf("Liste de mots initiale : ");
    print_string_list(string_list);

    printf("Mot le plus grand dans la liste de mots : %s\n", find_longest_word(string_list));

    remove_first_int_element(&int_list);
    printf("Liste d'entiers après suppression du premier élément : ");
    print_int_list(int_list);


    printf("Liste de mots après suppression du dernier élément : ");
    print_string_list(string_list);

    concatenate_int_lists(&int_list, create_int_node(50));
    printf("Liste d'entiers après concaténation avec un nouvel élément : ");
    print_int_list(int_list);

    // Libération de la mémoire allouée pour les listes
    free_int_list(int_list);
    free_string_list(string_list);

    return 0;
}

