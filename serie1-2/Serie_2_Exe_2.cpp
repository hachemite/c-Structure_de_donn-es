#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure d'un n�ud de la liste cha�n�e pour stocker des entiers
typedef struct IntNode {
    int data;
    struct IntNode* next;
} IntNode;

// Structure d'un n�ud de la liste cha�n�e pour stocker des cha�nes de caract�res
typedef struct StringNode {
    char* data;
    struct StringNode* next;
} StringNode;

// Fonction pour cr�er un nouveau n�ud avec une donn�e donn�e (entier)
IntNode* create_int_node(int data) {
    IntNode* new_node = (IntNode*)malloc(sizeof(IntNode));
    if (new_node == NULL) {
        printf("Erreur lors de l'allocation de m�moire.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Fonction pour cr�er un nouveau n�ud avec une donn�e donn�e (cha�ne de caract�res)
StringNode* create_string_node(char* data) {
    StringNode* new_node = (StringNode*)malloc(sizeof(StringNode));
    if (new_node == NULL) {
        printf("Erreur lors de l'allocation de m�moire.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = strdup(data);
    new_node->next = NULL;
    return new_node;
}

// Fonction pour ins�rer un nouveau n�ud au d�but de la liste cha�n�e (entiers)
void insert_int_node_beginning(IntNode** head, int data) {
    IntNode* new_node = create_int_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Fonction pour ins�rer un nouveau n�ud au d�but de la liste cha�n�e (cha�nes de caract�res)
void insert_string_node_beginning(StringNode** head, char* data) {
    StringNode* new_node = create_string_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Fonction pour trouver le mot le plus grand suivant l'ordre alphanum�rique
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

// Fonction pour supprimer le premier �l�ment de la liste (entiers)
void remove_first_int_element(IntNode** head) {
    if (*head != NULL) {
        IntNode* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Fonction pour supprimer le dernier �l�ment de la liste (cha�nes de caract�res)
// Fonction pour supprimer le dernier �l�ment d'une liste cha�n�e de cha�nes de caract�res



// Fonction pour concat�ner deux listes (entiers)
// Fonction pour concat�ner deux listes d'entiers
void concatenate_int_lists(IntNode** first, IntNode* second) {
    // V�rifier si la premi�re liste est vide
    if (*first == NULL) {
        *first = second; // Si oui, simplement assigner la deuxi�me liste � la premi�re
    } else {
        // La premi�re liste n'est pas vide
        IntNode* current = *first;

        // Parcourir la premi�re liste jusqu'� la fin
        while (current->next != NULL) {
            current = current->next;
        }

        // � ce stade, current pointe vers le dernier �l�ment de la premi�re liste
        // Concat�ner la deuxi�me liste � la fin de la premi�re liste
        current->next = second;
    }
}


// Fonction pour afficher les �l�ments de la liste (entiers)
void print_int_list(IntNode* head) {
    IntNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour afficher les �l�ments de la liste (cha�nes de caract�res)
void print_string_list(StringNode* head) {
    StringNode* current = head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour lib�rer la m�moire allou�e � la liste (entiers)
void free_int_list(IntNode* head) {
    IntNode* current = head;
    while (current != NULL) {
        IntNode* temp = current;
        current = current->next;
        free(temp);
    }
}

// Fonction pour lib�rer la m�moire allou�e � la liste (cha�nes de caract�res)
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

    // Insertion d'entiers dans la premi�re liste
    insert_int_node_beginning(&int_list, 3);
    insert_int_node_beginning(&int_list, 31);
    insert_int_node_beginning(&int_list, 49);
    insert_int_node_beginning(&int_list, 53);
// Liste des carr�s des �l�ments

    // Insertion de mots dans la deuxi�me liste
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
    printf("Liste d'entiers apr�s suppression du premier �l�ment : ");
    print_int_list(int_list);


    printf("Liste de mots apr�s suppression du dernier �l�ment : ");
    print_string_list(string_list);

    concatenate_int_lists(&int_list, create_int_node(50));
    printf("Liste d'entiers apr�s concat�nation avec un nouvel �l�ment : ");
    print_int_list(int_list);

    // Lib�ration de la m�moire allou�e pour les listes
    free_int_list(int_list);
    free_string_list(string_list);

    return 0;
}

