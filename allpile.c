BY ME
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


COURs

struct Node {
	int value;
	struct Node* next;
};

struct Stack {
	struct Node* top;
};

void init_stack(struct Stack* stack) {
	stack->top = NULL;
}

void push(struct Stack* stack, int value) {
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));
	node->value = value;
	node->next = stack->top;
	stack->top = node;
}

int pop(struct Stack* stack) {
	if (stack->top == NULL) {
		printf("Stack is empty");
		exit(1);
}

		int value = stack->top->value;
		struct Node* temp = stack->top;
		stack->top = stack->top->next;
		free(temp);
		return value;
}























COURS PROGRAMME

struct Element
{
    int valeur;
    Element *suivant;
};

struct Pile
{
    Element *premier;
};

struct Liste
{
    int longueur;
    Element *Tete;
};

// Fonction pour allouer de la mémoire à une nouvelle liste
Liste* Allouer()
{
    Liste* New=(Liste*)malloc(sizeof(Liste));

    New->longueur=0;
    New->Tete=NULL;

    return New;
}

// Fonction pour empiler un élément sur une pile
void Empiler(Pile *pile, int valeur)
{
    Element *New=(Element*)malloc(sizeof(Element));
    New->valeur=valeur;
    New->suivant=pile->premier;
    pile->premier=New;
}

// Fonction pour ajouter un élément au début d'une liste
void AjouDebut(Liste* liste, int valeur)
{
    Element *New=(Element*)malloc(sizeof(Element));

    New->valeur=valeur;
    New->suivant=liste->Tete;
    liste->Tete=New;
    liste->longueur++;
}

// Fonction pour afficher une liste
void AfficherL(Liste* liste)
{
    Element* tmp=liste->Tete;
    printf("\n ");
    while(tmp!=NULL)
    {
        printf(" %d -> ", tmp->valeur);
        tmp=tmp->suivant;
    }
    printf(" NULL \n ");
}

// Fonction pour afficher une pile
void AfficherP(Pile *pile)
{
    Element* tmp=pile->premier;
    while(tmp!=NULL)
    {
        printf("\t\t%d\n", tmp->valeur);
        tmp=tmp->suivant;
    }
    printf("\t\tNULL\n\n");
}

// Fonction pour permuter les valeurs de deux éléments
void Permuter(Element *a, Element *b)
{
    int t;
    t=a->valeur;
    a->valeur=b->valeur;
    b->valeur=t;
}

// Fonction pour supprimer un élément ayant une certaine valeur dans une liste
void SuppVal(Liste *liste, int Valeur)
{
    Element* tmp=liste->Tete;
    while(tmp!=NULL)
    {
        if(tmp->valeur==Valeur)
            Precedent(tmp,liste)->suivant = tmp->suivant;
        tmp=tmp->suivant;
    }
    liste->longueur--;
}

// Fonction pour supprimer le premier élément d'une liste
void SuppDebut(Liste* liste)
{
    Element* tmp=liste->Tete;
    liste->Tete=tmp->suivant;
    free(tmp);
}

// Fonction pour trouver l'élément précédent dans une liste
Element *Precedent(Element* E, Liste *L)
{
    Element *R;
    if(E==(L->Tete))
        return NULL;
    else
        for(R=L->Tete; R->suivant!=E; R=R->suivant);
    return R;
}





TP AMANE
typedef struct {
    int* array;     // Tableau dynamique pour stocker les éléments de la pile
    int top;        // Indice du sommet de la pile
    int capacity;   // Capacité maximale de la pile
} Stack;

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


