#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct materiel {
    int id;                 
    char nom[50];          
    float prix;           
    int quantite;          
    char *reference;     // ajouter l attribut reference   
    struct materiel *precedent; 
    struct materiel *suivant;   
} Materiel;

typedef struct liste {
   Materiel* debut;
   Materiel* fin;
int taille;
}Liste;

//1. initialiser_liste() : initialise une liste vide.
Liste* initialiserLDC() {                                          // Allouer de la m�moire � une nouvelle liste doublement cha�n�e (LDC)
    Liste* newListe = (Liste*) malloc(sizeof(Liste));              // Allocation m�moire pour la nouvelle liste
    if (newListe == NULL) {                                        // V�rification de l'�chec de l'allocation m�moire
        printf("Erreur allocation memoire");
        exit(EXIT_FAILURE);                                        // Arr�t du programme en cas d'�chec d'allocation
    }
    newListe->debut = NULL;                                        // Initialisation du pointeur de d�but � NULL
    newListe->fin = NULL;                                          // Initialisation du pointeur de fin � NULL
    newListe->taille = 0;                                          // Initialisation de la taille de la liste � 0
    return newListe;                                               // Retour du pointeur vers la nouvelle liste
}

/* Facultatif : fonction pour cr�er un nouveau n�ud (ici Materiel) ind�pendant de la LDC, 
**              **efficace lors de l'insertion dans n'importe quelle position de la LDC.** */            
Materiel* creerMateriel(Materiel materiel) {
    Materiel* newMateriel = (Materiel*) malloc(sizeof(Materiel)); // Allocation de m�moire pour le nouveau mat�riel.
    if (newMateriel == NULL) {                                     // V�rification de l'�chec de l'allocation m�moire.
        printf("Erreur allocation memoire \n");
        exit(EXIT_FAILURE);                                        // Arr�t du programme en cas d'�chec d'allocation.
    }
    newMateriel->id = materiel.id;                                 // Copie de l'ID.
    strcpy(newMateriel->nom, materiel.nom);                        // Copie s�curis�e du nom.
    newMateriel->prix = materiel.prix;                             // Copie du prix.
    newMateriel->quantite = materiel.quantite;                     // Copie de la quantit�.
    newMateriel->reference = strdup(materiel.reference);           // Duplication de la cha�ne de r�f�rence.
    newMateriel->suivant = NULL;                                   // Initialisation du pointeur suivant � NULL.
    newMateriel->precedent = NULL;                                 // Initialisation du pointeur pr�c�dent � NULL.
    return newMateriel;                                            // Retourne le pointeur vers le nouveau mat�riel.
}

//2. inserer_debut(liste*, materiel) : ins�re un �l�ment au d�but de la liste.
void inserer_debut(Liste* liste, Materiel materiel) {
    Materiel* newMateriel = creerMateriel(materiel);   // Cr�e un nouveau n�ud bas� sur les donn�es fournies.
    if (liste->debut == NULL) {                        // V�rifie si la liste est vide.
        newMateriel->suivant = NULL;                   // Pas n�cessaire car elle est d�j� � NULL par creerMateriel.
        //newMateriel->precedent = NULL;               // Aussi pas n�cessaire car elle est d�j� � NULL par creerMateriel.
        liste->debut = newMateriel;                    // Met � jour le d�but de la liste.
        liste->fin = newMateriel;                      // Attention dans ce cas, newMateriel est � la fois le d�but et la fin de la liste car la liste �tait vide.
    } else {                                           // Si la liste contient d�j� des �l�ments.
        newMateriel->suivant = liste->debut;           // Le nouveau n�ud pointe vers l'ancien d�but.
        //newMateriel->precedent = NULL;                 // Pas n�cessaire car elle est d�j� � NULL par creerMateriel.
        liste->debut->precedent = newMateriel;         // L'ancien d�but pointe en arri�re vers le nouveau n�ud.
        liste->debut = newMateriel;                    // Met � jour le d�but de la liste avec le nouveau n�ud.
    }
    liste->taille++;                                   // Incr�mente la taille de la liste.
}


