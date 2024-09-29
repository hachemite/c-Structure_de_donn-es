#include <stdio.h>
#include <stdlib.h>

/* Définition de la structure d'un noeud de la liste chaînée */
typedef struct Node {
    int value;
    struct Node* next;
} Node;

/* Fonction pour ajouter un nouveau noeud à la fin de la liste chaînée */
void append(Node** head_ref, int new_value) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->value = new_value;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    Node* last_node = *head_ref;
    while (last_node->next != NULL) {
        last_node = last_node->next;
    }
    last_node->next = new_node;
}

/* Fonction pour afficher la liste chaînée */
void print_list(Node* node) {
    while (node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

/* Fonction pour échanger les valeurs de deux noeuds de la liste chaînée */
void swap_values(Node* node1, Node* node2) {
    int temp = node1->value;
    node1->value = node2->value;
    node2->value = temp;
}

/* Fonction pour effectuer le tri rapide sur la liste chaînée */
Node* quicksort(Node* head, Node* tail) {
    if (head == NULL || head == tail) {
        return head;
    }

    Node* pivot = head;
    Node* current = head->next;
    Node* last_smaller = NULL;

    while (current != tail) {
        if (current->value < pivot->value) {
            last_smaller = (last_smaller == NULL) ? head : last_smaller->next;
            swap_values(current, last_smaller);
        }
        current = current->next;
    }

    if (last_smaller == NULL) {
        last_smaller = head;
    }
    swap_values(pivot, last_smaller);

    quicksort(head, last_smaller);
    quicksort(last_smaller->next, tail);

    return head;
}

int main() {
    Node* head = NULL;
    append(&head, 6);
    append(&head, 2);
    append(&head, 8);
    append(&head, 3);
    append(&head, 5);
    append(&head, 1);

    printf("Liste chaînée originale : ");
    print_list(head);

    head = quicksort(head, NULL);

    printf("Liste chaînée triée : ");
    print_list(head);

    return 0;
}

