#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure de données pour représenter une transaction bancaire
typedef struct Transaction {
    int type;          // 1: dépôt, 2: retrait, 3: transfert
    int montant;       // Montant de la transaction
    int compteSource;  // Numéro de compte source (pour les retraits et les transferts)
    int compteDestination; // Numéro de compte destination (pour les dépôts et les transferts)
    struct Transaction* suivant; // Pointeur vers la prochaine transaction dans la liste chaînée
} Transaction;

// Structure de données pour représenter une liste chaînée de transactions
typedef struct ListeTransactions {
    Transaction* debut; // Pointeur vers la première transaction dans la liste
    Transaction* fin;   // Pointeur vers la dernière transaction dans la liste
} ListeTransactions;

// Fonction pour créer une nouvelle transaction
Transaction* creerTransaction(int type, int montant, int compteSource, int compteDestination) {
    // Allocation de mémoire pour la nouvelle transaction
    Transaction* nouvelleTransaction = (Transaction*)malloc(sizeof(Transaction));
    // Vérification si l'allocation de mémoire a réussi
    if (nouvelleTransaction != NULL) {
        // Initialisation des données de la transaction
        nouvelleTransaction->type = type;
        nouvelleTransaction->montant = montant;
        nouvelleTransaction->compteSource = compteSource;
        nouvelleTransaction->compteDestination = compteDestination;
        nouvelleTransaction->suivant = NULL; // Initialisation du pointeur suivant à NULL
    }
    return nouvelleTransaction; // Retourne la nouvelle transaction
}

// Fonction pour ajouter une transaction à la liste chaînée
void ajouterTransaction(ListeTransactions* liste, Transaction* nouvelleTransaction) {
    // Vérification si la liste est vide
    if (liste->debut == NULL) {
        // Si la liste est vide, la transaction devient la première et la dernière transaction de la liste
        liste->debut = nouvelleTransaction;
        liste->fin = nouvelleTransaction;
    } else {
        // Sinon, la nouvelle transaction est ajoutée à la fin de la liste
        liste->fin->suivant = nouvelleTransaction;
        liste->fin = nouvelleTransaction;
    }
}

// Fonction pour afficher l'historique des transactions
void afficherTransactions(ListeTransactions* liste) {
    // Affichage de l'en-tête de l'historique des transactions
    printf("Historique des transactions :\n");
    // Initialisation d'un pointeur vers la première transaction dans la liste
    Transaction* current = liste->debut;
    // Parcours de la liste de transactions
    while (current != NULL) {
        // Affichage des détails de chaque transaction
        printf("Type: %d, Montant: %d, Compte Source: %d, Compte Destination: %d\n",
               current->type, current->montant, current->compteSource, current->compteDestination);
        // Déplacement vers la prochaine transaction dans la liste
        current = current->suivant;
    }
}

// Fonction principale pour le traitement des transactions
void traiterTransactions(ListeTransactions* listeDepots, ListeTransactions* listeRetraits, ListeTransactions* listeTransferts) {
    // Traiter les dépôts en attente
    while (listeDepots->debut != NULL) {
        // Récupération de la première transaction de la liste des dépôts
        Transaction* transactionDepot = listeDepots->debut;
        // Affichage du traitement de la transaction de dépôt
        printf("Traitement d'un dépôt de %d sur le compte %d.\n", transactionDepot->montant, transactionDepot->compteDestination);
        // Libération de la mémoire allouée pour la transaction de dépôt
        free(transactionDepot);
        // Déplacement vers la prochaine transaction dans la liste des dépôts
        listeDepots->debut = listeDepots->debut->suivant;
    }

    // Traiter les retraits en attente
    while (listeRetraits->debut != NULL) {
        // Récupération de la première transaction de la liste des retraits
        Transaction* transactionRetrait = listeRetraits->debut;
        // Affichage du traitement de la transaction de retrait
        printf("Traitement d'un retrait de %d sur le compte %d.\n", transactionRetrait->montant, transactionRetrait->compteSource);
        // Libération de la mémoire allouée pour la transaction de retrait
        free(transactionRetrait);
        // Déplacement vers la prochaine transaction dans la liste des retraits
        listeRetraits->debut = listeRetraits->debut->suivant;
    }

    // Traiter les transferts en attente
    while (listeTransferts->debut != NULL) {
        // Récupération de la première transaction de la liste des transferts
        Transaction* transactionTransfert = listeTransferts->debut;
        // Affichage du traitement de la transaction de transfert
        printf("Traitement d'un transfert de %d du compte %d vers le compte %d.\n", 
               transactionTransfert->montant, transactionTransfert->compteSource, transactionTransfert->compteDestination);
        // Libération de la mémoire allouée pour la transaction de transfert
        free(transactionTransfert);
        // Déplacement vers la prochaine transaction dans la liste des transferts
        listeTransferts->debut = listeTransferts->debut->suivant;
    }
}

// Fonction principale pour le menu interactif
int main() {
    // Initialisation des listes de transactions pour les dépôts, les retraits et les transferts
    ListeTransactions listeDepots = { .debut = NULL, .fin = NULL };
    ListeTransactions listeRetraits = { .debut = NULL, .fin = NULL };
    ListeTransactions listeTransferts = { .debut = NULL, .fin = NULL };

    // Déclaration des variables pour le menu
    int choix, montant, compteSource, compteDestination;

    do {
        // Affichage du menu
        printf("\nMenu :\n");
        printf("1. Effectuer un dépôt\n");
        printf("2. Effectuer un retrait\n");
        printf("3. Effectuer un transfert\n");
        printf("4. Afficher l'historique des transactions\n");
        printf("5. Traiter les transactions en attente\n");
        printf("6. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Saisie des informations pour le dépôt
                printf("Montant du dépôt : ");
                scanf("%d", &montant);
                printf("Com

