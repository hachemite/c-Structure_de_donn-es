#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure de données pour une pile
typedef struct {
    int* array;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isStackFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack* stack, int item) {
    if (isStackFull(stack)) {
        printf("Stack is full.\n");
        return;
    }
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isStackEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->array[stack->top--];
}

// Structure de données pour une file
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

int main() {
    // Tests pour la pile (stack)
    Stack* stack = createStack(5);
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    printf("Popped from stack: %d\n", pop(stack));
    printf("Popped from stack: %d\n", pop(stack));

    // Tests pour la file (queue)
    Queue* queue = createQueue(5);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    printf("Dequeued from queue: %d\n", dequeue(queue));
    printf("Dequeued from queue: %d\n", dequeue(queue));

    free(stack->array);
    free(stack);
    free(queue->array);
    free(queue);

    return 0;
}
