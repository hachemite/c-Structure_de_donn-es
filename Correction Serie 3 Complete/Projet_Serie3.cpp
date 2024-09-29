#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Contact{
	char *nom;
	char *numeroTelephone;
}Contact;

typedef struct Node{
	Contact contact;
	struct Node *next;
}Node;

// A.1. Le programme doit permettre a l utilisateur d ajouter de nouveaux 
//     contacts en saisissant leur nom et leur numero de telephone.

Node *creerContact(char *nom, char *numeroTelephone){
	Node *newContact = (Node*) malloc(sizeof(Node));
	
	if(newContact == NULL){
		printf("Erreur Allocation Memoire");
		exit(EXIT_FAILURE);
	}
	newContact->contact.nom = strdup(nom);
	newContact->contact.numeroTelephone = strdup(numeroTelephone); 
	newContact->next = NULL;
	return newContact;
}

void ajouterContact(Node **head, char *nom, char *numeroTelephone){
	Node *newContact = creerContact(nom, numeroTelephone);
	newContact->next = *head;
	*head = newContact;
}


// A.2. Il devrait �galement offrir la possibilit� de rechercher des 
//      contacts existants en fonction de leur nom.

Node* chercherContact(Node *head, char *nom) {
    if (head == NULL) {                                           // V�rifie si la liste est vide.
        printf("La liste est vide.\n");
        return NULL;                                              // Retourne NULL si la liste est vide.
    }

    Node *current = head;                                         // Initialise 'current' au d�but de la liste pour parcourir.
    while (current != NULL && strcmp(current->contact.nom, nom) != 0) { // Continue tant que la fin de la liste n'est pas atteinte et que le nom ne correspond pas.
        current = current->next;                                 
    }

    if (current != NULL) {                                        // Si 'current' n'est pas NULL, le contact a �t� trouv� :strcmp(current->contact.nom, nom) = 0.
        printf("Contact trouve !!!\n");
        return current;                                           // Retourne le pointeur vers le contact trouv�.
    } 
	else {
        printf("Contact introuvable.\n");                         // Si 'current' est NULL, le contact n'a pas �t� trouv� : strcmp(current->contact.nom, nom) != 0.
        return NULL;                                              // Retourne NULL.
    }
}


// A.3. Ecrivez des fonctions pour supprimer des contacts de l�annuaire t�l�phonique.

void supprimerContact(Node **head, char *nom) {
    if (*head == NULL) {                                                       // V�rifie si la liste est vide.
        printf("La liste est vide, aucun element � supprimer.\n");
        return;
    }

    // Supprimer le premier �l�ment si c'est celui � supprimer
    while (*head != NULL && strcmp((*head)->contact.nom, nom) == 0) {          // Boucle pour g�rer la suppression au d�but si le nom correspond.
        Node *aSupprimer = *head;                                              // Sauvegarder le n�ud � supprimer.
        *head = (*head)->next;                                                 // Avancer la t�te de liste.
        free(aSupprimer->contact.nom);                                         // Lib�rer le nom du contact.
        free(aSupprimer->contact.numeroTelephone);                             // Lib�rer le num�ro de t�l�phone du contact.
        free(aSupprimer);                                                      // Lib�rer le n�ud.
        printf("Contact supprime avec succes.\n");
    }

    Node *current = *head;                                                     // Initialiser 'current' pour parcourir la liste depuis le d�but.
    while (current->next != NULL && strcmp(current->next->contact.nom, nom) != 0) { 
        current = current->next;                                               
    }

    if (current->next != NULL) {                                               // Si le contact � supprimer a �t� trouv�: strcmp(current->next->contact.nom, nom) != 0.
        Node *aSupprimer = current->next;                                      // Sauvegarder le n�ud � supprimer.
        current->next = aSupprimer->next;                                      // R�affecter le pointeur next pour exclure 'aSupprimer' de la liste.
        free(aSupprimer->contact.nom);                                         // Lib�rer le nom du contact.
        free(aSupprimer->contact.numeroTelephone);                             // Lib�rer le num�ro de t�l�phone du contact.
        free(aSupprimer);                                                      // Lib�rer le n�ud.
        printf("Contact supprime avec succes.\n");
    } 
	else {                                                                   // Si on arrive ici, le contact n'a pas �t� trouv�.
        printf("Contact introuvable.\n");
    }
}

                  
// B.1. Une fois la liste de contacts construite, l�utilisateur doit avoir la 
//      possibilit� de d�clencher le tri de l�annuaire.

