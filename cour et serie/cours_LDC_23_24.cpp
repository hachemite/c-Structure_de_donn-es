#include <stdio.h>
#include <stdlib.h>

// D�finition de la structure d'un �l�ment
typedef struct Element {
    int donnee;                    // Donn�e stock�e dans le n�ud
    struct Element* ptr_precedent; // Pointeur vers le n�ud pr�c�dent dans la liste
    struct Element* ptr_suivant;   // Pointeur vers le n�ud suivant dans la liste
} Element;

//Fonction pour ins�rer un �l�ment au d�but de la liste
void insertAuDebut(Element** debut, int data) {
	// Allocation d'un nouvel �l�ment
  Element* nouveau = (Element*)malloc(sizeof(Element));
  nouveau->donnee = data;
  nouveau->ptr_precedent = NULL;

  // Si la liste est vide, le nouveau �l�ment devient le premier et le dernier �l�ment
  if (*debut == NULL) {
    nouveau->ptr_suivant = NULL;
    *debut = nouveau;
  } else {
    // Sinon, le nouveau �l�ment devient le premier �l�ment et le deuxi�me �l�ment pointe vers lui
    nouveau->ptr_suivant = *debut;
    (*debut)->ptr_precedent = nouveau;
    *debut = nouveau;
  }
}

// Ajout d'un �l�ment � la fin de la liste
void ajoutElementFin(Element** debutRef, int donnee) {
     // Allocation d'un nouvel �l�ment
  Element* nouveau = (Element*)malloc(sizeof(Element));
  nouveau->donnee = donnee;
  nouveau->ptr_suivant = NULL;

  // Si la liste est vide, le nouveau �l�ment devient le premier et le dernier �l�ment
  if (*debutRef == NULL) {
    nouveau->ptr_precedent = NULL;
    *debutRef = nouveau;
  } else {
    // Sinon, on parcourt la liste jusqu'� trouver le dernier �l�ment
    Element* temp = *debutRef;
    while (temp->ptr_suivant != NULL) {
      temp = temp->ptr_suivant;
    }

    // Le dernier �l�ment pointe vers le nouveau �l�ment et le nouveau �l�ment devient le dernier �l�ment
    temp->ptr_suivant = nouveau;
    nouveau->ptr_precedent = temp;
  }
}
// Fonction pour compter le nombre d'�l�ments dans la liste (non fournie dans le prompt)
int countElements(Element* debut, Element* fin) {
  int count = 0;
  Element* temp = debut;
  while (temp != NULL) {
    count++;
    temp = temp->ptr_suivant;
  }
  return count;
  printf("%d",count);
}
// Fonction pour ins�rer un �l�ment � une position donn�e
void insererPosition(Element** debut, Element** fin, int donnee, int position) {
  // Si la position est invalide, on ne fait rien
  if (position < 1 || position > countElements(*debut, *fin) + 1) {
    return;
  }
  // Si la position est 1, on ins�re l'�l�ment au d�but
  if (position == 1) {
    insertAuDebut(debut, donnee);
    return;
  }
  // Si la position est la fin de la liste, on utilise la fonction `ajoutElementFin`
  if (position == countElements(*debut, *fin) + 1) {
    ajoutElementFin(fin, donnee);
    return;
  }
  // Sinon, on parcourt la liste jusqu'� trouver la position d'insertion
  Element* temp = *debut;
  int i = 1;
  while (i < position) {
    temp = temp->ptr_suivant;
    i++;
  }

  // On ins�re le nouvel �l�ment apr�s l'�l�ment � la position `position - 1`
  Element* nouveau = (Element*)malloc(sizeof(Element));
  nouveau->donnee = donnee;
  nouveau->ptr_precedent = temp->ptr_precedent;
  nouveau->ptr_suivant = temp;
  /*la ligne de code ci-dessous met � jour le pointeur ptr_suivant du n�ud pr�c�dent de temp
  pour qu'il pointe vers le nouvel �l�ment nouveau,   ce qui ins�re correctement nouveau 
  dans la liste � la position sp�cifi�e.*/
  temp->ptr_precedent->ptr_suivant = nouveau;
  /*L'instruction temp->ptr_precedent->ptr_suivant = nouveau; remplace le pointeur 
  ptr_suivant de l'�l�ment temp->ptr_precedent par l'adresse du nouveau �l�ment. 
  En d'autres termes, cela relie le nouvel �l�ment � l'�l�ment temp->ptr_precedent*/
  /*Exemple:
  	Supposons que nous avons une liste A -> B -> C et que nous voulons ins�rer un nouvel 
	  �l�ment D avant B.
	temp pointe vers B.
	temp->ptr_precedent pointe vers A.
	ptr_suivant de A pointe actuellement vers B.
	L'instruction temp->ptr_precedent->ptr_suivant = nouveau; modifie 
	le ptr_suivant de A pour qu'il pointe vers D. 
	La nouvelle liste devient ainsi A -> D -> B -> C.
	Conclusion: temp->ptr_precedent->ptr_suivant = nouveau; est une instruction qui met � jour 
	les pointeurs dans une liste doublement cha�n�e pour ins�rer un nouvel �l�ment 
	apr�s un �l�ment existant.
	*/
  temp->ptr_precedent = nouveau;
}
// Fonction pour supprimer le premier �l�ment de la liste
void supprimerDebut(Element** debut) {
  // Si la liste est vide, on ne fait rien
  if (*debut == NULL) {
    return;
  }

  // Si la liste ne contient qu'un seul �l�ment, on le supprime et la liste devient vide
  if ((*debut)->ptr_suivant == NULL) {
    free(*debut);
    *debut = NULL;
    return;
  }

  // Sinon, on d�place le pointeur de d�but vers le deuxi�me �l�ment
  Element* temp = *debut;
  *debut = (*debut)->ptr_suivant;
  (*debut)->ptr_precedent = NULL;

  // On lib�re la m�moire de l'ancien premier �l�ment
  free(temp);
}

