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
Liste* initialiserLDC() {                                          // Allouer de la mémoire à une nouvelle liste doublement chaînée (LDC)
    Liste* newListe = (Liste*) malloc(sizeof(Liste));              // Allocation mémoire pour la nouvelle liste
    if (newListe == NULL) {                                        // Vérification de l'échec de l'allocation mémoire
        printf("Erreur allocation memoire");
        exit(EXIT_FAILURE);                                        // Arrêt du programme en cas d'échec d'allocation
    }
    newListe->debut = NULL;                                        // Initialisation du pointeur de début à NULL
    newListe->fin = NULL;                                          // Initialisation du pointeur de fin à NULL
    newListe->taille = 0;                                          // Initialisation de la taille de la liste à 0
    return newListe;                                               // Retour du pointeur vers la nouvelle liste
}

/* Facultatif : fonction pour créer un nouveau nœud (ici Materiel) indépendant de la LDC, 
**              **efficace lors de l'insertion dans n'importe quelle position de la LDC.** */            
Materiel* creerMateriel(Materiel materiel) {
    Materiel* newMateriel = (Materiel*) malloc(sizeof(Materiel)); // Allocation de mémoire pour le nouveau matériel.
    if (newMateriel == NULL) {                                     // Vérification de l'échec de l'allocation mémoire.
        printf("Erreur allocation memoire \n");
        exit(EXIT_FAILURE);                                        // Arrêt du programme en cas d'échec d'allocation.
    }
    newMateriel->id = materiel.id;                                 // Copie de l'ID.
    strcpy(newMateriel->nom, materiel.nom);                        // Copie sécurisée du nom.
    newMateriel->prix = materiel.prix;                             // Copie du prix.
    newMateriel->quantite = materiel.quantite;                     // Copie de la quantité.
    newMateriel->reference = strdup(materiel.reference);           // Duplication de la chaîne de référence.
    newMateriel->suivant = NULL;                                   // Initialisation du pointeur suivant à NULL.
    newMateriel->precedent = NULL;                                 // Initialisation du pointeur précédent à NULL.
    return newMateriel;                                            // Retourne le pointeur vers le nouveau matériel.
}

//2. inserer_debut(liste*, materiel) : insère un élément au début de la liste.
void inserer_debut(Liste* liste, Materiel materiel) {
    Materiel* newMateriel = creerMateriel(materiel);   // Crée un nouveau nœud basé sur les données fournies.
    if (liste->debut == NULL) {                        // Vérifie si la liste est vide.
        newMateriel->suivant = NULL;                   // Pas nécessaire car elle est déjà à NULL par creerMateriel.
        //newMateriel->precedent = NULL;               // Aussi pas nécessaire car elle est déjà à NULL par creerMateriel.
        liste->debut = newMateriel;                    // Met à jour le début de la liste.
        liste->fin = newMateriel;                      // Attention dans ce cas, newMateriel est à la fois le début et la fin de la liste car la liste était vide.
    } else {                                           // Si la liste contient déjà des éléments.
        newMateriel->suivant = liste->debut;           // Le nouveau nœud pointe vers l'ancien début.
        //newMateriel->precedent = NULL;                 // Pas nécessaire car elle est déjà à NULL par creerMateriel.
        liste->debut->precedent = newMateriel;         // L'ancien début pointe en arrière vers le nouveau nœud.
        liste->debut = newMateriel;                    // Met à jour le début de la liste avec le nouveau nœud.
    }
    liste->taille++;                                   // Incrémente la taille de la liste.
}