void permuteValeur(Node *node1, Node *node2) {  // Attention, dans les algorithmes de tri, la fonction permuteValeur est destin�e � permuter les donn�es ('Contact') entre deux n�uds, sans changer leur position dans la liste.
    Contact temp = node1->contact; 
	node1->contact = node2->contact;                       
    node2->contact = temp;                                 
}

Node* quicksort(Node *head, Node *tail) {                  

    if (head == NULL || head == tail) {                             
        return head;
    }
    Node *pivot = head;                                          
    Node *current = head->next;                               
    Node *last_smaller = NULL;                                   

    while (current != NULL) {           
        if (strcmp(current->contact.nom, pivot->contact.nom) < 0) {           // la seule ligne qui change en fonction du type de donn�e � comparer. S'il s'agit d'une donn�e de type int on aura : if(current->donnee < pivot->donnee )                 
            last_smaller = (last_smaller == NULL) ? head->next : last_smaller->next; 
            permuteValeur(current, last_smaller);                   
        }
        current = current->next;                                 
    }
    
    if (last_smaller == NULL) {                                    
        last_smaller = head;
    } else {
        permuteValeur(pivot, last_smaller);                              
    }
    quicksort(head, last_smaller);                                 
    quicksort(last_smaller->next, tail);                        

    return head;                                                   
}



// B.2. Le programme doit afficher l�annuaire t�l�phonique tri� par ordre alphab�tique 
//      apr�s l�application de l�algorithme de tri rapide.

void afficherAnnuaire(Node *head) {
	if(head == NULL){
		printf("Annuaire telephonique vide \n");
		return;
	}
    printf("Annuaire telephonique trie:\n");
    Node *current = head;
    while (current != NULL) {
        printf("Nom: %s, Numero de Telephone: %s\n", current->contact.nom, current->contact.numeroTelephone);
        current = current->next;
    }
}



/* C. Interface Utilisateur : D�veloppez une interface utilisateur conviviale permettant 
                              � l�utilisateur d�interagir avec l�annuaire t�l�phonique. 
                              L�interface devrait permettre d�ajouter de nouveaux contacts, 
							  de rechercher des contacts existants et d�afficher l�annuaire tri�.*/

// Fonction pour ajouter le contact dont les informations sont fournies par l'utilisateur							  
void ajouterContactUtilisateur(Node **head) {
    char nom[100], numero[20];

    printf("Entrez le nom du contact : ");
    scanf(" %99s", nom); 

    printf("Entrez le numero de telephone : ");
    scanf("%19s", numero); 
    
    ajouterContact(head, nom, numero);                          // Appeler la fonction qu'on a d�j� d�finie "ajouterContact" pour ajouter le contact dont les informations ont �t� fournies par l'utilisateur.
}

// Fonction pour chercher le contact dont les informations sont fournies par l'utilisateur
void chercherContactUtilisateur(Node *head) {
    char nom[100];
    printf("Entrez le nom du contact � rechercher : ");
    scanf("%99s", nom);
    chercherContact(head, nom);                                // Appeler la fonction qu'on a d�j� d�finie "chercherContact" pour chercher le contact dont les informations ont �t� fournies par l'utilisateur.

}

void libererListe(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next; 
        free(temp->contact.nom); 
        free(temp->contact.numeroTelephone); 
        free(temp); 
    }
}


							  
int main() {
    Node *head = NULL;
    int choix;

    do {
        printf("\nAnnuaire Telephonique\n");
        printf("1. Ajouter un nouveau contact\n");
        printf("2. Rechercher un contact existant\n");
        printf("3. Afficher l'annuaire trie\n");
        printf("4. Quitter\n");
        
		printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterContactUtilisateur(&head);
                break;
            case 2:
                chercherContactUtilisateur(head);
                break;
            case 3:
                head = quicksort(head, NULL); 
                afficherAnnuaire(head);
                break;
            case 4:
                printf("Merci d'avoir utilise notre annuaire telephonique.\n");
                break;
            default:
                printf("Option invalide, veuillez reessayer.\n");
        }
    } while (choix != 4);

    
	// Lib�ration de la m�moire allou�e
    libererListe(head);

    return 0;
}
