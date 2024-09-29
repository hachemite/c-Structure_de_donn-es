#include <stdio.h>
#include <stdlib.h>

// Définition de la structure pour un nœud de liste simplement chaînée.
struct Node {
    int data; 
    struct Node* next; 
};


// Fonction pour diviser la liste en deux moitiés.
void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* fast;                       // Déclare un pointeur pour avancer de deux nœuds à la fois.
    struct Node* slow;                       // Déclare un pointeur pour avancer d'un nœud à la fois.
    slow = source;                           // Initialise 'slow' au début de la liste.
    fast = source->next;                     // Initialise 'fast' au second nœud de la liste.

    // 'fast' avance deux nœuds pour chaque avancée d'un nœud de 'slow'.
    while (fast != NULL) {                   // Tant que 'fast' n'atteint pas la fin de la liste,
        fast = fast->next;                   // avancer 'fast' d'un nœud.
        if (fast != NULL) {                  // Si 'fast' n'est pas à la fin de la liste après l'avancée,
            slow = slow->next;               // avancer 'slow' d'un nœud,
            fast = fast->next;               // puis avancer 'fast' encore d'un nœud.
        }
    }

    // 'slow' est maintenant avant le point milieu de la liste, donc diviser la liste à ce niveau.
    *frontRef = source;                      // La première moitié commence à 'source' (et se termine à slow mais on ne vas affecter sa fin "slow->next = NULL;" qu'apres l' utilisation de l'adresse slow->next pour definir le debut de la seconde moitier : voir ligne suivante).
    *backRef = slow->next;                   // La seconde moitié commence au nœud suivant 'slow' et se termine en achevant NULL.
    slow->next = NULL;                       // Après avoir utilisé "slow->next" pour définir le début de la deuxième moitié de la liste(backRef), on pointe maintenant "slow->next" sur NULL pour déterminer la fin de la première moitié de la liste (frontRef ).
}



// Fonction pour fusionner deux listes triées en une seule liste triée.
struct Node* SortedMerge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;                        // Initialise le pointeur de résultat à NULL.

    // Cas de base : si l'une des listes est vide, retourner l'autre liste.
    if (a == NULL)
        return b;                                      // Si 'a' est vide, retourner 'b'.
    else if (b == NULL)
        return a;                                      // Si 'b' est vide, retourner 'a'.

    // Sélectionner le plus petit élément des deux listes.
    if (a->data <= b->data) {
        result = a;                                    // Si l'élément de 'a' est plus petit ou égal, 'a' devient le début de la liste fusionnée.
        result->next = SortedMerge(a->next, b);        // apres que le premier élément de 'a' est séléctionné, "repetez la meme opération de fusion au niveau de a->next et b" :ce qui veut dire appelez la meme fonction en utilisant ces nouveaux arguments
    } 
    else // if (a->data > b->data)
    {
        result = b;                                    // Sinon, 'b' devient le début de la liste fusionnée.
        result->next = SortedMerge(a, b->next);         // apres que le premier élément de 'b' est séléctionné, "repetez la meme opération de fusion au niveau de a et b->next" :ce qui veut dire appelez la meme fonction en utilisant ces nouveaux arguments
    }
    return result;                                     // Retourner le pointeur vers la tête de la liste fusionnée.
}



// Fonction récursive pour trier par fusion une liste chaînée.
void MergeSort(struct Node** head) {
    struct Node* currentHead = *head;                  // 'currentHead' est un pointeur vers la tête de la liste à trier.
    struct Node* a;                                    // Pointeur pour la première moitié de la liste.
    struct Node* b;                                    // Pointeur pour la seconde moitié de la liste.

    // Cas de base : si la liste est vide ou contient un seul élément, elle est déjà triée.
    if ((currentHead == NULL) || (currentHead->next == NULL)) {
        return;
    }

    // Diviser la liste en deux moitiés.
    FrontBackSplit(currentHead, &a, &b);               // 'FrontBackSplit' divise la liste en deux moitiés 'a' et 'b'.

    // Trier récursivement chaque moitié.
    MergeSort(&a);                                     // Tri récursif de la première moitié.
    MergeSort(&b);                                     // Tri récursif de la seconde moitié.

    // Fusionner les deux moitiés triées.
    *head = SortedMerge(a, b);                         // 'SortedMerge' fusionne les deux moitiés triées en une seule liste triée.
}




// Fonction pour insérer un nouvel élément en tête de liste.
void insererDebut(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data; 
    new_node->next = (*head); 
    (*head) = new_node; 
}


// Fonction pour afficher les éléments de la liste.
void afficherList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next; 
    }

}

/*
void printInverse(struct Node* node){
	if(node == NULL){
		return;
	}
	else{
		printInverse(node->next);
		printf("%d ", node->data);
	}
}

*/

int main() {
   
    struct Node* head = NULL; 

    // Création de la liste en ajoutant des éléments. Les éléments sont ajoutés au début, donc l'ordre sera inversé.
    insererDebut(&head, 2); 
    insererDebut(&head, 1); 
    insererDebut(&head, 4); 
    insererDebut(&head, 3);

    printf("Liste avant le trie :\n");
    afficherList(head); 
    
    MergeSort(&head);
    printf("\nListe apres le trie :\n");
    afficherList(head); 

    return 0;
}



/*Prenons l'exemple d'une liste de 4 éléments : [4, 3, 2, 1], et voyons comment l'arbre d'appels récursifs se développe pour le tri par fusion.

----Niveau 0---
Liste initiale : [4, 3, 2, 1]
L'action principale à ce niveau est de diviser la liste en deux sous-listes.


----Niveau 1---
-Sous-liste gauche : [4, 3]
Cette liste est divisée en deux sous-listes plus petites : [4] et [3].
-Sous-liste droite : [2, 1]
De même, cette liste est divisée en [2] et [1].


----Niveau 2---
Sous-listes finales :
À gauche, nous avons [4] et [3], qui sont déjà "triées" car elles contiennent un seul élément. Leur fusion donne [3, 4].
À droite, il en va de même pour [2] et [1], dont la fusion donne [1, 2].


----Niveau 3---
Fusion finale :
Les deux sous-listes [3, 4] et [1, 2] sont fusionnées pour former la liste triée finale : [1, 2, 3, 4].
L'arbre d'appels récursifs pour ce tri par fusion ressemble à ceci :


                [4, 3, 2, 1]
               /            \
          [4, 3]            [2, 1]
          /    \            /    \
       [4]     [3]        [2]    [1]
          \    /            \    /
         [3, 4]            [1, 2]
               \            /
                [1, 2, 3, 4]

Niveau 0 : l'appel initial de la fonction sur la liste complète.
Niveau 1 : l'arbre se divise en deux branches, représentant les appels récursifs sur les deux sous-listes.
Niveau 2 : chaque sous-liste est à son tour traitée récursivement, mais ici, puisqu'elles ne contiennent 
           qu'un seul élément, elles sont considérées comme triées.
Niveau 3 : la fusion des sous-listes triées commence à remonter dans l'arbre, combinant progressivement 
           les éléments en listes plus grandes et triées jusqu'à ce que la liste complète soit reconstituée 
		   et triée à la racine de l'arbre.




*/
