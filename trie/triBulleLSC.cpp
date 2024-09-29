#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_node(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int get_list_length(Node* head) {
    int length = 0;
    Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

void bubble_sort(Node** head) {
    int n = get_list_length(*head);
    Node* temp;
    for (int i = 0; i < n - 1; i++) {
        Node* current = *head;
        Node* prev = NULL;
        while (current->next != NULL) {
            if (current->data > current->next->data) {
                if (prev == NULL) {
                    *head = current->next;
                } else {
                    prev->next = current->next;
                }
                temp = current->next->next;
                current->next->next = current;
                current->next = temp;
                prev = current->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
}
/*Dans ce programme, la fonction bubble_sort trie la liste en utilisant l'algorithme de tri � bulle. La fonction get_list_length calcule la longueur de
 la liste en parcourant la liste une fois. Ensuite, la boucle ext�rieure de bubble_sort parcourt la liste n - 1 fois o� n est la longueur de la liste. 
 La boucle int�rieure parcourt la liste en comparant chaque paire d'�l�ments adjacents et les �change si n�cessaire pour les mettre dans l'ordre croissant.
  Les pointeurs prev, current et temp sont utilis�s pour r�organiser les liens entre les noeuds de la liste.
*/

int main() {
    Node* head = NULL;
    insert_node(&head, 10);
    insert_node(&head, 7);
    insert_node(&head, 8);
    insert_node(&head, 9);
    insert_node(&head, 1);
    insert_node(&head, 5);
    insert_node(&head, 3);
    insert_node(&head, 2);
    printf("List before sorting:\n");
    print_list(head);
    bubble_sort(&head);
    printf("List after sorting:\n");
    print_list(head);
    return 0;
}

