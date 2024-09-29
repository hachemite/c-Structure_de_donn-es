#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Pour INT_MIN et INT_MAX

// Structure représentant un nœud de l'arbre binaire de recherche
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Fonction pour créer un nouveau nœud avec la valeur spécifiée
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour insérer un nœud dans l'arbre binaire de recherche
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    } else {
        if (value < root->data) {
            root->left = insertNode(root->left, value);
        } else if (value > root->data) {
            root->right = insertNode(root->right, value);
        }
        return root;
    }
}

// Fonction pour vérifier si un nœud contenant une valeur donnée existe dans l'arbre
int searchNode(struct Node* root, int value) {
    if (root == NULL) {
        return 0;
    } else if (root->data == value) {
        return 1;
    } else if (value < root->data) {
        return searchNode(root->left, value);
    } else {
        return searchNode(root->right, value);
    }
}
// Fonction pour trouver le nœud de valeur minimale dans un sous-arbre donné
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
// Fonction pour supprimer un nœud contenant une valeur donnée de l'arbre
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;
    } else if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        } else {
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}


void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}



int main() {
    struct Node* root = NULL;

    // Insérer les valeurs dans l'arbre binaire de recherche
    root = insertNode(root, 6);
    root = insertNode(root, 3);
    root = insertNode(root, 1);
    root = insertNode(root, 4);
    root = insertNode(root, 2);
    root = insertNode(root, 5);
    root = insertNode(root, 8);
    root = insertNode(root, 9);
    root = insertNode(root, 7);

    // 1. Vérifier si l'arbre est complet




    // 3. Afficher les éléments de l'arbre en parcourant
    printf("Parcours préfixe : ");
    preorderTraversal(root);
    printf("\n");

    printf("Parcours infixe : ");
    inorderTraversal(root);
    printf("\n");

    printf("Parcours postfixe : ");
    postorderTraversal(root);
    printf("\n");



    return 0;
}

