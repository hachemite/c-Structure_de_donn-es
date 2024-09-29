#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char *word;
  struct Node *left;
  struct Node *right;
} Node;

Node *insertNode(Node *root, char *word) {
  if (root == NULL) {
    Node *new_node = malloc(sizeof(Node));
    new_node->word = strdup(word);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
  }

  if (strcmp(word, root->word) < 0) {
    root->left = insertNode(root->left, word);
  } else {
    root->right = insertNode(root->right, word);
  }

  return root;
}

void searchWord(Node *root, char *word) {
  if (root == NULL) {
    printf("%s not found.\n", word);
    return;
  }

  if (strcmp(word, root->word) == 0) {
    printf("%s found.\n", word);
    return;
  } else if (strcmp(word, root->word) < 0) {
    searchWord(root->left, word);
  } else {
    searchWord(root->right, word);
  }
}

void inOrderTraversal(Node *root) {
  if (root == NULL) {
    return;
  }

  inOrderTraversal(root->left);
  printf("%s ->", root->word);
  inOrderTraversal(root->right);
}

void freeTree(Node *root) {
  if (root == NULL) {
    return;
  }

  freeTree(root->left);
  freeTree(root->right);
  free(root->word);
  free(root);
}

int main() {
  char paragraph[1000];
  Node *root = NULL;

  printf("Enter a paragraph: ");
  fgets(paragraph, sizeof(paragraph), stdin);

  char *word = strtok(paragraph, " ");
  while (word != NULL) {
    root = insertNode(root, word);
    word = strtok(NULL, " ");
  }

  printf("\nIn-order traversal of the BST:\n");
  inOrderTraversal(root);

  printf("\nSearch a word: ");
  char search_word[100];
  scanf("%s", search_word);
  searchWord(root, search_word);

  freeTree(root);

  return 0;
}