//3. inserer_fin(liste*, materiel) : ins�re un �l�ment � la fin de la liste.
void inserer_fin(Liste* liste, Materiel materiel) {
    Materiel* newMateriel = creerMateriel(materiel);  // Cr�e un nouveau n�ud bas� sur les donn�es fournies.
    if (liste->debut == NULL) {                       // V�rifie si la liste est vide.
        newMateriel->suivant = NULL;                  // D�j� � NULL par creerMateriel, assure que le nouveau n�ud est le dernier.
        newMateriel->precedent = NULL;                // Aussi pas n�cessaire car elle est d�j� � NULL par creerMateriel.
        liste->fin = newMateriel;                     // Met � jour la fin de la liste.
        liste->debut = newMateriel;                   // Dans ce cas, newMateriel est � la fois le d�but et la fin de la liste car la liste �tait vide.
    } else {
        newMateriel->suivant = NULL;                  // Assure que le nouveau n�ud est le dernier. Pas n�cessaire car elle est d�j� � NULL par creerMateriel.
        newMateriel->precedent = liste->fin;          // Connecte le nouveau n�ud � l'ancienne fin de la liste.
        liste->fin->suivant = newMateriel;            // L'ancienne fin de la liste pointe vers le nouveau n�ud.
        liste->fin = newMateriel;                     // Met � jour la fin de la liste avec le nouveau n�ud.
    }
    liste->taille++;                                  // Incr�mente la taille de la liste.
}


//4. supprimer_debut(liste*) : supprime le premier �l�ment de la liste.
void supprimer_debut(Liste* liste) {
    if (liste->debut == NULL) {                           // V�rifie si la liste est vide.
        printf("La liste est vide, rien � supprimer \n");
        return;
    }
    if (liste->debut->suivant == NULL) {                  // Cas o� la liste ne contient qu'un seul �l�ment.
        free(liste->debut->reference);                    // Lib�re la m�moire allou�e pour la r�f�rence.
        free(liste->debut);                               // Lib�re la m�moire allou�e pour l'�l�ment lui-m�me.
        liste->debut = NULL;                              // R�initialise le pointeur de d�but � NULL.
        liste->fin = NULL;                                // R�initialise �galement le pointeur de fin � NULL.
    } else {                                              // Cas o� la liste contient plusieurs �l�ments.
        Materiel* temp = liste->debut;                    // Stocke temporairement le premier �l�ment pour lib�ration.
        liste->debut = liste->debut->suivant;             // Avance le pointeur de d�but au deuxi�me �l�ment.
        liste->debut->precedent = NULL;                   // Supprime le lien pr�c�dent du nouveau premier �l�ment.
        free(temp->reference);                            // Lib�re la m�moire de la r�f�rence de l'ancien premier �l�ment.
        free(temp);                                       // Lib�re la m�moire de l'ancien premier �l�ment.
    }
    liste->taille--;                                      // D�cr�mente la taille de la liste.
}


//5. supprimer_fin(liste*) : supprime le dernier �l�ment de la liste.
void supprimer_fin(Liste* liste) {
    if (liste->debut == NULL) {                           // V�rifie si la liste est vide.
        printf("La liste est vide, aucun element a supprimer \n");
        return;
    }
    if (liste->debut->suivant == NULL) {                  // Cas o� la liste ne contient qu'un seul �l�ment.
        free(liste->fin->reference);                      // Lib�re la m�moire allou�e pour la r�f�rence de l'�l�ment.
        free(liste->fin);                                 // Lib�re la m�moire allou�e pour l'�l�ment lui-m�me.
        liste->fin = NULL;                                // R�initialise le pointeur de fin � NULL.
        liste->debut = NULL;                              // R�initialise �galement le pointeur de d�but � NULL, car la liste est maintenant vide.
    } else {                                              // Cas o� la liste contient plusieurs �l�ments.
        Materiel* temp = liste->fin;                      // Stocke temporairement le dernier �l�ment pour lib�ration.
        liste->fin = liste->fin->precedent;               // Recule le pointeur de fin � son �l�ment precedent.
        liste->fin->suivant = NULL;                       // Supprime le lien suivant du nouveau dernier �l�ment, isolant l'ancien dernier �l�ment.
        free(temp->reference);                            // Lib�re la m�moire de la r�f�rence de l'ancien dernier �l�ment.
        free(temp);                                       // Lib�re la m�moire de l'ancien dernier �l�ment.
    }
    liste->taille--;                                      // D�cr�mente la taille de la liste.
}

