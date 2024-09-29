#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Etudiant{

    char Nom[20];
    char Prénom[20];
    int nbr_eleve;
    struct Etudiant * next;


}Etudiant;

typedef struct filliere{

    char nom_fe[100];
    int nbr_eleve;
    Etudiant * list_etd[nbr_eleve];
    struct filliere * next;


}filiere;





void ajouter_filliere(filliere **head, char *nom_fe,int *nbr_eleve){
    filliere *new_filliere =  (filliere*)malloc(sizeof(filliere));
    if(new_filliere==NULL){
        printf("Erreur d'allocation de mémoire!\n");
        return ;
    }
    strcpy(new_filliere->nom_fe,nom_fe);
    new_filliere->nbr_eleve = nbr_eleve;

    new_filliere->next = *head ;
    *head = new_filliere;
}

void afficher_filliere(filliere *head){
    filliere *temp = head;
    while(temp != NULL){
        printf("Nom de la filiere : %s\n", temp->nom);
        printf("Nombre d'etudiants : %d\n", temp->nbEtudiants);
        printf("\n");
        temp = temp->next;

    }

}
void Permuter(filliere *a, filliere *b)
{
    int t;
    t=a->data;
    a->data=b->data;
    b->data=t;
}

void trier_filieres(Filiere* head) {
    int echange;
    Filiere* temp;
    Filiere* cemp = NULL;
    do {
        echange = 0;
        temp = head;
        while (temp->next != next) {
            if (actuelle->nbEtudiants > actuelle->suivante->nbEtudiants) {
                // Permuter les filières
                char tempNom[50];
                int tempNbEtudiants;

                strcpy(tempNom, actuelle->nom);
                strcpy(actuelle->nom, actuelle->suivante->nom);
                strcpy(actuelle->suivante->nom, tempNom);

                tempNbEtudiants = actuelle->nbEtudiants;
                actuelle->nbEtudiants = actuelle->suivante->nbEtudiants;
                actuelle->suivante->nbEtudiants = tempNbEtudiants;

                echange = 1;
            }
            actuelle = actuelle->suivante;
        }
        suivante = actuelle;
    } while (echange);
}

