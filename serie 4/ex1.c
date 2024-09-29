#include <stdio.h>
#include <stdlib.h>

// Structure d'un nœud de l'arbre binaire
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Fonction pour créer un nouveau nœud
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour un nouveau nœud.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer un nœud dans un arbre binaire de recherche
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

// Fonction pour effectuer une traversée en préfixe de l'arbre
void prefixTraversal(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);  // Affiche la valeur du nœud
        prefixTraversal(root->left); // Traverse le sous-arbre gauche
        prefixTraversal(root->right); // Traverse le sous-arbre droit
    }
}
// Fonction pour effectuer une traversée en ordre infix de l'arbre
void infixTraversal(Node *root) {
    if (root != NULL) {
        infixTraversal(root->left); // Traverse le sous-arbre gauche
        printf("%d ", root->data);  // Affiche la valeur du nœud
        infixTraversal(root->right); // Traverse le sous-arbre droit
    }
}

// Fonction pour effectuer une traversée en postfix de l'arbre
void postfixTraversal(Node *root) {
    if (root != NULL) {
        postfixTraversal(root->left); // Traverse le sous-arbre gauche
        postfixTraversal(root->right); // Traverse le sous-arbre droit
        printf("%d ", root->data);  // Affiche la valeur du nœud
    }
}


int main() {
    int nodes[] = {17, 6, 8, 9, 15, 13, 41, 28, 16};
    int numNodes = sizeof(nodes) / sizeof(nodes[0]);

    Node *root = NULL;
    for (int i = 0; i < numNodes; i++) {
        root = insert(root, nodes[i]);
    }

    printf("Arbre binaire de recherche créé avec succès.\n");

    printf("Traversée en préfixe de l'arbre: ");
    prefixTraversal(root);
    printf("\n");


    printf("Traversée en infix de l'arbre: ");
    infixTraversal(root);
    printf("\n");

    printf("Traversée en postfix de l'arbre: ");
    postfixTraversal(root);
    printf("\n");

    return 0;
}