//6. afficher_liste(liste*) : affiche les �l�ments de la liste.
// Fonction pour afficher tous les �l�ments de la liste doublement cha�n�e.
void afficher_liste(Liste* liste) {
    if (liste->debut == NULL) {  // V�rifie si la liste est vide.
        printf("La liste est vide, aucun element a afficher \n");
        return;
    }
    Materiel* current = liste->debut; 
    while (current != NULL) {    
        printf("La LDC contient les informations suivantes : nom = %s, prix = %.2f, quantite = %d, reference = %s \n", current->nom, current->prix, current->quantite, current->reference);
        current = current->suivant;                         
    }
}

//7. ajouter_materiel(liste*) : ajoute un nouveau mat�riel � la liste.
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

//8. modifier_materiel(liste*, int) : modifie un mat�riel existant dans la liste.
void modifier_materiel(Liste* liste, int idModifier) {
    if (liste->debut == NULL) {                                            // V�rifie si la liste est vide
        printf("La liste est vide, aucun element a modifier \n");
        return;
    }
    Materiel* current = liste->debut;                                      
    while (current != NULL && current->id != idModifier) {                 // Cherche l'�l�ment avec l'ID sp�cifi�
        current = current->suivant;                                      
    }
    if (current != NULL) {                                                 // Si l'�l�ment est trouv� avant la fin de la liste: on sort de la boucle while avec :: current != NULL et current->id = idModifier
        printf("Veuillez saisir le nom du materiel a modifier \n");
        scanf("%49s", current->nom);                                       
        printf("Veuillez saisir le prix du materiel a modifier \n");
        scanf("%f", &current->prix);                                       
        printf("Veuillez saisir la quantite du materiel a modifier \n");
        scanf("%d", &current->quantite);                                   
        printf("Veuillez saisir la reference du materiel a modifier \n");
        scanf("%99s", current->reference);                                 
    }
    else {
        printf("La liste a ete totalement explore et l'ID passe en argument ne correspond a aucun materiel dans la liste.\n");
    }   
}


//9. supprimer_materiel(liste*, int) : supprime un mat�riel de la liste.
void supprimer_materiel(Liste* liste, int idSupprimer){
    if (liste->debut == NULL) {                                                  // V�rifie si la liste est vide
        printf("La liste est vide, aucun element a supprimer \n");
        return;
    }
    if (liste->debut->suivant == NULL && liste->debut->id == idSupprimer) {      // Cas sp�cial o� la liste n'a qu'un seul �l�ment
        supprimer_debut(liste);
        return;
    }
    Materiel *current = liste->debut;
    while (current->suivant != NULL && current->suivant->id != idSupprimer) {    // Cherche l'�l�ment pr�c�dant celui � supprimer
        current = current->suivant;
    }
    if (current->suivant != NULL) {                                              // Si l'�l�ment � supprimer est trouv� : on sort de la boucle while avec :: current->suivant != NULL et current->suivant->id = idSupprimer
        Materiel* aSupprimer = current->suivant;
        current->suivant = aSupprimer->suivant;                                  // Relie le pr�c�dent de l'�l�ment supprim� avec son suivant
        if (aSupprimer->suivant != NULL) {                                       // Si l'�l�ment � supprimer n'est pas le dernier
            aSupprimer->suivant->precedent = current;                            // Met � jour le lien pr�c�dent du suivant
        }
        else {                                                                   // Si l'�l�ment � supprimer est le dernier
            liste->fin = current;                                                // Met � jour le pointeur de fin de la liste
        }
        free(aSupprimer->reference);                                             // Lib�re la m�moire de la r�f�rence
        free(aSupprimer);                                                        // Lib�re la m�moire de l'�l�ment
        liste->taille--;                                                         // D�cr�mente la taille de la liste
    }
    else {                                                                       // Si l'�l�ment � supprimer n'est pas trouv�
        printf("La liste a ete totalement explore et l'ID passe en argument ne correspond a aucun materiel dans la liste.");
    }
}


