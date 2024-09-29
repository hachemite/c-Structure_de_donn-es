struct materiel {
  int id;
  char nom[50];
  float prix;
  int quantite;
  struct materiel *precedent;
  struct materiel *suivant;
};

struct liste {
  struct materiel *debut;
  struct materiel *fin;
  int taille;
};

void initialiser_liste(liste *l) {
  l->debut = NULL;
  l->fin = NULL;
  l->taille = 0;
}

void inserer_debut(liste *l, materiel m) {
  struct materiel *nouveau = malloc(sizeof(struct materiel));
  nouveau->id = m.id;
  strcpy(nouveau->nom, m.nom);
  nouveau->prix = m.prix;
  nouveau->quantite = m.quantite;
  nouveau->precedent = NULL;
  nouveau->suivant = l->debut;

  if (l->debut != NULL) {
    l->debut->precedent = nouveau;
  }

  l->debut = nouveau;

  if (l->fin == NULL) {
    l->fin = nouveau;
  }

  l->taille++;
}

void inserer_fin(liste *l, materiel m) {
  struct materiel *nouveau = malloc(sizeof(struct materiel));
  nouveau->id = m.id;
  strcpy(nouveau->nom, m.nom);
  nouveau->prix = m.prix;
  nouveau->quantite = m.quantite;
  nouveau->precedent = l->fin;
  nouveau->suivant = NULL;

  if (l->fin != NULL) {
    l->fin->suivant = nouveau;
  }

  l->fin = nouveau;

  if (l->debut == NULL) {
    l->debut = nouveau;
  }

  l->taille++;
}

void supprimer_debut(liste *l) {
  if (l->debut == NULL) {
    return;
  }

  struct materiel *aSupprimer = l->debut;
  l->debut = l->debut->suivant;

  if (l->debut != NULL) {
    l->debut->precedent = NULL;
  }

  if (l->fin == aSupprimer) {
    l->fin = NULL;
  }

  free(aSupprimer);
  l->taille--;
}

void supprimer_fin(liste *l) {
  if (l->fin == NULL) {
    return;
  }

  struct materiel *aSupprimer = l->fin;
  l->fin = l->fin->precedent;

  if (l->fin != NULL) {
    l->fin->suivant = NULL;
  }

  if (l->debut == aSupprimer) {
    l->debut = NULL;
  }

  free(aSupprimer);
  l->taille--;
}

void afficher_liste(liste *l) {
  struct materiel *courant = l->debut;

  while (courant != NULL) {
    printf("ID: %d\n", courant->id);
    printf("Nom: %s\n", courant->nom);
    printf("Prix: %.2f\n", courant->prix);
    printf("Quantité: %d\n\n", courant->quantite);
    courant = courant->suivant;
  }
}
void ajouter_materiel(liste *l, materiel m) {
  // Demande à l'utilisateur de choisir l'emplacement d'insertion
  int choix;
  do {
    printf("Choisissez l'emplacement d'insertion :\n");
    printf("1. Début\n");
    printf("2. Fin\n");
    printf("3. Après un matériel (par ID)\n");
    scanf("%d", &choix);
  } while (choix < 1 || choix > 3);

  switch (choix) {
    case 1:
      inserer_debut(l, m);
      break;
    case 2:
      inserer_fin(l, m);
      break;
    case 3:
      int id;
      printf("Entrez l'ID du matériel après lequel insérer : ");
      scanf("%d", &id);
      struct materiel *precedent = rechercher_materiel(l, id);
      if (precedent != NULL) {
        inserer_apres(l, m, precedent);
      } else {
        printf("Matériel introuvable !\n");
      }
      break;
  }
}

void modifier_materiel(liste *l, int id) {
  struct materiel *m = rechercher_materiel(l, id);

  if (m != NULL) {
    printf("Entrez le nouveau nom : ");
    scanf("%s", m->nom);

    printf("Entrez le nouveau prix : ");
    scanf("%f", &m->prix);

    printf("Entrez la nouvelle quantité : ");
    scanf("%d", &m->quantite);
  } else {
    printf("Matériel introuvable !\n");
  }
}

void supprimer_materiel(liste *l, int id) {
  struct materiel *aSupprimer = rechercher_materiel(l, id);

  if (aSupprimer != NULL) {
    if (aSupprimer == l->debut) {
      supprimer_debut(l);
    } else if (aSupprimer == l->fin) {
      supprimer_fin(l);
    } else {
      supprimer_apres(l, aSupprimer->precedent);
    }
    free(aSupprimer);
  } else {
    printf("Matériel introuvable !\n");
  }
}
struct materiel *rechercher_materiel(liste *l, int id) {
  struct materiel *courant = l->debut;

  while (courant != NULL && courant->id != id) {
    courant = courant->suivant;
  }

  return courant;
}


void trier_par_id(liste *l) {
  // Tri par insertion
  struct materiel *courant = l->debut;

  while (courant != NULL) {
    struct materiel *suivant = courant->suivant;

    while (suivant != NULL && courant->id > suivant->id) {
      // Echange des valeurs
      int tempId = courant->id;
      strcpy(tempNom, courant->nom);
      float tempPrix = courant->prix;
      int tempQuantite = courant->quantite;

      courant->id = suivant->id;
      strcpy(courant->nom, suivant->nom);
      courant->prix = suivant->prix;
      courant->quantite = suivant->quantite;

      suivant->id = tempId;
      strcpy(suivant->nom, tempNom);
      suivant->prix = tempPrix;
      suivant->quantite = tempQuantite;

      suivant = suivant->suivant;
    }

    courant = courant->suivant;
  }
}

