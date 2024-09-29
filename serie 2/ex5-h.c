#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>



// Structure de données pour représenter une transaction bancaire

typedef struct Transaction {

    int type;          // 1: dépôt, 2: retrait, 3: transfert

    int montant;

    int compteSource;

    int compteDestination;

    struct Transaction* suivant;

} Transaction;



// Structure de données pour représenter une liste chaînée de transactions

typedef struct ListeTransactions {

    Transaction* debut;

    Transaction* fin;

} ListeTransactions;



// Fonction pour créer une nouvelle transaction

Transaction* creerTransaction(int type, int montant, int compteSource, int compteDestination) {

    Transaction* nouvelleTransaction = (Transaction*)malloc(sizeof(Transaction));

    if (nouvelleTransaction != NULL) {

        nouvelleTransaction->type = type;

        nouvelleTransaction->montant = montant;

        nouvelleTransaction->compteSource = compteSource;

        nouvelleTransaction->compteDestination = compteDestination;

        nouvelleTransaction->suivant = NULL;

    }

    return nouvelleTransaction;

}



// Fonction pour ajouter une transaction à la liste chaînée

void ajouterTransaction(ListeTransactions* liste, Transaction* nouvelleTransaction) {

    if (liste->debut == NULL) {

        liste->debut = nouvelleTransaction;

        liste->fin = nouvelleTransaction;

    } else {

        liste->fin->suivant = nouvelleTransaction;

        liste->fin = nouvelleTransaction;

    }

}



// Fonction pour afficher l'historique des transactions

void afficherTransactions(ListeTransactions* liste) {

    printf("Historique des transactions :\n");

    Transaction* current = liste->debut;

    while (current != NULL) {

        printf("Type: %d, Montant: %d, Compte Source: %d, Compte Destination: %d\n",

               current->type, current->montant, current->compteSource, current->compteDestination);

        current = current->suivant;

    }

}



// Fonction principale pour le traitement des transactions

void traiterTransactions(ListeTransactions* listeDepots, ListeTransactions* listeRetraits, ListeTransactions* listeTransferts) {

    // Traiter les dépôts en attente

    while (listeDepots->debut != NULL) {

        Transaction* transactionDepot = listeDepots->debut;

        printf("Traitement d'un dépôt de %d sur le compte %d.\n", transactionDepot->montant, transactionDepot->compteDestination);

        free(transactionDepot);

        listeDepots->debut = listeDepots->debut->suivant;

    }



    // Traiter les retraits en attente

    while (listeRetraits->debut != NULL) {

        Transaction* transactionRetrait = listeRetraits->debut;

        printf("Traitement d'un retrait de %d sur le compte %d.\n", transactionRetrait->montant, transactionRetrait->compteSource);

        free(transactionRetrait);

        listeRetraits->debut = listeRetraits->debut->suivant;

    }



    // Traiter les transferts en attente

    while (listeTransferts->debut != NULL) {

        Transaction* transactionTransfert = listeTransferts->debut;

        printf("Traitement d'un transfert de %d du compte %d vers le compte %d.\n",

               transactionTransfert->montant, transactionTransfert->compteSource, transactionTransfert->compteDestination);

        free(transactionTransfert);

        listeTransferts->debut = listeTransferts->debut->suivant;

    }

}



// Fonction principale pour le menu interactif

int main() {

    ListeTransactions listeDepots = { .debut = NULL, .fin = NULL };

    ListeTransactions listeRetraits = { .debut = NULL, .fin = NULL };

    ListeTransactions listeTransferts = { .debut = NULL, .fin = NULL };



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

                printf("Montant du dépôt : ");

                scanf("%d", &montant);

                printf("Compte de destination : ");

                scanf("%d", &compteDestination);

                ajouterTransaction(&listeDepots, creerTransaction(1, montant, -1, compteDestination));

                break;

            case 2:

                printf("Montant du retrait : ");

                scanf("%d", &montant);

                printf("Compte source : ");

                scanf("%d", &compteSource);

                ajouterTransaction(&listeRetraits, creerTransaction(2, montant, compteSource, -1));

                break;

            case 3:

                printf("Montant du transfert : ");

                scanf("%d", &montant);

                printf("Compte source : ");

                scanf("%d", &compteSource);

                printf("Compte de destination : ");

                scanf("%d", &compteDestination);

                ajouterTransaction(&listeTransferts, creerTransaction(3, montant, compteSource, compteDestination));

                break;

            case 4:

                afficherTransactions(&listeDepots);

                afficherTransactions(&listeRetraits);

                afficherTransactions(&listeTransferts);

                break;

            case 5:

                traiterTransactions(&listeDepots, &listeRetraits, &listeTransferts);

                printf("Transactions traitées avec succès.\n");

                break;

            case 6:

                printf("Programme terminé.\n");

                break;

            default:

                printf("Choix invalide. Veuillez entrer un choix valide.\n");

        }

    } while (choix != 6);



    return 0;

}