//10. rechercher_materiel(liste*, int) : recherche un mat�riel dans la liste par son identifiant.
Materiel* rechercher_materiel(Liste* liste, int idRechercher) {
    if (liste->debut == NULL) {                                       // V�rifie si la liste est vide
        printf("La liste est vide.\n");
        return NULL;                                                   // Renvoie NULL car la liste est vide
    }

    Materiel* current = liste->debut;                                 
    while (current != NULL && current->id != idRechercher) {           // Parcourt la liste jusqu'� atteindre la fin (current = NULL) ou trouver l'ID (current->id = idRechercher)
        current = current->suivant;                                    
    }

    if (current != NULL) {                                             // Si l'�l�ment est trouv� : on sort de la boucle while avec :: current!= NULL et current->id = idRechercher
        printf("Materiel trouve !!!\n");
        return current;                                                // Renvoie un pointeur vers l'�l�ment trouv�
    } else {
        printf("La liste a ete totalement exploree et l'ID passe en argument ne correspond a aucun materiel dans la liste.\n");
        return NULL;                                                   // Attention ici : Renvoie NULL car l'ID n'est pas trouv�
    }
}


// 11. trier_par_nom(liste*) : trie la liste par nom de mat�riel croissant.

void permuterValeur(Materiel *mat1, Materiel *mat2) {
    // �change temporaire des valeurs simples (id , prix et quantite)
    int idTemp = mat1->id;
    mat1->id = mat2->id;
    mat2->id = idTemp;

    float prixTemp = mat1->prix;
    mat1->prix = mat2->prix;
    mat2->prix = prixTemp;

    int quantiteTemp = mat1->quantite;
    mat1->quantite = mat2->quantite;
    mat2->quantite = quantiteTemp;

    // �change des cha�nes statiques pour 'nom'
    char nomTemp[50];
    strcpy(nomTemp, mat1->nom);
    strcpy(mat1->nom, mat2->nom);
    strcpy(mat2->nom, nomTemp);

    // �change des pointeurs pour 'reference'. Pas besoin d'allouer ou lib�rer de la m�moire,
    // seulement �changer les pointeurs.
    char *refTemp = mat1->reference;
    mat1->reference = mat2->reference;
    mat2->reference = refTemp;
}


//11.2 Le tri � bulle:
void Tri_Bulles(Liste* liste)
{
    Materiel *tmp;                                                          // Pointeur temporaire pour parcourir la liste
    Materiel *cmp;                                                         // Pointeur pour comparer les �l�ments
    for (tmp = liste->debut; tmp->suivant != NULL; tmp = tmp->suivant)     // Parcourt la liste � partir du d�but jusqu'� l'avant-dernier �l�ment (tmp->suivant != NULL)
    {
        for (cmp = tmp; cmp != NULL; cmp = cmp->suivant)                   // Parcourt la liste � partir de l'�l�ment actuel (tmp) jusqu'� la fin
        {
            if (strcmp(tmp->nom, cmp->nom) > 0)                            // Compare les noms de mat�riel des �l�ments actuels tmp et cmp
                permuterValeur(tmp, cmp);                                 // Permute les valeurs des �l�ments si n�cessaire
        }
    }
    
    afficher_liste(liste);                                                // Affiche la liste tri�e apr�s le tri � bulles
}