// Fonction pour supprimer le dernier �l�ment de la liste
void supprimerFin(Element** debut) {
  // Si la liste est vide, on ne fait rien
  if (*debut == NULL) {
    return;
  }

  // Si la liste ne contient qu'un seul �l�ment, on le supprime et la liste devient vide
  if ((*debut)->ptr_suivant == NULL) {
    free(*debut);
    *debut = NULL;
    return;
  }

  // On parcourt la liste jusqu'� trouver l'�l�ment pr�c�dent du dernier �l�ment
  Element* temp = *debut;
  while (temp->ptr_suivant->ptr_suivant != NULL) {
    temp = temp->ptr_suivant;
  }

  // On lib�re la m�moire du dernier �l�ment et on met � jour les pointeurs
  free(temp->ptr_suivant);
  temp->ptr_suivant = NULL;
}
// Fonction pour supprimer un �l�ment � une position donn�e
void suppremerPosition(Element** debut, int position) {
  // Si la position est invalide, on ne fait rien
  if (position < 1 || position > countElements(*debut, NULL) + 1) {
    return;
  }

  // Si la position est 1, on supprime le premier �l�ment
  if (position == 1) {
    supprimerDebut(debut);
    return;
  }

  // Si la position est la fin de la liste, on supprime le dernier �l�ment
  if (position == countElements(*debut, NULL) + 1) {
    supprimerFin(debut);
    return;
  }

  // Sinon, on parcourt la liste jusqu'� trouver l'�l�ment � supprimer
  Element* temp = *debut;
  int i = 1;
  while (i < position) {
    temp = temp->ptr_suivant;
    i++;
  }

  // On retire l'�l�ment de la liste et on lib�re sa m�moire
  temp->ptr_precedent->ptr_suivant = temp->ptr_suivant;
  temp->ptr_suivant->ptr_precedent = temp->ptr_precedent;
  free(temp);
}
// Affichage de la liste
void afficherListe(Element* debut) {
    Element* temp = debut;
    while (temp != NULL) {
        printf("%d<=>", temp->donnee);
        temp = temp->ptr_suivant;
    }
    printf("NULL");
    printf("\n");
}

// Exemple d'utilisation
int main() {
    Element* debut = NULL;
    Element* fin = NULL;

    // Insertions et suppressions d'�l�ments
    insertAuDebut(&debut, 10);
    ajoutElementFin(&debut, 20);
    ajoutElementFin(&debut, 30);
    insererPosition(&debut, &fin, 15, 1);
        // Affichage de la liste
    afficherListe(debut);
    int nbElements = countElements(debut,fin);
	printf("\nNombre d'�l�ments dans la liste : %d\n", nbElements);
    printf("\n------------------\n");
    supprimerDebut(&debut);
    supprimerFin(&debut);
    suppremerPosition(&debut, 0);
    // Affichage de la liste
    afficherListe(debut);
    int nbElementsRestant = countElements(debut,fin);
    printf("\nNombre d'�l�ments dans la liste : %d\n", nbElementsRestant);
    return 0;
}

