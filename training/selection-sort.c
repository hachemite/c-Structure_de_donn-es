#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

// Function to print the linked list
void printList(struct Node* head) {
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

// Function to perform selection sort on the linked list
void selectionSort(struct Node** head_ref) {
  struct Node* current;

  // Traverse through all nodes
  for (current = *head_ref; current != NULL; current = current->next) {
    // Initialize min_node as current
    struct Node* min_node = current;

    // Search for the minimum node after current
    struct Node* next = current->next;
    while (next != NULL) {
      if (next->data < min_node->data) {
        min_node = next;
      }
      next = next->next;
    }

    // Swap data of current and minimum node (if different)
    if (current != min_node) {
      int temp = current->data;
      current->data = min_node->data;
      min_node->data = temp;
    }
  }
}

int main() {
  struct Node* head = newNode(5);
  head->next = newNode(3);
  head->next->next = newNode(6);
  head->next->next->next = newNode(1);

  printf("Original Linked List: ");
  printList(head);

  selectionSort(&head);

  printf("Sorted Linked List: ");
  printList(head);

  return 0;
}
