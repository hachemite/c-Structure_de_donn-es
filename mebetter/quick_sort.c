#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
  temp->data = data;
  temp->next = NULL;
  return temp;
}

// Function to print the linked list
void printList(struct Node* head) {
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

// Function to swap two nodes
void swap(struct Node* a, struct Node* b) {
  int temp = a->data;
  a->data = b->data;
  b->data = temp;
}

// Partition function
struct Node* partition(struct Node* head, struct Node* end) {
  struct Node* pivot = head;
  struct Node *current = head->next;

  while (current != end) {
    if (current->data < pivot->data) {
      swap(current, head);
      head = head->next;
    }
    current = current->next;
  }

  swap(pivot, head);  // Move pivot to its final position
  return head;
}

// Recursive Quick Sort function
void quickSort(struct Node* head, struct Node* tail) {
  if (head == tail || head == NULL) return;

  struct Node* pivot = partition(head, tail);

  // Recursively sort sub-lists
  quickSort(head, pivot->prev);
  quickSort(pivot->next, tail);
}

int main() {
  struct Node* head = NULL;
  head = newNode(4);
  head->next = newNode(2);
  head->next->next = newNode(8);
  head->next->next->next = newNode(1);
  head->next->next->next->next = newNode(6);

  printf("Original list: ");
  printList(head);

  quickSort(head, NULL); // Pass tail as NULL for the end of the list

  printf("Sorted list: ");
  printList(head);

  return 0;
}
