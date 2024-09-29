#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Pour INT_MIN et INT_MAX

// Structure repr�sentant un n�ud de l'arbre binaire de recherche
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Fonction pour cr�er un nouveau n�ud avec la valeur sp�cifi�e
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Fonction pour ins�rer un n�ud dans l'arbre binaire de recherche
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

// Fonction pour v�rifier si un n�ud contenant une valeur donn�e existe dans l'arbre
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
// Fonction pour trouver le n�ud de valeur minimale dans un sous-arbre donn�
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
// Fonction pour supprimer un n�ud contenant une valeur donn�e de l'arbre
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


// Fonction pour effectuer un parcours pr�fixe de l'arbre (racine-gauche-droite)
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Fonction pour effectuer un parcours infixe de l'arbre (gauche-racine-droite)
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Fonction pour effectuer un parcours postfixe de l'arbre (gauche-droite-racine)
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Fonction pour calculer la hauteur de l'arbre
int calculateHeight(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = calculateHeight(root->left);
        int rightHeight = calculateHeight(root->right);
        return (leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);
    }
}

// Fonction pour calculer la profondeur moyenne des n�uds de l'arbre
float calculateAverageDepth(struct Node* root, int depth) {
    if (root == NULL) {
        return 0;
    } else {
        float leftSum = calculateAverageDepth(root->left, depth + 1);
        float rightSum = calculateAverageDepth(root->right, depth + 1);
        return depth + leftSum + rightSum;
    }
}

// Fonction pour v�rifier si l'arbre est un arbre binaire de recherche valide
int isBinarySearchTree(struct Node* root, int min, int max) {
    if (root == NULL) {
        return 1;
    } else if (root->data < min || root->data > max) {
        return 0;
    } else {
        return isBinarySearchTree(root->left, min, root->data - 1) &&
               isBinarySearchTree(root->right, root->data + 1, max);
    }
}

// Fonction pour trouver la profondeur d'un n�ud donn� dans l'arbre
int findNodeDepth(struct Node* root, int value, int depth) {
    if (root == NULL) {
        return -1;
    } else if (value == root->data) {
        return depth;
    } else if (value < root->data) {
        return findNodeDepth(root->left, value, depth + 1);
    } else {
        return findNodeDepth(root->right, value, depth + 1);
    }
}
// Structure pour la file
struct Queue {
    struct Node** array;
    int front, rear;
    unsigned capacity;
};

// Fonction pour cr�er une file avec une capacit� donn�e
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

// Fonction pour v�rifier si la file est vide
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Fonction pour v�rifier si la file est pleine
int isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Fonction pour ajouter un �l�ment � la file
void enqueue(struct Queue* queue, struct Node* item) {
    if (isFull(queue)) {
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    if (queue->front == -1) {
        queue->front = queue->rear;
    }
}

// Fonction pour retirer un �l�ment de la file
struct Node* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    struct Node* item = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    return item;
}