//3. inserer_fin(liste*, materiel) : insère un élément à la fin de la liste.
void inserer_fin(Liste* liste, Materiel materiel) {
    Materiel* newMateriel = creerMateriel(materiel);  // Crée un nouveau nœud basé sur les données fournies.
    if (liste->debut == NULL) {                       // Vérifie si la liste est vide.
        newMateriel->suivant = NULL;                  // Déjà à NULL par creerMateriel, assure que le nouveau nœud est le dernier.
        newMateriel->precedent = NULL;                // Aussi pas nécessaire car elle est déjà à NULL par creerMateriel.
        liste->fin = newMateriel;                     // Met à jour la fin de la liste.
        liste->debut = newMateriel;                   // Dans ce cas, newMateriel est à la fois le début et la fin de la liste car la liste était vide.
    } else {
        newMateriel->suivant = NULL;                  // Assure que le nouveau nœud est le dernier. Pas nécessaire car elle est déjà à NULL par creerMateriel.
        newMateriel->precedent = liste->fin;          // Connecte le nouveau nœud à l'ancienne fin de la liste.
        liste->fin->suivant = newMateriel;            // L'ancienne fin de la liste pointe vers le nouveau nœud.
        liste->fin = newMateriel;                     // Met à jour la fin de la liste avec le nouveau nœud.
    }
    liste->taille++;                                  // Incrémente la taille de la liste.
}


//4. supprimer_debut(liste*) : supprime le premier élément de la liste.
void supprimer_debut(Liste* liste) {
    if (liste->debut == NULL) {                           // Vérifie si la liste est vide.
        printf("La liste est vide, rien à supprimer \n");
        return;
    }
    if (liste->debut->suivant == NULL) {                  // Cas où la liste ne contient qu'un seul élément.
        free(liste->debut->reference);                    // Libère la mémoire allouée pour la référence.
        free(liste->debut);                               // Libère la mémoire allouée pour l'élément lui-même.
        liste->debut = NULL;                              // Réinitialise le pointeur de début à NULL.
        liste->fin = NULL;                                // Réinitialise également le pointeur de fin à NULL.
    } else {                                              // Cas où la liste contient plusieurs éléments.
        Materiel* temp = liste->debut;                    // Stocke temporairement le premier élément pour libération.
        liste->debut = liste->debut->suivant;             // Avance le pointeur de début au deuxième élément.
        liste->debut->precedent = NULL;                   // Supprime le lien précédent du nouveau premier élément.
        free(temp->reference);                            // Libère la mémoire de la référence de l'ancien premier élément.
        free(temp);                                       // Libère la mémoire de l'ancien premier élément.
    }
    liste->taille--;                                      // Décrémente la taille de la liste.
}


//5. supprimer_fin(liste*) : supprime le dernier élément de la liste.
void supprimer_fin(Liste* liste) {
    if (liste->debut == NULL) {                           // Vérifie si la liste est vide.
        printf("La liste est vide, aucun element a supprimer \n");
        return;
    }
    if (liste->debut->suivant == NULL) {                  // Cas où la liste ne contient qu'un seul élément.
        free(liste->fin->reference);                      // Libère la mémoire allouée pour la référence de l'élément.
        free(liste->fin);                                 // Libère la mémoire allouée pour l'élément lui-même.
        liste->fin = NULL;                                // Réinitialise le pointeur de fin à NULL.
        liste->debut = NULL;                              // Réinitialise également le pointeur de début à NULL, car la liste est maintenant vide.
    } else {                                              // Cas où la liste contient plusieurs éléments.
        Materiel* temp = liste->fin;                      // Stocke temporairement le dernier élément pour libération.
        liste->fin = liste->fin->precedent;               // Recule le pointeur de fin à son élément precedent.
        liste->fin->suivant = NULL;                       // Supprime le lien suivant du nouveau dernier élément, isolant l'ancien dernier élément.
        free(temp->reference);                            // Libère la mémoire de la référence de l'ancien dernier élément.
        free(temp);                                       // Libère la mémoire de l'ancien dernier élément.
    }
    liste->taille--;                                      // Décrémente la taille de la liste.
}

