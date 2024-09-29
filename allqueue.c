BY ME
typedef struct {
    int* array;
    int front, rear, size, capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

bool isQueueFull(Queue* queue) {
    return queue->size == queue->capacity;
}

void enqueue(Queue* queue, int item) {
    if (isQueueFull(queue)) {
        printf("Queue is full.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}





















COURS
struct Queue {
struct Node* front;
struct Node* rear;
};
struct Queue* createQueue() {
struct Queue* newQueue = (struct Queue*)malloc(sizeof(struct Queue));
newQueue->front = newQueue->rear = NULL;
return newQueue;
}
struct Node* createNode(int data) {
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
newNode->data = data;
newNode->next = NULL;
return newNode;
}
void enqueue(struct Queue* queue, int data) {
struct Node* newNode = createNode(data);
if (queue->rear == NULL) { // si la file est vide
queue->front = queue->rear = newNode;
return;
}
queue->rear->next = newNode;
queue->rear = newNode;
}

int dequeue(struct Queue* queue) {
if (queue->front == NULL) { // vérifie si la file est vide
printf("La file est vide.\n");
return -1;
}
struct Node* temp = queue->front;
int dequeued = temp->data;
queue->front = queue->front->next;
if (queue->front == NULL) { // si la file est maintenant vide
queue->rear = NULL;
}
free(temp);
return dequeued;
}
void printQueue(struct Queue* queue) {
struct Node* currentNode = queue->front;
while (currentNode != NULL) {
printf("%d ", currentNode->data);
currentNode = currentNode->next;
}
printf("\n");
}
















TP AMANE

// Structure de données pour représenter une file
typedef struct {
    int* array;     // Tableau dynamique pour stocker les éléments de la file
    int front;      // Indice du début de la file
    int rear;       // Indice de la fin de la file
    int capacity;   // Capacité maximale de la file
} Queue;

Queue* create_queue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour la file.\n");
        exit(EXIT_FAILURE);
    }
    queue->array = (int*)malloc(capacity * sizeof(int));
    if (queue->array == NULL) {
        printf("Erreur lors de l'allocation de mémoire pour le tableau de la file.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Fonction pour vérifier si la file est vide
int is_queue_empty(Queue* queue) {
    return queue->rear < queue->front;
}

// Fonction pour vérifier si la file est pleine
int is_queue_full(Queue* queue) {
    return queue->rear == queue->capacity - 1;
}

// Fonction pour enfiler un élément dans la file
void enqueue(Queue* queue, int item) {
    if (is_queue_full(queue)) {
        printf("Erreur : la file est pleine, impossible d'enfiler.\n");
        return;
    }
    queue->array[++queue->rear] = item;
    printf("%d a été enfilé avec succès.\n", item);
}

// Fonction pour défiler un élément de la file
int dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Erreur : la file est vide, impossible de défiler.\n");
        exit(EXIT_FAILURE);
    }
    return queue->array[queue->front++];
}






SERIE 5
struct Queue {
    struct Node** array;
    int front, rear;
    unsigned capacity;
};

// Fonction pour créer une file avec une capacité donnée
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (struct Node**)malloc(queue->capacity * sizeof(struct Node*));
    return queue;
}

// Fonction pour vérifier si la file est vide
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Fonction pour vérifier si la file est pleine
int isFull(struct Queue* queue) {
    return (queue->rear + 1) % queue->capacity == queue->front;
}

// Fonction pour ajouter un élément à la file
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

// Fonction pour retirer un élément de la file
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

// Fonction pour vérifier si l'arbre est complet
// Fonction pour vérifier si l'arbre est complet
int isCompleteBinaryTree(struct Node* root) {
    if (root == NULL) {
        return 1;
    }

    struct Queue* queue = createQueue(1000); // Création de la file

    // Enfiler la racine
    enqueue(queue, root);

    int flag = 0; // Indicateur pour vérifier si un nœud sans enfant a été rencontré

    // Parcourir l'arbre en largeur
    while (!isEmpty(queue)) {
        struct Node* tempNode = dequeue(queue);

        // Si un nœud sans enfant a été rencontré précédemment et le nœud actuel a des enfants
        if (tempNode->left == NULL && tempNode->right != NULL) {
            return 0;
        }

        // Si un nœud sans enfant a été rencontré précédemment et le nœud actuel n'a pas d'enfant
        if ((tempNode->left != NULL && tempNode->right == NULL) || (flag && (tempNode->left != NULL || tempNode->right != NULL))) {
            return 0;
        }

        // Si le nœud actuel a un enfant gauche
        if (tempNode->left != NULL) {
            enqueue(queue, tempNode->left);
        } else {
            flag = 1; // Marquer qu'un nœud sans enfant a été rencontré
        }

        // Si le nœud actuel a un enfant droit
        if (tempNode->right != NULL) {
            enqueue(queue, tempNode->right);
        } else {
            flag = 1; // Marquer qu'un nœud sans enfant a été rencontré
        }
    }

    // Si l'arbre a été parcouru sans problèmes, il est complet
    return 1;
}
