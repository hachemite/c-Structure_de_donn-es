#include <stdio.h>
#include <stdlib.h>

// Structure de données pour représenter une pile
typedef struct {
    int* array;     // Tableau dynamique pour stocker les éléments de la pile
    int top;        // Indice du sommet de la pile
    int capacity;   // Capacité maximale de la pile
} Stack;

// Structure de données pour représenter une file
typedef struct {
    int* array;     // Tableau dynamique pour stocker les éléments de la file
    int front;      // Indice du début de la file
    int rear;       // Indice de la fin de la file
    int capacity;   // Capacité maximale de la file
} Queue;

// Fonction pour créer une pile de capacité donnée
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Fonction pour vérifier si la pile est vide
int is_stack_empty(Stack* stack) {
    return stack->top == -1;
}

// Fonction pour vérifier si la pile est pleine
int is_stack_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Fonction pour empiler un élément sur la pile
void push(Stack* stack, int item) {
    if (is_stack_full(stack)) {
        printf("Erreur : la pile est pleine, impossible d'empiler.\n");
        return;
    }
    //stack->array[++stack->top] = item;
    // Incrémenter le sommet de la pile
    stack->top++;
// Ajouter l'élément à la position indiquée par le sommet de la pile
    stack->array[stack->top] = item;
    printf("%d a été empilé avec succès.\n", item);
}

// Fonction pour dépiler un élément de la pile
int pop(Stack* stack) {
    if (is_stack_empty(stack)) {
        printf("Erreur : la pile est vide, impossible de dépiler.\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}
// Fonction pour afficher les éléments de la pile
void display_stack(Stack* stack) {
    // Vérifier si la pile est vide
    if (is_stack_empty(stack)) {
        printf("La pile est vide.\n");
        return;
    }

    // Parcourir la pile du sommet au bas
    printf("Contenu de la pile (du sommet au bas) : ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}


// Fonction pour créer une file de capacité donnée
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

int main() {
    int capacity;
    int choice, item;

    // Demander à l'utilisateur de spécifier la capacité de la pile et de la file
    printf("Entrez la capacité de la pile et de la file : ");
    scanf("%d", &capacity);

    // Créer une pile et une file avec la capacité spécifiée
    Stack* stack = create_stack(capacity);
    Queue* queue = create_queue(capacity);

    do {
        // Afficher le menu des opérations
        printf("\n");
        printf("1. Empiler (Pile)\n");
        printf("2. Dépiler (Pile)\n");
        printf("3. Enfiler (File)\n");
        printf("4. Défiler (File)\n");
        printf("5. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Empiler (Pile)
                printf("Entrez l'élément à empiler : ");
                scanf("%d", &item);
                push(stack, item);
                break;
            case 2: // Dépiler (Pile)
                if (!is_stack_empty(stack)) {
                    printf("Elément dépiler : %d\n", pop(stack));
                }
                break;
            case 3: // Enfiler (File)
                printf("Entrez l'élément à enfiler : ");
                scanf("%d", &item);
                enqueue(queue, item);
                break;
            case 4: // Défiler (File)
                if (!is_queue_empty(queue)) {
                    printf("Elément défiler : %d\n", dequeue(queue));
                }
            case 5: // afficher (pile)
                if (!is_stack_empty(stack)) {
                    display_stack(stack);
                }

            case 6: // Quitter
                printf("Programme terminé.\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 5);

    // Libérer la mémoire allouée pour la pile et la file
    free(stack->array);
    free(stack);
    free(queue->array);
    free(queue);

    return 0;
}