//12. sauvegarder_liste(liste*, char*) : sauvegarde la liste dans un fichier.
void sauvegarder_liste(Liste *liste, char *filename) {
    FILE *file = fopen(filename, "w");                               // Ouvre le fichier en mode �criture.
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier pour �crire.\n");
        return;
    }

    Materiel *current = liste->debut;
    while (current != NULL) {
        fprintf(file, "%d,%s,%f,%s,%d \n", current->id, current->nom, current->prix, current->reference, current->quantite);
        current = current->suivant;
    }

    fclose(file);                                                   // Ferme le fichier apr�s l'�criture.
}


// Necessaire pour impl�menter la fonction de la question suivante : charger_liste(liste*, char*)
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
    // R�initialise les pointeurs de d�but et de fin ainsi que la taille de la liste (c'est le point de difference entre liberer_liste et vider_liste, � cette �tape liberer_liste lib�re la Liste entiere free(liste) )
    liste->debut = NULL;
    liste->fin = NULL;
    liste->taille = 0;
}


//13. charger_liste(liste*, char*) : charge la liste depuis un fichier.
// La fonction charger_liste est con�ue pour lire les informations sur des objets de type Materiel
// depuis un fichier texte et les ins�rer dans une liste cha�n�e. Cela permet de reconstruire 
// une liste cha�n�e � partir de donn�es existants dans un fichier
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
        Materiel* materiel = (Materiel*) malloc(sizeof(Materiel));                   // Cr�e un nouveau Materiel dynamiquement pour chaque entr�e lue
        materiel->id = id;
        strcpy(materiel->nom, nom);
        materiel->prix = prix;
        materiel->quantite = quantite;
        materiel->reference = strdup(reference); 
        materiel->suivant = NULL;
        materiel->precedent = NULL;

        inserer_debut(liste, *materiel);                                              // Ins�re le nouveau Materiel au d�but de la liste
    }
    fclose(file); 
}


//**Obligatoire*** : fonction pour liberer la m�moire allou�e par la LDC (pareille pour LSC)
void liberer_liste(Liste* liste) {
    Materiel* current = liste->debut;
    while (current != NULL) {
        Materiel* aSupprimer = current;
        current = current->suivant;
        free(aSupprimer->reference);                        // Attention lib�rer la m�moire allou�e pour la r�f�rence !!!!       
        free(aSupprimer);                                  // Lib�rer la m�moire allou�e pour le mat�riel lui-m�me
    }
    free(liste);                                          // Attention, ici lib�rez la Liste entiere puisqu'elle est allou�e dynamiquement.
}



int main() {
    Liste* liste = initialiserLDC(); 

    // �tape 2: Ajout de mat�riels.
    Materiel m1 = {1, "Clavier", 25.99, 10, strdup("REF001"),NULL,NULL};
    Materiel m2 = {2, "Souris", 15.75, 20, strdup("REF002"),NULL,NULL};
    Materiel m3 = {3, "Ecran", 199.99, 5, strdup("REF003"),NULL,NULL};
   

    inserer_debut(liste, m1);
    inserer_debut(liste, m2);
    inserer_fin(liste, m3); 


    printf("Liste apres ajout:\n");
    afficher_liste(liste);
    
    // Sauvegarde de la liste dans un fichier.
    sauvegarder_liste(liste, "liste_materiel.txt");
    printf("Liste sauvegard�e.\n");

    // Cr�ation d'une nouvelle liste pour charger les donn�es.
    Liste* listeChargee = initialiserLDC();
    charger_liste(listeChargee, "liste_materiel.txt");
    printf("Liste chargee du fichier.\n");

    // Affichage de la liste charg�e.
    afficher_liste(listeChargee);
  
    printf("\n Modification du materiel ID 2: \n");
    modifier_materiel(liste, 2); 


    printf("\nListe apres modification:\n");
    afficher_liste(liste);


    printf("\nRecherche du materiel ID 3:\n");
    Materiel* trouve = rechercher_materiel(liste, 3);
    

    printf("\nSuppression du materiel ID 1:\n");
    supprimer_materiel(liste, 1);


    printf("\nListe apr�s suppression:\n");
    afficher_liste(liste);


    printf("\nTri de la liste par nom:\n");
    Tri_Bulles(liste); 
    

    liberer_liste(liste);
    return 0;
}






