#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure de donn�es pour repr�senter une transaction bancaire
typedef struct Transaction {
    int type;          // 1: d�p�t, 2: retrait, 3: transfert
    int montant;       // Montant de la transaction
    int compteSource;  // Num�ro de compte source (pour les retraits et les transferts)
    int compteDestination; // Num�ro de compte destination (pour les d�p�ts et les transferts)
    struct Transaction* suivant; // Pointeur vers la prochaine transaction dans la liste cha�n�e
} Transaction;

// Structure de donn�es pour repr�senter une liste cha�n�e de transactions
typedef struct ListeTransactions {
    Transaction* debut; // Pointeur vers la premi�re transaction dans la liste
    Transaction* fin;   // Pointeur vers la derni�re transaction dans la liste
} ListeTransactions;

// Fonction pour cr�er une nouvelle transaction
Transaction* creerTransaction(int type, int montant, int compteSource, int compteDestination) {
    // Allocation de m�moire pour la nouvelle transaction
    Transaction* nouvelleTransaction = (Transaction*)malloc(sizeof(Transaction));
    // V�rification si l'allocation de m�moire a r�ussi
    if (nouvelleTransaction != NULL) {
        // Initialisation des donn�es de la transaction
        nouvelleTransaction->type = type;
        nouvelleTransaction->montant = montant;
        nouvelleTransaction->compteSource = compteSource;
        nouvelleTransaction->compteDestination = compteDestination;
        nouvelleTransaction->suivant = NULL; // Initialisation du pointeur suivant � NULL
    }
    return nouvelleTransaction; // Retourne la nouvelle transaction
}

// Fonction pour ajouter une transaction � la liste cha�n�e
void ajouterTransaction(ListeTransactions* liste, Transaction* nouvelleTransaction) {
    // V�rification si la liste est vide
    if (liste->debut == NULL) {
        // Si la liste est vide, la transaction devient la premi�re et la derni�re transaction de la liste
        liste->debut = nouvelleTransaction;
        liste->fin = nouvelleTransaction;
    } else {
        // Sinon, la nouvelle transaction est ajout�e � la fin de la liste
        liste->fin->suivant = nouvelleTransaction;
        liste->fin = nouvelleTransaction;
    }
}

// Fonction pour afficher l'historique des transactions
void afficherTransactions(ListeTransactions* liste) {
    // Affichage de l'en-t�te de l'historique des transactions
    printf("Historique des transactions :\n");
    // Initialisation d'un pointeur vers la premi�re transaction dans la liste
    Transaction* current = liste->debut;
    // Parcours de la liste de transactions
    while (current != NULL) {
        // Affichage des d�tails de chaque transaction
        printf("Type: %d, Montant: %d, Compte Source: %d, Compte Destination: %d\n",
               current->type, current->montant, current->compteSource, current->compteDestination);
        // D�placement vers la prochaine transaction dans la liste
        current = current->suivant;
    }
}

// Fonction principale pour le traitement des transactions
void traiterTransactions(ListeTransactions* listeDepots, ListeTransactions* listeRetraits, ListeTransactions* listeTransferts) {
    // Traiter les d�p�ts en attente
    while (listeDepots->debut != NULL) {
        // R�cup�ration de la premi�re transaction de la liste des d�p�ts
        Transaction* transactionDepot = listeDepots->debut;
        // Affichage du traitement de la transaction de d�p�t
        printf("Traitement d'un d�p�t de %d sur le compte %d.\n", transactionDepot->montant, transactionDepot->compteDestination);
        // Lib�ration de la m�moire allou�e pour la transaction de d�p�t
        free(transactionDepot);
        // D�placement vers la prochaine transaction dans la liste des d�p�ts
        listeDepots->debut = listeDepots->debut->suivant;
    }

    // Traiter les retraits en attente
    while (listeRetraits->debut != NULL) {
        // R�cup�ration de la premi�re transaction de la liste des retraits
        Transaction* transactionRetrait = listeRetraits->debut;
        // Affichage du traitement de la transaction de retrait
        printf("Traitement d'un retrait de %d sur le compte %d.\n", transactionRetrait->montant, transactionRetrait->compteSource);
        // Lib�ration de la m�moire allou�e pour la transaction de retrait
        free(transactionRetrait);
        // D�placement vers la prochaine transaction dans la liste des retraits
        listeRetraits->debut = listeRetraits->debut->suivant;
    }

    // Traiter les transferts en attente
    while (listeTransferts->debut != NULL) {
        // R�cup�ration de la premi�re transaction de la liste des transferts
        Transaction* transactionTransfert = listeTransferts->debut;
        // Affichage du traitement de la transaction de transfert
        printf("Traitement d'un transfert de %d du compte %d vers le compte %d.\n", 
               transactionTransfert->montant, transactionTransfert->compteSource, transactionTransfert->compteDestination);
        // Lib�ration de la m�moire allou�e pour la transaction de transfert
        free(transactionTransfert);
        // D�placement vers la prochaine transaction dans la liste des transferts
        listeTransferts->debut = listeTransferts->debut->suivant;
    }
}

// Fonction principale pour le menu interactif
int main() {
    // Initialisation des listes de transactions pour les d�p�ts, les retraits et les transferts
    ListeTransactions listeDepots = { .debut = NULL, .fin = NULL };
    ListeTransactions listeRetraits = { .debut = NULL, .fin = NULL };
    ListeTransactions listeTransferts = { .debut = NULL, .fin = NULL };

    // D�claration des variables pour le menu
    int choix, montant, compteSource, compteDestination;

    do {
        // Affichage du menu
        printf("\nMenu :\n");
        printf("1. Effectuer un d�p�t\n");
        printf("2. Effectuer un retrait\n");
        printf("3. Effectuer un transfert\n");
        printf("4. Afficher l'historique des transactions\n");
        printf("5. Traiter les transactions en attente\n");
        printf("6. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Saisie des informations pour le d�p�t
                printf("Montant du d�p�t : ");
                scanf("%d", &montant);
                printf("Com

