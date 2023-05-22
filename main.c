#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  T_Magasin *mon_magasin = NULL;

  // ============= MENU UTILISATEUR ============= */
  char choix = '0';
  while (choix != '9') {
    printf("\n======================================");
    printf("\n0. Creer un magasin");
    printf("\n1. Ajouter un rayon au magasin");
    printf("\n2. Ajouter un produit dans un rayon");
    printf("\n3. Afficher les rayons du magasin");
    printf("\n4. Afficher les produits d'un rayon");
    printf("\n5. Supprimer un produit");
    printf("\n6. Supprimer un rayon");
    printf("\n7. Rechercher un produit par prix");
    printf("\n8. Fusionner deux rayons");
    printf("\n9. Quitter");
    printf("\n======================================");
    printf("\n   Votre choix ? ");
    choix = getchar();
    viderBuffer(); // supprimer de l'entrŽe standard le retour charriot et les
                   // Žventuels caractres supplŽmentaires tapŽs par
                   // l'utilisateur

    switch (choix) {
    case '0':
      if (mon_magasin == NULL) {
        printf("Entrez votre nom de magasin : ");
        char nom_magasin[20];
        scanf("%s", nom_magasin);
        viderBuffer();
        mon_magasin = creerMagasin(nom_magasin);
        printf("Le magasin '%s' a bien ete cree\n", mon_magasin->nom);
      } else {
        printf("Vous ne pouvez pas creer un second magasin. Vous perdrez "
               "toutes vos donnees.");
      }
      break;

    case '1':
      if (mon_magasin != NULL) {
        printf("Entrez votre nom de rayon : ");
        char rayon_ajout[20];
        scanf("%s", rayon_ajout);
          viderBuffer();
          if (ajouterRayon(mon_magasin, rayon_ajout)) {
              printf("Le rayon a bien ete ajoute");
          } else {
              printf("Une erreur c'est produite");
          }
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '2':
      if (mon_magasin != NULL) {
        printf("Entrez le nom du rayon ou le produit sera range : ");
        char rayon_ajout_prod[20];
        scanf("%s", rayon_ajout_prod);
          viderBuffer();
        T_Rayon *rayon_ajout_produit =
            recherche_rayon(mon_magasin, rayon_ajout_prod);
        if (rayon_ajout_produit != NULL) {
          printf("Entrez la designation du produit : ");
          char designation[20];
          scanf("%s", designation);
            viderBuffer();
          printf("Entrez le prix du produit : ");
          float prix;
          scanf("%f", &prix);
            viderBuffer();
          printf("Entrez la quantitee du produit : ");
          int quantitee;
          scanf("%d", &quantitee);
            viderBuffer();
            if(ajouterProduit(rayon_ajout_produit, designation, prix, quantitee)) {
                printf("Le produit a bien ete ajoute");
            } else {
                printf("Une erreur c'est produite");
            }
        }
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '3':
      if (mon_magasin != NULL) {
        afficherMagasin(mon_magasin);
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '4':
      if (mon_magasin != NULL) {
        printf("Entrez le nom du rayon a afficher : ");
        char rayon_a_afficher[20];
        scanf("%s", rayon_a_afficher);
          viderBuffer();
        T_Rayon *rayon_afficher =
            recherche_rayon(mon_magasin, rayon_a_afficher);
        if (rayon_afficher != NULL) {
          afficherRayon(rayon_afficher, NULL);
        } else {
          printf("Le rayon n'existe pas.");
        }
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '5':
      if (mon_magasin != NULL) {
        printf("Entrez le nom du rayon dans lequel se situe le produit : ");
        char rayon_produit_a_suppr[20];
        scanf("%s", rayon_produit_a_suppr);
          viderBuffer();
        T_Rayon *rayon_suppr_prod =
            recherche_rayon(mon_magasin, rayon_produit_a_suppr);
        if (rayon_suppr_prod != NULL) {
          printf("Entrez le nom du produit a supprimer : ");
          char designation_suppr[20];
          scanf("%s", designation_suppr);
          viderBuffer();
          if(supprimerProduit(rayon_suppr_prod, designation_suppr)){
              printf("Le produit a bien ete supprime\n");
          } else {
              printf("Une erreur c'est produite");
          }
        } else {
          printf("Le rayon n'existe pas.");
        }
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '6':
      if (mon_magasin != NULL) {
        printf("Entrez le nom du rayon a supprimer : ");
        char rayon_a_suppr[20];
        scanf("%s", rayon_a_suppr);
          viderBuffer();
          if(supprimerRayon(mon_magasin, rayon_a_suppr)){
              printf("Le rayon a bien ete supprime\n");
          } else {
              printf("Une erreur c'est produite");
          }
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '7':
      if (mon_magasin != NULL) {
        printf("Entrez le prix minimum du produit : ");
        float prix_min;
        scanf("%f", &prix_min);
          viderBuffer();
        printf("Entrez le prix maximum du produit : ");
        float prix_max;
        scanf("%f", &prix_max);
          viderBuffer();
        rechercheProduits(mon_magasin, prix_min, prix_max);
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '8':
      if (mon_magasin != NULL) {
        fusionnerRayons(mon_magasin);
      } else {
        printf("Veuillez d'abord creer un magasin");
      }
      break;

    case '9':
      printf("\n======== PROGRAMME TERMINE ========\n");
      break;

    default:
      printf("\n\nERREUR : votre choix n'est valide ! ");
    }
    printf("\n\n\n");
  }

  return 0;
}

