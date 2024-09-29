#include<stdio.h>

struct materiel{
    int id;
    char nom[50];
    float prix;
    int quatite;
    struct materiel *previous;
    struct materiel *next;

};

struct liste{
    struct materiel *head;
    struct materiel *last;
    int taille;
};

void initialiser_liste(struct liste *lst){
    lst->head = NULL;
    lst->last = NULL;
    lst->taille = 0;

}

void inserer_debut(liste* lst, materiel *mtrl){
    mtrl->previous = NULL;
    mtrl->next= lst->head;

    if(lst->head=NULL){
        m->next = lst
        lst->head->previous = mtrl;
    }
    else{
        lst->last = mtrl;
    }
    lst->head = m;
    lst->taille++;
}

void inserer_fin(liste* lst, materiel *mtrl){
    mtrl->previous = NULL;
    mtrl->next= lst->head;

    if(lst->head=NULL){
        m->next = lst
        lst->head->previous = mtrl;
    }
    else{
        lst->last = mtrl;
    }
    lst->head = m;
    lst->taille++;
}
