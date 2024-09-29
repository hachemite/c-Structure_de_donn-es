/*Explications :
Nous commençons par définir une structure pour représenter un élément de la liste.
* Elle contient deux champs : data pour stocker la valeur de l'élément, 
 et next pour pointer vers le prochain élément de la liste.
* La fonction append permet d'ajouter un élément à la fin de la liste.
* La fonction split divise la liste en deux parties*/

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un élément de la liste
struct node {
    int data;
    struct node *next;
};

// Fonction pour ajouter un élément à la fin de la liste
void append(struct node **head, int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

// Fonction pour diviser la liste en deux parties
void split(struct node *head, struct node **left, struct node **right) {
    struct node *slow = head;
    struct node *fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = head;
    *right = slow->next;
    slow->next = NULL;
}

// Fonction pour fusionner deux listes triées
struct node* merge(struct node *left, struct node *right) {
    if (left == NULL) {
        return right;
    }

    if (right == NULL) {
        return left;
    }

    struct node *result = NULL;
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

// Fonction principale de tri par fusion
void merge_sort(struct node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct node *left, *right;
    split(*head, &left, &right);

    merge_sort(&left);
    merge_sort(&right);

    *head = merge(left, right);
}

// Fonction pour afficher les éléments de la liste
void print_list(struct node *head) {
    struct node *temp = head;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Programme principal pour tester la fonction de tri par fusion
int main() {
    struct node *head = NULL;
    append(&head, 5);
    append(&head, 3);
    append(&head, 7);
    append(&head, 2);
    append(&head, 8);

    printf("Liste avant le tri par fusion : ");
    print_list(head);

    merge_sort(&head);

    printf("Liste après le tri par fusion : ");
    print_list(head);

    return 0;
}

