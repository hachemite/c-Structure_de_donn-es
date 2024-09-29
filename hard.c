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


/* Fonction pour effectuer le tri rapide sur la liste chaînée */
Node* quicksort(Node* head, Node* tail) {
    if (head == NULL || head == tail) {
        return head;
    }

    Node* pivot = head;
    Node* current = head->next;
    Node* last_smaller = NULL;

    while (current != tail) {
        if (current->value < pivot->value) {
            last_smaller = (last_smaller == NULL) ? head : last_smaller->next;
            swap_values(current, last_smaller);
        }
        current = current->next;
    }

    if (last_smaller == NULL) {
        last_smaller = head;
    }
    swap_values(pivot, last_smaller);

    quicksort(head, last_smaller);
    quicksort(last_smaller->next, tail);

    return head;
}


void supprimerElement(IntNode **head, int data) {
    if (*head == NULL) {
        // La liste est vide, donc rien à supprimer
        return;
    }
    // Cas spécial si l'élément à supprimer est à la tête de la liste
    if ((*head)->data == data) {
        IntNode *aSupprimer = *head;             // Sauvegarder le noeud à supprimer
        *head = (*head)->next;                   // Avancer la tête de la liste
        free(aSupprimer);                        // Libérer la mémoire de l'ancien noeud tête
        return;
    }
    // Recherche de l'élément à supprimer
    IntNode *current = *head;                   // Initialiser le pointeur pour parcourir la liste
    while (current->next != NULL && current->next->data != data) {
        current = current->next;                // Avancer dans la liste pour trouver l'élément
    }
    // Supprimer l'élément trouvé, s'il existe
    if (current->next != NULL) {
        IntNode *aSupprimer = current->next;    // Noeud à supprimer
        current->next = aSupprimer->next;       // Relier le noeud précédent au noeud suivant
        free(aSupprimer);                       // Libérer la mémoire du noeud supprimé
    }
	// Si l'élément n'est pas trouvé, informer l'utilisateur
	else {
        printf("Element not found in the list.\n");
    }
}



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


void ajouter_materiel(Liste* liste){
	Materiel materiel;

	printf("veuillez saisie l ID du nouveau materiel a ajouter \n");
	scanf("%d",&materiel.id);

	printf("veuillez saisie le nom du nouveau materiel a ajouter \n");
	scanf("%49s",materiel.nom);

	printf("veuillez saisie le prix du nouveau materiel a ajouter \n");
	scanf("%f",&materiel.prix);

	printf("veuillez saisie la quantite du nouveau materiel a ajouter \n");
	scanf("%d",&materiel.quantite);


	materiel.reference = (char*) malloc(sizeof(char)*100);
	printf("veuillez saisie la reference du nouveau materiel a ajouter \n");
	scanf("%99s",materiel.reference);

	inserer_debut(liste,materiel);
}

void sauvegarder_liste(Liste *liste, char *filename) {
    FILE *file = fopen(filename, "w");                               // Ouvre le fichier en mode écriture.
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier pour écrire.\n");
        return;
    }

    Materiel *current = liste->debut;
    while (current != NULL) {
        fprintf(file, "%d,%s,%f,%s,%d \n", current->id, current->nom, current->prix, current->reference, current->quantite);
        current = current->suivant;
    }

    fclose(file);                                                   // Ferme le fichier après l'écriture.
}


// Necessaire pour implémenter la fonction de la question suivante : charger_liste(liste*, char*)
void vider_liste(Liste* liste) {
    if (liste == NULL) {
        return;
    }
    Materiel* current = liste->debut;
    while (current != NULL) {
        Materiel* aSupprimer = current;
        current = current->suivant;
        free(aSupprimer->reference);
        free(aSupprimer);
    }
    // Réinitialise les pointeurs de début et de fin ainsi que la taille de la liste (c'est le point de difference entre liberer_liste et vider_liste, à cette étape liberer_liste libére la Liste entiere free(liste) )
    liste->debut = NULL;
    liste->fin = NULL;
    liste->taille = 0;
}


//13. charger_liste(liste*, char*) : charge la liste depuis un fichier.
// La fonction charger_liste est conçue pour lire les informations sur des objets de type Materiel
// depuis un fichier texte et les insérer dans une liste chaînée. Cela permet de reconstruire
// une liste chaînée à partir de données existants dans un fichier
void charger_liste(Liste *liste, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier pour lire.\n");
        return;
    }
    vider_liste(liste);                                                             // Vide la liste existante

	int id, quantite;
    char nom[50], reference[100];
    float prix;

    while (fscanf(file, "%d,%49[^,],%f,%99[^,],%d \n", &id, nom, &prix, reference, &quantite) == 5) {
        Materiel* materiel = (Materiel*) malloc(sizeof(Materiel));                   // Crée un nouveau Materiel dynamiquement pour chaque entrée lue
        materiel->id = id;
        strcpy(materiel->nom, nom);
        materiel->prix = prix;
        materiel->quantite = quantite;
        materiel->reference = strdup(reference);
        materiel->suivant = NULL;
        materiel->precedent = NULL;

        inserer_debut(liste, *materiel);                                              // Insère le nouveau Materiel au début de la liste
    }
    fclose(file);
}

