#include <stdio.h>
#include <stdlib.h>

// Structure de donn�es pour repr�senter une pile
typedef struct {
    int* array;     // Tableau dynamique pour stocker les �l�ments de la pile
    int top;        // Indice du sommet de la pile
    int capacity;   // Capacit� maximale de la pile
} Stack;

// Structure de donn�es pour repr�senter une file
typedef struct {
    int* array;     // Tableau dynamique pour stocker les �l�ments de la file
    int front;      // Indice du d�but de la file
    int rear;       // Indice de la fin de la file
    int capacity;   // Capacit� maximale de la file
} Queue;

// Fonction pour cr�er une pile de capacit� donn�e
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Fonction pour v�rifier si la pile est vide
int is_stack_empty(Stack* stack) {
    return stack->top == -1;
}

// Fonction pour v�rifier si la pile est pleine
int is_stack_full(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Fonction pour empiler un �l�ment sur la pile
void push(Stack* stack, int item) {
    if (is_stack_full(stack)) {
        printf("Erreur : la pile est pleine, impossible d'empiler.\n");
        return;
    }
    //stack->array[++stack->top] = item;
    // Incr�menter le sommet de la pile
    stack->top++;
// Ajouter l'�l�ment � la position indiqu�e par le sommet de la pile
    stack->array[stack->top] = item;
    printf("%d a �t� empil� avec succ�s.\n", item);
}

// Fonction pour d�piler un �l�ment de la pile
int pop(Stack* stack) {
    if (is_stack_empty(stack)) {
        printf("Erreur : la pile est vide, impossible de d�piler.\n");
        exit(EXIT_FAILURE);
    }
    return stack->array[stack->top--];
}
// Fonction pour afficher les �l�ments de la pile
void display_stack(Stack* stack) {
    // V�rifier si la pile est vide
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


// Fonction pour cr�er une file de capacit� donn�e
Queue* create_queue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Erreur lors de l'allocation de m�moire pour la file.\n");
        exit(EXIT_FAILURE);
    }
    queue->array = (int*)malloc(capacity * sizeof(int));
    if (queue->array == NULL) {
        printf("Erreur lors de l'allocation de m�moire pour le tableau de la file.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

// Fonction pour v�rifier si la file est vide
int is_queue_empty(Queue* queue) {
    return queue->rear < queue->front;
}

// Fonction pour v�rifier si la file est pleine
int is_queue_full(Queue* queue) {
    return queue->rear == queue->capacity - 1;
}

// Fonction pour enfiler un �l�ment dans la file
void enqueue(Queue* queue, int item) {
    if (is_queue_full(queue)) {
        printf("Erreur : la file est pleine, impossible d'enfiler.\n");
        return;
    }
    queue->array[++queue->rear] = item;
    printf("%d a �t� enfil� avec succ�s.\n", item);
}

// Fonction pour d�filer un �l�ment de la file
int dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Erreur : la file est vide, impossible de d�filer.\n");
        exit(EXIT_FAILURE);
    }
    return queue->array[queue->front++];
}

int main() {
    int capacity;
    int choice, item;

    // Demander � l'utilisateur de sp�cifier la capacit� de la pile et de la file
    printf("Entrez la capacit� de la pile et de la file : ");
    scanf("%d", &capacity);

    // Cr�er une pile et une file avec la capacit� sp�cifi�e
    Stack* stack = create_stack(capacity);
    Queue* queue = create_queue(capacity);

    do {
        // Afficher le menu des op�rations
        printf("\n");
        printf("1. Empiler (Pile)\n");
        printf("2. D�piler (Pile)\n");
        printf("3. Enfiler (File)\n");
        printf("4. D�filer (File)\n");
        printf("5. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Empiler (Pile)
                printf("Entrez l'�l�ment � empiler : ");
                scanf("%d", &item);
                push(stack, item);
                break;
            case 2: // D�piler (Pile)
                if (!is_stack_empty(stack)) {
                    printf("El�ment d�piler : %d\n", pop(stack));
                }
                break;
            case 3: // Enfiler (File)
                printf("Entrez l'�l�ment � enfiler : ");
                scanf("%d", &item);
                enqueue(queue, item);
                break;
            case 4: // D�filer (File)
                if (!is_queue_empty(queue)) {
                    printf("El�ment d�filer : %d\n", dequeue(queue));
                }
            case 5: // afficher (pile)
                if (!is_stack_empty(stack)) {
                    display_stack(stack);
                }

            case 6: // Quitter
                printf("Programme termin�.\n");
                break;
            default:
                printf("Choix invalide. Veuillez r�essayer.\n");
        }
    } while (choice != 5);

    // Lib�rer la m�moire allou�e pour la pile et la file
    free(stack->array);
    free(stack);
    free(queue->array);
    free(queue);

    return 0;
}

