#include <stdio.h>
#include <stdlib.h>

// Structure d'un n�ud de l'arbre binaire
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Fonction pour cr�er un nouveau n�ud
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur: Impossible d'allouer de la m�moire pour un nouveau n�ud.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour ins�rer un n�ud dans un arbre binaire de recherche
Node *insert(Node *root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Fonction pour effectuer une travers�e en pr�fixe de l'arbre
void prefixTraversal(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);  // Affiche la valeur du n�ud
        prefixTraversal(root->left); // Traverse le sous-arbre gauche
        prefixTraversal(root->right); // Traverse le sous-arbre droit
    }
}
// Fonction pour effectuer une travers�e en ordre infix de l'arbre
void infixTraversal(Node *root) {
    if (root != NULL) {
        infixTraversal(root->left); // Traverse le sous-arbre gauche
        printf("%d ", root->data);  // Affiche la valeur du n�ud
        infixTraversal(root->right); // Traverse le sous-arbre droit
    }
}

// Fonction pour effectuer une travers�e en postfix de l'arbre
void postfixTraversal(Node *root) {
    if (root != NULL) {
        postfixTraversal(root->left); // Traverse le sous-arbre gauche
        postfixTraversal(root->right); // Traverse le sous-arbre droit
        printf("%d ", root->data);  // Affiche la valeur du n�ud
    }
}


int main() {
    int nodes[] = {17, 6, 8, 9, 15, 13, 41, 28, 16};
    int numNodes = sizeof(nodes) / sizeof(nodes[0]);

    Node *root = NULL;
    for (int i = 0; i < numNodes; i++) {
        root = insert(root, nodes[i]);
    }

    printf("Arbre binaire de recherche cr�� avec succ�s.\n");

    printf("Travers�e en pr�fixe de l'arbre: ");
    prefixTraversal(root);
    printf("\n");


    printf("Travers�e en infix de l'arbre: ");
    infixTraversal(root);
    printf("\n");

    printf("Travers�e en postfix de l'arbre: ");
    postfixTraversal(root);
    printf("\n");

    return 0;
}