// Fonction pour v�rifier si l'arbre est complet
// Fonction pour v�rifier si l'arbre est complet
int isCompleteBinaryTree(struct Node* root) {
    if (root == NULL) {
        return 1;
    }

    struct Queue* queue = createQueue(1000); // Cr�ation de la file

    // Enfiler la racine
    enqueue(queue, root);

    int flag = 0; // Indicateur pour v�rifier si un n�ud sans enfant a �t� rencontr�

    // Parcourir l'arbre en largeur
    while (!isEmpty(queue)) {
        struct Node* tempNode = dequeue(queue);

        // Si un n�ud sans enfant a �t� rencontr� pr�c�demment et le n�ud actuel a des enfants
        if (tempNode->left == NULL && tempNode->right != NULL) {
            return 0;
        }

        // Si un n�ud sans enfant a �t� rencontr� pr�c�demment et le n�ud actuel n'a pas d'enfant
        if ((tempNode->left != NULL && tempNode->right == NULL) || (flag && (tempNode->left != NULL || tempNode->right != NULL))) {
            return 0;
        }

        // Si le n�ud actuel a un enfant gauche
        if (tempNode->left != NULL) {
            enqueue(queue, tempNode->left);
        } else {
            flag = 1; // Marquer qu'un n�ud sans enfant a �t� rencontr�
        }

        // Si le n�ud actuel a un enfant droit
        if (tempNode->right != NULL) {
            enqueue(queue, tempNode->right);
        } else {
            flag = 1; // Marquer qu'un n�ud sans enfant a �t� rencontr�
        }
    }

    // Si l'arbre a �t� parcouru sans probl�mes, il est complet
    return 1;
}
// Fonction pour trouver le successeur d'un n�ud donn� dans l'arbre
struct Node* findSuccessor(struct Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    struct Node* current = root;
    struct Node* successor = NULL;
    while (current != NULL) {
        if (value < current->data) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return successor;
}

// Fonction pour trouver le pr�d�cesseur d'un n�ud donn� dans l'arbre
struct Node* findPredecessor(struct Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    struct Node* current = root;
    struct Node* predecessor = NULL;
    while (current != NULL) {
        if (value > current->data) {
            predecessor = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return predecessor;
}
// Fonction pour compter le nombre de n�uds dans l'arbre
int countNodes(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Ins�rer les valeurs dans l'arbre binaire de recherche
    root = insertNode(root, 6);
    root = insertNode(root, 8);
    root = insertNode(root, 3);
    root = insertNode(root, 1);
    root = insertNode(root, 4);
    root = insertNode(root, 9);
    root = insertNode(root, 2);
    root = insertNode(root, 7);
    root = insertNode(root, 5);

    // 1. V�rifier si l'arbre est complet
    int isComplete = isCompleteBinaryTree(root);
    printf("L'arbre est %s complet.\n", isComplete ? "complet" : "non complet");

    // 2. Calculer la hauteur de l'arbre
    int height = calculateHeight(root);
    printf("La hauteur de l'arbre est : %d\n", height);

    // 3. Afficher les �l�ments de l'arbre en parcourant
    printf("Parcours pr�fixe : ");
    preorderTraversal(root);
    printf("\n");

    printf("Parcours infixe : ");
    inorderTraversal(root);
    printf("\n");

    printf("Parcours postfixe : ");
    postorderTraversal(root);
    printf("\n");

    // 4. Rechercher la valeur 5 dans l'arbre et afficher sa profondeur
    int valueToSearch = 5;
    int depth = findNodeDepth(root, valueToSearch, 0);
    if (depth != -1) {
        printf("La valeur %d se trouve � la profondeur %d.\n", valueToSearch, depth);
    } else {
        printf("La valeur %d n'existe pas dans l'arbre.\n", valueToSearch);
    }

    // 5. Supprimer la valeur 4 de l'arbre et afficher l'arbre apr�s la suppression
    root = deleteNode(root, 4);
    printf("Arbre apr�s la suppression de la valeur 4 :\n");
    inorderTraversal(root);
    printf("\n");

    // 6. Ins�rer la valeur 10 dans l'arbre et afficher l'arbre apr�s l'insertion
    root = insertNode(root, 10);
    printf("Arbre apr�s l'insertion de la valeur 10 :\n");
    inorderTraversal(root);
    printf("\n");

    // 7. Trouver le successeur de la valeur 3
    struct Node* successor = findSuccessor(root, 3);
    if (successor != NULL) {
        printf("Le successeur de la valeur 3 est : %d\n", successor->data);
    } else {
        printf("Il n'y a pas de successeur pour la valeur 3\n");
    }

    // 8. Trouver le pr�d�cesseur de la valeur 9
    struct Node* predecessor = findPredecessor(root, 9);
    if (predecessor != NULL) {
        printf("Le pr�d�cesseur de la valeur 9 est : %d\n", predecessor->data);
    } else {
        printf("Il n'y a pas de pr�d�cesseur pour la valeur 9\n");
    }

    // 9. Calculer la profondeur moyenne des n�uds de l'arbre
    float averageDepth = calculateAverageDepth(root, 0) / (float)countNodes(root);
    printf("La profondeur moyenne des n�uds de l'arbre est : %.2f\n", averageDepth);

    // 10. V�rifier si l'arbre est un arbre binaire de recherche valide
    int isValidBinarySearchTree = isBinarySearchTree(root, INT_MIN, INT_MAX);
    printf("L'arbre est %s un arbre binaire de recherche valide.\n", isValidBinarySearchTree ? "" : "non");

    return 0;
}