//6. afficher_liste(liste*) : affiche les éléments de la liste.
// Fonction pour afficher tous les éléments de la liste doublement chaînée.
void afficher_liste(Liste* liste) {
    if (liste->debut == NULL) {  // Vérifie si la liste est vide.
        printf("La liste est vide, aucun element a afficher \n");
        return;
    }
    Materiel* current = liste->debut; 
    while (current != NULL) {    
        printf("La LDC contient les informations suivantes : nom = %s, prix = %.2f, quantite = %d, reference = %s \n", current->nom, current->prix, current->quantite, current->reference);
        current = current->suivant;                         
    }
}

//7. ajouter_materiel(liste*) : ajoute un nouveau matériel à la liste.
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

//8. modifier_materiel(liste*, int) : modifie un matériel existant dans la liste.
void modifier_materiel(Liste* liste, int idModifier) {
    if (liste->debut == NULL) {                                            // Vérifie si la liste est vide
        printf("La liste est vide, aucun element a modifier \n");
        return;
    }
    Materiel* current = liste->debut;                                      
    while (current != NULL && current->id != idModifier) {                 // Cherche l'élément avec l'ID spécifié
        current = current->suivant;                                      
    }
    if (current != NULL) {                                                 // Si l'élément est trouvé avant la fin de la liste: on sort de la boucle while avec :: current != NULL et current->id = idModifier
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


//9. supprimer_materiel(liste*, int) : supprime un matériel de la liste.
void supprimer_materiel(Liste* liste, int idSupprimer){
    if (liste->debut == NULL) {                                                  // Vérifie si la liste est vide
        printf("La liste est vide, aucun element a supprimer \n");
        return;
    }
    if (liste->debut->suivant == NULL && liste->debut->id == idSupprimer) {      // Cas spécial où la liste n'a qu'un seul élément
        supprimer_debut(liste);
        return;
    }
    Materiel *current = liste->debut;
    while (current->suivant != NULL && current->suivant->id != idSupprimer) {    // Cherche l'élément précédant celui à supprimer
        current = current->suivant;
    }
    if (current->suivant != NULL) {                                              // Si l'élément à supprimer est trouvé : on sort de la boucle while avec :: current->suivant != NULL et current->suivant->id = idSupprimer
        Materiel* aSupprimer = current->suivant;
        current->suivant = aSupprimer->suivant;                                  // Relie le précédent de l'élément supprimé avec son suivant
        if (aSupprimer->suivant != NULL) {                                       // Si l'élément à supprimer n'est pas le dernier
            aSupprimer->suivant->precedent = current;                            // Met à jour le lien précédent du suivant
        }
        else {                                                                   // Si l'élément à supprimer est le dernier
            liste->fin = current;                                                // Met à jour le pointeur de fin de la liste
        }
        free(aSupprimer->reference);                                             // Libère la mémoire de la référence
        free(aSupprimer);                                                        // Libère la mémoire de l'élément
        liste->taille--;                                                         // Décrémente la taille de la liste
    }
    else {                                                                       // Si l'élément à supprimer n'est pas trouvé
        printf("La liste a ete totalement explore et l'ID passe en argument ne correspond a aucun materiel dans la liste.");
    }
}


//10. rechercher_materiel(liste*, int) : recherche un matériel dans la liste par son identifiant.
Materiel* rechercher_materiel(Liste* liste, int idRechercher) {
    if (liste->debut == NULL) {                                       // Vérifie si la liste est vide
        printf("La liste est vide.\n");
        return NULL;                                                   // Renvoie NULL car la liste est vide
    }

    Materiel* current = liste->debut;                                 
    while (current != NULL && current->id != idRechercher) {           // Parcourt la liste jusqu'à atteindre la fin (current = NULL) ou trouver l'ID (current->id = idRechercher)
        current = current->suivant;                                    
    }

    if (current != NULL) {                                             // Si l'élément est trouvé : on sort de la boucle while avec :: current!= NULL et current->id = idRechercher
        printf("Materiel trouve !!!\n");
        return current;                                                // Renvoie un pointeur vers l'élément trouvé
    } else {
        printf("La liste a ete totalement exploree et l'ID passe en argument ne correspond a aucun materiel dans la liste.\n");
        return NULL;                                                   // Attention ici : Renvoie NULL car l'ID n'est pas trouvé
    }
}


// 11. trier_par_nom(liste*) : trie la liste par nom de matériel croissant.

void permuterValeur(Materiel *mat1, Materiel *mat2) {
    // Échange temporaire des valeurs simples (id , prix et quantite)
    int idTemp = mat1->id;
    mat1->id = mat2->id;
    mat2->id = idTemp;

    float prixTemp = mat1->prix;
    mat1->prix = mat2->prix;
    mat2->prix = prixTemp;

    int quantiteTemp = mat1->quantite;
    mat1->quantite = mat2->quantite;
    mat2->quantite = quantiteTemp;

    // Échange des chaînes statiques pour 'nom'
    char nomTemp[50];
    strcpy(nomTemp, mat1->nom);
    strcpy(mat1->nom, mat2->nom);
    strcpy(mat2->nom, nomTemp);

    // Échange des pointeurs pour 'reference'. Pas besoin d'allouer ou libérer de la mémoire,
    // seulement échanger les pointeurs.
    char *refTemp = mat1->reference;
    mat1->reference = mat2->reference;
    mat2->reference = refTemp;
}


//11.2 Le tri à bulle:
void Tri_Bulles(Liste* liste)
{
    Materiel *tmp;                                                          // Pointeur temporaire pour parcourir la liste
    Materiel *cmp;                                                         // Pointeur pour comparer les éléments
    for (tmp = liste->debut; tmp->suivant != NULL; tmp = tmp->suivant)     // Parcourt la liste à partir du début jusqu'à l'avant-dernier élément (tmp->suivant != NULL)
    {
        for (cmp = tmp; cmp != NULL; cmp = cmp->suivant)                   // Parcourt la liste à partir de l'élément actuel (tmp) jusqu'à la fin
        {
            if (strcmp(tmp->nom, cmp->nom) > 0)                            // Compare les noms de matériel des éléments actuels tmp et cmp
                permuterValeur(tmp, cmp);                                 // Permute les valeurs des éléments si nécessaire
        }
    }
    
    afficher_liste(liste);                                                // Affiche la liste triée après le tri à bulles
}



//12. sauvegarder_liste(liste*, char*) : sauvegarde la liste dans un fichier.
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


//**Obligatoire*** : fonction pour liberer la mémoire allouée par la LDC (pareille pour LSC)
void liberer_liste(Liste* liste) {
    Materiel* current = liste->debut;
    while (current != NULL) {
        Materiel* aSupprimer = current;
        current = current->suivant;
        free(aSupprimer->reference);                        // Attention libérer la mémoire allouée pour la référence !!!!       
        free(aSupprimer);                                  // Libérer la mémoire allouée pour le matériel lui-même
    }
    free(liste);                                          // Attention, ici libérez la Liste entiere puisqu'elle est allouée dynamiquement.
}



int main() {
    Liste* liste = initialiserLDC(); 

    // Étape 2: Ajout de matériels.
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
    printf("Liste sauvegardée.\n");

    // Création d'une nouvelle liste pour charger les données.
    Liste* listeChargee = initialiserLDC();
    charger_liste(listeChargee, "liste_materiel.txt");
    printf("Liste chargee du fichier.\n");

    // Affichage de la liste chargée.
    afficher_liste(listeChargee);
  
    printf("\n Modification du materiel ID 2: \n");
    modifier_materiel(liste, 2); 


    printf("\nListe apres modification:\n");
    afficher_liste(liste);


    printf("\nRecherche du materiel ID 3:\n");
    Materiel* trouve = rechercher_materiel(liste, 3);
    

    printf("\nSuppression du materiel ID 1:\n");
    supprimer_materiel(liste, 1);


    printf("\nListe après suppression:\n");
    afficher_liste(liste);


    printf("\nTri de la liste par nom:\n");
    Tri_Bulles(liste); 
    

    liberer_liste(liste);
    return 0;
}