void trier_par_nom(liste *l) {
  // Tri par sélection
  struct materiel *courant = l->debut;

  while (courant != NULL) {
    struct materiel *min = courant;
    struct materiel *suivant = courant->suivant;

    while (suivant != NULL) {
      if (strcmp(suivant->nom, min->nom) < 0) {
        min = suivant;
      }
      suivant = suivant->suivant;
    }

    // Echange des valeurs
    int tempId = courant->id;
    strcpy(tempNom, courant->nom);
    float tempPrix = courant->prix;
    int tempQuantite = courant->quantite;

    courant->id = min->id;
    strcpy(courant->nom, min->nom);
    courant->prix = min->prix;
    courant->quantite = min->quantite;

    min->id = tempId;
    strcpy(min->nom, tempNom);
    min->prix = tempPrix;
    min->quantite = tempQuantite;

    courant = courant->suivant;
  }
}

void trier_par_prix(liste *l) {
  // Tri par insertion
  struct materiel *courant = l->debut;

  while (courant != NULL) {
    struct materiel *suivant = courant->suivant;

    while (suivant != NULL && courant->prix > suivant->prix) {
      // Echange des valeurs
      int tempId = courant->id;
      strcpy(tempNom, courant->nom);
      float tempPrix = courant->prix;
      int tempQuantite = courant->quantite;

      courant->id = suivant->id;
      strcpy(courant->nom, suivant->nom);
      courant->prix = suivant->prix;
      courant->quantite = suivant->quantite;

      suivant->id = tempId;
      strcpy(suivant->nom, tempNom);
      suivant->prix = tempPrix;
      suivant->quantite = tempQuantite;

      suivant = suivant->suivant;
    }

    courant = courant->suivant;
  }
}

void trier_par_quantite(liste *l) {
  // Tri par insertion
  struct materiel *courant = l->debut;

  while (courant != NULL) {
    struct materiel *suivant = courant->suivant;

    while (suivant != NULL && courant->quantite > suivant->quantite) {
      // Echange des valeurs
      int tempId = courant->id;
      strcpy(tempNom, courant->nom);
      float tempPrix = courant->prix;
      int tempQuantite = courant->quantite;

      courant->id = suivant->id;
      strcpy(courant->nom, suivant->nom);
      courant->prix = suivant->prix;
      courant->quantite = suivant->quantite;

      suivant->id = tempId;
      strcpy(suivant->nom, tempNom);
      suivant->prix = tempPrix;
      suivant->quantite = tempQuantite;

      suivant = suivant->suivant;
    }

    courant = courant->suivant;
  }
}
int main() {
  liste l;
  initialiser_liste(&l);

  int choix;
  do {
    // Menu principal
    printf("**Gestion des matériels**\n");
    printf("1. Ajouter un matériel\n");
    printf("2. Modifier un matériel\n");
    printf("3. Supprimer un matériel\n");
    printf("4. Rechercher un matériel\n");
    printf("5. Afficher la liste des matériels\n");
    printf("6. Trier la liste\n");
    printf("7. Sauvegarder la liste\n");
    printf("8. Charger la liste\n");
    printf("9. Quitter\n");
    scanf("%d", &choix);

    switch (choix) {
      case 1:
        // Ajouter un matériel
        materiel m;
        printf("Entrez l'ID du matériel : ");
        scanf("%d", &m.id);
        printf("Entrez le nom du matériel : ");
        scanf("%s", m.nom);
        printf("Entrez le prix du matériel : ");
        scanf("%f", &m.prix);
        printf("Entrez la quantité du matériel : ");
        scanf("%d", &m.quantite);
        ajouter_materiel(&l, m);
        break;
      case 2:
        // Modifier un matériel
        int id;
        printf("Entrez l'ID du matériel à modifier : ");
        scanf("%d", &id);
        modifier_materiel(&l, id);
        break;
      case 3:
        // Supprimer un matériel
        int id;
        printf("Entrez l'ID du matériel à supprimer : ");
        scanf("%d", &id);
        supprimer_materiel(&l, id);
        break;
      case 4:
        // Rechercher un matériel
        int id;
        printf("Entrez l'ID du matériel à rechercher : ");
        scanf("%d", &id);
        struct materiel *m = rechercher_materiel(&l, id);
        if (m != NULL) {
          printf("Matériel trouvé :\n");
          printf("ID: %d\n", m->id);
          printf("Nom: %s\n", m->nom);
          printf("Prix: %.2f\n", m->prix);
          printf("Quantité: %d\n", m->quantite);
        } else {
          printf("Matériel introuvable !\n");
        }
        break;
      case 5:
        // Afficher la liste des matériels
        afficher_liste(&l);
        break;
      case 6:
        // Trier la liste
        int choixTri;
        do {
          printf("Choisissez le critère de tri :\n");
          printf("1. ID\n");
          printf("2. Nom\n");
          printf("3. Prix\n");
          printf("4. Quantité\n");
          scanf("%d", &choixTri);
        } while (choixTri < 1 || choixTri > 4);
        switch (choixTri) {
          case 1:
            trier_par_id(&l);
            break;
          case 2:
            trier_par_nom(&l);
            break;
          case 3:
            trier_par_prix(&l);
            break;
          case 4:
            trier_par_quantite(&l);
            break;
        }
        break;
      case 7:
        // Sauvegarder la liste
        char nomFichier[50];
        printf("Entrez le nom du fichier de sauvegarde : ");
        scanf("%s", nomFichier);
        sauvegarder_liste(&l, nomFichier);
        break;
      case 8:
        // Charger la liste
        char nomFichier[50];
        printf("Entrez le nom du fichier à charger : ");
        scanf("%s", nomFichier);
        charger_liste(&l, nomFichier);
        break;
    }
  } while (choix != 9);

  return 0;
}
