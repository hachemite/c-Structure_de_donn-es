#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure pour un n�ud de liste simplement cha�n�e.
struct Node {
    int data; 
    struct Node* next; 
};


// Fonction pour diviser la liste en deux moiti�s.
void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* fast;                       // D�clare un pointeur pour avancer de deux n�uds � la fois.
    struct Node* slow;                       // D�clare un pointeur pour avancer d'un n�ud � la fois.
    slow = source;                           // Initialise 'slow' au d�but de la liste.
    fast = source->next;                     // Initialise 'fast' au second n�ud de la liste.

    // 'fast' avance deux n�uds pour chaque avanc�e d'un n�ud de 'slow'.
    while (fast != NULL) {                   // Tant que 'fast' n'atteint pas la fin de la liste,
        fast = fast->next;                   // avancer 'fast' d'un n�ud.
        if (fast != NULL) {                  // Si 'fast' n'est pas � la fin de la liste apr�s l'avanc�e,
            slow = slow->next;               // avancer 'slow' d'un n�ud,
            fast = fast->next;               // puis avancer 'fast' encore d'un n�ud.
        }
    }

    // 'slow' est maintenant avant le point milieu de la liste, donc diviser la liste � ce niveau.
    *frontRef = source;                      // La premi�re moiti� commence � 'source' (et se termine � slow mais on ne vas affecter sa fin "slow->next = NULL;" qu'apres l' utilisation de l'adresse slow->next pour definir le debut de la seconde moitier : voir ligne suivante).
    *backRef = slow->next;                   // La seconde moiti� commence au n�ud suivant 'slow' et se termine en achevant NULL.
    slow->next = NULL;                       // Apr�s avoir utilis� "slow->next" pour d�finir le d�but de la deuxi�me moiti� de la liste(backRef), on pointe maintenant "slow->next" sur NULL pour d�terminer la fin de la premi�re moiti� de la liste (frontRef ).
}



// Fonction pour fusionner deux listes tri�es en une seule liste tri�e.
struct Node* SortedMerge(struct Node* a, struct Node* b) {
    struct Node* result = NULL;                        // Initialise le pointeur de r�sultat � NULL.

    // Cas de base : si l'une des listes est vide, retourner l'autre liste.
    if (a == NULL)
        return b;                                      // Si 'a' est vide, retourner 'b'.
    else if (b == NULL)
        return a;                                      // Si 'b' est vide, retourner 'a'.

    // S�lectionner le plus petit �l�ment des deux listes.
    if (a->data <= b->data) {
        result = a;                                    // Si l'�l�ment de 'a' est plus petit ou �gal, 'a' devient le d�but de la liste fusionn�e.
        result->next = SortedMerge(a->next, b);        // apres que le premier �l�ment de 'a' est s�l�ctionn�, "repetez la meme op�ration de fusion au niveau de a->next et b" :ce qui veut dire appelez la meme fonction en utilisant ces nouveaux arguments
    } 
    else // if (a->data > b->data)
    {
        result = b;                                    // Sinon, 'b' devient le d�but de la liste fusionn�e.
        result->next = SortedMerge(a, b->next);         // apres que le premier �l�ment de 'b' est s�l�ctionn�, "repetez la meme op�ration de fusion au niveau de a et b->next" :ce qui veut dire appelez la meme fonction en utilisant ces nouveaux arguments
    }
    return result;                                     // Retourner le pointeur vers la t�te de la liste fusionn�e.
}



// Fonction r�cursive pour trier par fusion une liste cha�n�e.
void MergeSort(struct Node** head) {
    struct Node* currentHead = *head;                  // 'currentHead' est un pointeur vers la t�te de la liste � trier.
    struct Node* a;                                    // Pointeur pour la premi�re moiti� de la liste.
    struct Node* b;                                    // Pointeur pour la seconde moiti� de la liste.

    // Cas de base : si la liste est vide ou contient un seul �l�ment, elle est d�j� tri�e.
    if ((currentHead == NULL) || (currentHead->next == NULL)) {
        return;
    }

    // Diviser la liste en deux moiti�s.
    FrontBackSplit(currentHead, &a, &b);               // 'FrontBackSplit' divise la liste en deux moiti�s 'a' et 'b'.

    // Trier r�cursivement chaque moiti�.
    MergeSort(&a);                                     // Tri r�cursif de la premi�re moiti�.
    MergeSort(&b);                                     // Tri r�cursif de la seconde moiti�.

    // Fusionner les deux moiti�s tri�es.
    *head = SortedMerge(a, b);                         // 'SortedMerge' fusionne les deux moiti�s tri�es en une seule liste tri�e.
}




// Fonction pour ins�rer un nouvel �l�ment en t�te de liste.
void insererDebut(struct Node** head, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data; 
    new_node->next = (*head); 
    (*head) = new_node; 
}


// Fonction pour afficher les �l�ments de la liste.
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

    // Cr�ation de la liste en ajoutant des �l�ments. Les �l�ments sont ajout�s au d�but, donc l'ordre sera invers�.
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



/*Prenons l'exemple d'une liste de 4 �l�ments : [4, 3, 2, 1], et voyons comment l'arbre d'appels r�cursifs se d�veloppe pour le tri par fusion.

----Niveau 0---
Liste initiale : [4, 3, 2, 1]
L'action principale � ce niveau est de diviser la liste en deux sous-listes.


----Niveau 1---
-Sous-liste gauche : [4, 3]
Cette liste est divis�e en deux sous-listes plus petites : [4] et [3].
-Sous-liste droite : [2, 1]
De m�me, cette liste est divis�e en [2] et [1].


----Niveau 2---
Sous-listes finales :
� gauche, nous avons [4] et [3], qui sont d�j� "tri�es" car elles contiennent un seul �l�ment. Leur fusion donne [3, 4].
� droite, il en va de m�me pour [2] et [1], dont la fusion donne [1, 2].


----Niveau 3---
Fusion finale :
Les deux sous-listes [3, 4] et [1, 2] sont fusionn�es pour former la liste tri�e finale : [1, 2, 3, 4].
L'arbre d'appels r�cursifs pour ce tri par fusion ressemble � ceci :


                [4, 3, 2, 1]
               /            \
          [4, 3]            [2, 1]
          /    \            /    \
       [4]     [3]        [2]    [1]
          \    /            \    /
         [3, 4]            [1, 2]
               \            /
                [1, 2, 3, 4]

Niveau 0 : l'appel initial de la fonction sur la liste compl�te.
Niveau 1 : l'arbre se divise en deux branches, repr�sentant les appels r�cursifs sur les deux sous-listes.
Niveau 2 : chaque sous-liste est � son tour trait�e r�cursivement, mais ici, puisqu'elles ne contiennent 
           qu'un seul �l�ment, elles sont consid�r�es comme tri�es.
Niveau 3 : la fusion des sous-listes tri�es commence � remonter dans l'arbre, combinant progressivement 
           les �l�ments en listes plus grandes et tri�es jusqu'� ce que la liste compl�te soit reconstitu�e 
		   et tri�e � la racine de l'arbre.




*/
