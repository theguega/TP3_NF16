#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

#define MAX_LEN 20

/* **********************************
 * Création et initialisation Produit
 ********************************** */
T_Produit *creerProduit(char *designation, float prix, int quantite)
{
    T_Produit *nouveauProduit = NULL;

    nouveauProduit = malloc(sizeof(T_Produit));
    if (nouveauProduit != NULL)
    {
        // l'allocation mémoire s'est bien passée
        nouveauProduit->designation = malloc(strlen(designation) + 1); // Important : malloc permet d'avoir l'espace mémoire dédié pour notre champ de structure
        strcpy(nouveauProduit->designation,designation);
        nouveauProduit->prix = prix;
        nouveauProduit->quantite_en_stock = quantite;
        nouveauProduit->suivant = NULL;
    }

    return nouveauProduit;
}



/* ********************************
 * Création et initialisation Rayon
 ******************************** */
T_Rayon *creerRayon(char *nom)
{
    T_Rayon *nouveauRayon = NULL;

    nouveauRayon = malloc(sizeof(T_Rayon));
    if (nouveauRayon != NULL)
    {
        // l'allocation mémoire s'est bien passée
        nouveauRayon->nom_rayon = malloc(strlen(nom) + 1);
        strcpy(nouveauRayon->nom_rayon,nom);
        nouveauRayon->liste_produits = NULL;
        nouveauRayon->suivant = NULL;
    }

    return nouveauRayon;
}



/* **********************************
 * Création et initialisation Magasin
 ********************************** */
T_Magasin *creerMagasin(char *nom)
{
    T_Magasin *nouveauMagasin = NULL;

    nouveauMagasin = malloc(sizeof(T_Magasin));
    if (nouveauMagasin != NULL)
    {
        nouveauMagasin->nom = malloc(strlen(nom) + 1);
        strcpy(nouveauMagasin->nom,nom);
        nouveauMagasin->liste_rayons = NULL;
    }

    return nouveauMagasin;
}



/* ********************************
 * Ajout d'un rayon dans un magasin
 ******************************** */
int ajouterRayon(T_Magasin *magasin, char *nomRayon)
{

    T_Rayon *rayon = magasin->liste_rayons; //on recup  le premier rayon de la liste
    T_Rayon *nouveau_rayon=creerRayon(nomRayon); //on creer un nouveau rayon qu'il faudra ajouter au bon endroit

    if (rayon == NULL || strcmp(nouveau_rayon->nom_rayon,rayon->nom_rayon)<0)
    {
        //dans le cas ou le nouveau rayon a ajouter est situe avant le premier rayon ou qu'il n'existe pas de premier rayon :
        //l'ancien premier devient le deuxieme et le nouveau rayon devient premier (dans le cas ou pas de premier rayon : nouveau.suivanbt sera null

        magasin->liste_rayons = nouveau_rayon; //ce nouveau rayon devient le premier element de la liste rayons

        nouveau_rayon->suivant = rayon; //prendra null si il n'y avais pas de rayon en tete
        return 1;
    }
    else
    {
        while (rayon->suivant != NULL)
        {
            //on parcour maintenant la liste des rayons
            printf("%s %s",nouveau_rayon->nom_rayon,rayon->nom_rayon);
            if (strcmp(nouveau_rayon->nom_rayon,rayon->nom_rayon)==0 || strcmp(nouveau_rayon->nom_rayon,rayon->suivant->nom_rayon)==0)
            {
                //si le rayon existe deja : on ne fais rien
                return 1;
            }
            
            else if (strcmp(nouveau_rayon->nom_rayon,rayon->nom_rayon)>0 && strcmp(nouveau_rayon->nom_rayon,rayon->suivant->nom_rayon)<0)
            {
                //dans le cas ou notre rayon a ajouter est situé entre le rayon et le rayon suivant, on l'ajoute :

                nouveau_rayon->suivant = rayon->suivant; //le succésseur de notre nouveau rayon devient le successeur du rayon initial
                rayon->suivant = nouveau_rayon; //le suivant du rayon devient le nouveau
                return 1;

            }
            rayon = rayon->suivant;
        }
        if (rayon->suivant == NULL && strcmp(nouveau_rayon->nom_rayon,rayon->nom_rayon)!=0) //le strcmp sert a traiter le cas ou on ajoute un rayon alors qu'il existe deja et qu'il est seul (ne rentre pas dans le while d'avant car il n'a pas de suivant si il est seul)
        {
            //si on arrive au but de la liste : on l'ajoute au bout
            rayon->suivant = nouveau_rayon; //le suivant du rayon devient le nouveau
            return 1;
        }
    }
    return 0;
}


/* ********************************
 * Ajout d'un produit dans un rayon
 ******************************** */
int ajouterProduit(T_Rayon *rayon,char *designation, float prix, int quantite)
{
    T_Produit *produit = rayon->liste_produits; //on recup  le premier rayon de la liste
    T_Produit *nouveau_produit=creerProduit(designation, prix, quantite); //on creer un nouveau produit

    if (produit == NULL || (nouveau_produit->prix-produit->prix<0 && nouveau_produit->designation != produit->designation))
    {
        //dans le cas ou il n'existe pas de premier produit :
        //ou que le nouveau produit est ˆ ajouter au tout debut

        rayon->liste_produits = nouveau_produit; //ce nouveau produit devient le premier element de la liste produit
        
        nouveau_produit->suivant = produit; //prendra null si la liste etait vide
        return 1;
    }
    else
    {
        while (produit->suivant != NULL)
        {
            if (strcmp(nouveau_produit->designation,produit->designation)==0 || strcmp(nouveau_produit->designation,produit->suivant->designation)==0)
            {
                //si le produit existe deja : on ne fais rien
                return 1;
            }
            else if ((nouveau_produit->prix - produit->prix)>0 && (nouveau_produit->prix - produit->suivant->prix)<=0)
            {
                //dans le cas ou notre produit a ajouter est situe entre le produit et son suivant, on l'ajoute entre les deux :

                nouveau_produit->suivant = produit->suivant; //le successeur de notre nouveau produit devient le successeur du produit initial
                produit->suivant = nouveau_produit; //le suivant du produit devient le nouveau
                return 1;

            }
            produit = produit->suivant; //si pas d'ajout, on passe au suivant

        }
        if (produit->suivant == NULL && strcmp(nouveau_produit->designation,produit->designation)!=0)
        {
            //si on arrive au boutt de la liste : on l'ajoute au bout
            produit->suivant = nouveau_produit; //le suivant du produit devient le nouveau
            return 1;
        }
    }
    return 0;
}



/* *****************************************
 * Affichage de tous les rayons d'un magasin
 ***************************************** */
void afficherMagasin(T_Magasin *magasin)
{
    if (magasin->liste_rayons == NULL)
    {
        //si aucun rayon n'existe pour le moment dans le magasion, on n'affiche le message suivant
        printf("\nVotre magasin ne contient aucun rayon\n");
    }
    else
    {
        printf("\nNom\tNombres de produits\n\n");
        T_Rayon *rayon = magasin->liste_rayons; //on recupere  le premier rayon de la liste
        while (rayon != NULL)
        {
            //on parcour la liste des produits du rayon
            T_Produit *produit = rayon->liste_produits; //on recupere le premier produit de la liste
            
            if (produit != NULL)
            {
                    int compteur_produit=0;
                    while (produit!=NULL)
                    {
                        compteur_produit++; //on compte tous les produits
                        produit=produit->suivant;
                    }
                    printf("%s\t%d\n",rayon->nom_rayon,compteur_produit);
            } else {
                printf("%s\t0\n",rayon->nom_rayon); //si aucun produit dans le rayon : on affiche 0
            }
            rayon = rayon->suivant;
        }
    }
}



/* *****************************************
 * Affichage de tous les produits d'un rayon
 ***************************************** */
void afficherRayon(T_Rayon *rayon, T_Magasin *liste_rayons)
{
    if (rayon->liste_produits == NULL)
    {
        //si aucun rayon n'existe pour le moment dans le magasion, on n'affiche le message suivant
        printf("\nVotre rayon ne contient aucun produit\n");
    }
    else
    {
        T_Produit *produit = rayon->liste_produits; //on recupere  le premier produit de la liste
        if(liste_rayons==NULL) {
            printf("\nDesignation\t\tPrix\tQuantite\n\n");
            while (produit != NULL)
            {
                printf("%11s\t\t%3.2f\t%8d\n",produit->designation,produit->prix,produit->quantite_en_stock);
                
                produit=produit->suivant; //après affichage du nom du rayon et du nombre de produits, on passe au suivant
                
            }
            } else {
            printf("\nDesignation\t\tPrix\tQuantite\tRayon\n\n");
                T_Rayon *rayon_affichage = liste_rayons->liste_rayons;
                while (produit != NULL)
                {
                    printf("%11s\t\t%3.2f\t%d\t%s\n",produit->designation,produit->prix,produit->quantite_en_stock,rayon_affichage->nom_rayon);
                    
                    produit=produit->suivant; //après affichage du nom du rayon et du nombre de produits, on passe au suivant
                    rayon_affichage=rayon_affichage->suivant;
                    
                }
        }
    }
}



/* **************************************
 * Suppression d'un produit dans un rayon
 ************************************** */
int supprimerProduit(T_Rayon *rayon, char* designation_produit) {
    
    
    T_Produit *produit = rayon->liste_produits; //on recup  le premier produit de la liste

    if (produit == NULL)
    {
        //dans le cas ou il n'y a aucun element dans la liste, on n'a rien a faire
        return 1;
    }
    else if (strcmp(produit->designation,designation_produit)==0)
    {
        
        //si le premier produit est celui a supprimer : on le supprime, pas besoin de recuperer les successeur
        T_Produit *tmp = rayon->liste_produits; //celui a supprimer
        rayon->liste_produits = rayon->liste_produits->suivant; //le deuxieme devient la nouvelle tete
        free(tmp);
        return 1;
        
    }
    else
    {
        //dans le cas ou la liste n'est pas vide et que celui a supprimer n'est pas en tete:
        while (produit->suivant != NULL)
        {
            //on parcour la liste
            if (strcmp(designation_produit,produit->designation)>0 && (produit->suivant->suivant== NULL || strcmp(designation_produit,produit->suivant->suivant->designation)<0))
            {
                //dans le cas ou notre produit a supprimer est situe entre le produit actuel et le successeur du produit a supprimer, on le supprime :
                //dans le cas ou le successeur du produit ˆ supprimer n'existe pas, le produit prendra comme suivant NULL ce qui reviens ˆ supprimer le dernier element de la liste
                T_Produit *tmp = produit->suivant;
                produit->suivant = produit->suivant->suivant;
                free(tmp);
                return 1;

            }
            produit = produit->suivant; //si pas de suppression, on passe au produit suivant

        }
        if (produit->suivant == NULL)
        {
            //si on arrive au bout de la liste sans avoir trouver de produit a suppr, le produit ne s'y trouve pas
            return 1;
        }
    }
    return 0;
}



/* *************************************************************
 * Suppression d'un rayon et de tous les produits qu'il contient
 ************************************************************* */
int supprimerRayon(T_Magasin *magasin, char *nom_rayon)
{
    //si le rayon a des produits, il faut les supprimer :
    //il faut d'abord recuperer l'adresse du rayon a supprimer :
    T_Rayon *rayon_suppr = recherche_rayon(magasin, nom_rayon);
    if (rayon_suppr->liste_produits != NULL) {
        //il faut supprimer tous les produits du rayon avant de pouvoir supprimer le rayon
        
        T_Produit *produit = rayon_suppr->liste_produits; //on recupere le premier produit
        while (produit != NULL) {
            //on parcourt tous les rayons
            T_Produit *tmp = produit; //on conserve l'adresse du rayon a supprimer
            produit = produit->suivant; //on passe au suivant
            free(tmp); //on supprime celui que l'on a passer
        }
    }
    
    
    
    //on peut maintenant supprimer le rayon en procŽdant de la mme faon que supprimer produit
    T_Rayon *rayon = magasin->liste_rayons; //on recup  le premier rayon de la liste

    if (rayon == NULL)
    {
        //dans le cas ou il n'y a aucun rayon dans le magasin, on n'a rien a faire
        return 1;
    }
    else if (strcmp(rayon->nom_rayon,nom_rayon)==0)
    {
        
        //si le premier rayon est celui a supprimer : on le supprime, pas besoin de recuperer les successeur
        T_Rayon *tmp = rayon; //celui a supprimer
        magasin->liste_rayons = magasin->liste_rayons->suivant; //le deuxieme devient la nouvelle tete
        free(tmp); //suppresion
        return 1;
        
    }
    else
    {
        //dans le cas ou la liste n'est aps vide et que celui a supprimer n'est pas en tete:
        while (rayon->suivant != NULL)
        {
            //on parcour la liste
            if (strcmp(nom_rayon,rayon->nom_rayon)>0 && (rayon->suivant->suivant == NULL || strcmp(nom_rayon,rayon->suivant->suivant->nom_rayon)<0))
            {
                //dans le cas ou notre rayon a supprimer est situe entre le rayon actuel et le successeur du rayon a supprimer, on le supprime :
                //dans le cas ou le successeur du produit ˆ supprimer n'existe pas, le produit prendra comme suivant NULL ce qui reviens ˆ supprimer le dernier element de la liste
                T_Rayon *tmp = rayon->suivant;
                rayon->suivant = rayon->suivant->suivant;
                free(tmp);
                return 1;

            }
            rayon = rayon->suivant; //si pas de suppression, on passe au rayon suivant

        }
        if (rayon->suivant == NULL)
        {
            //si on arrive au bout de la liste sans avoir trouver de rayon a suppr, le rayon ne s'y trouve pas
            return 1;
        }
    }
    return 0;
}



/* **************************************************************************************
 * Recherche des produits se situant dans une fourchette de prix entrée par l'utilisateur
 ************************************************************************************** */
void rechercheProduits(T_Magasin *magasin, float prix_min, float prix_max)
{
    //pour que l'affichage de sortie se fasse bien par ordre de prix, on va creer un rayon temporaire que l'on supprimera ˆ la fin.
    char tmp[20] = "!"; //nom pour etre sur qu'il soit mis en tete de liste et que par la suite on ne recupere pas une deuxieme fois les produits
    ajouterRayon(magasin, tmp);
    T_Rayon *tmp_rayon = recherche_rayon(magasin, tmp); //on recupere son adresse pour pouivoir ensuit utiliser ajouter produit
    
    //pour afficher a quel rayon le produit appartient il faut aussi conserver tous les noms de rayons -> liste de rayons -> un magasin
    T_Magasin *tmp_magasin = creerMagasin(tmp);
    
    //on parcours maintenant tous les rayons
    T_Rayon *rayon = magasin->liste_rayons; //premier rayon de la liste
    while(rayon != NULL) {
        
        //pour chaque rayons, on parcours sa liste de produits
        T_Produit *produit = rayon->liste_produits; //on recup le premier prod
        while (produit != NULL) {
            if (produit->prix<=prix_max && produit->prix>=prix_min) {
                ajouterProduit(tmp_rayon, produit->designation, produit->prix, produit->quantite_en_stock);
                ajouterListeRayon(tmp_magasin,rayon->nom_rayon);
            }
            produit = produit->suivant;
        }
        
        rayon = rayon->suivant;
    }
    
    //on affiche notre rŽsultat :
    afficherRayon(tmp_rayon, tmp_magasin);
    
    //on supprimer notre rayon temporaire
    supprimerRayon(magasin, tmp);
    
    //on supprime tous les rayons de notre magasin temporaire
    T_Rayon *res = tmp_magasin->liste_rayons;
    while (res!=NULL) {
        T_Rayon *res2 =res;
        res = res->suivant;
        free(res2);
    } free(res); //on vide res (qui est a NULL normalement)
    
    //on supprime notre magasin temporaire
    free(tmp_magasin);
}



/* *********************
 * Fusionner deux rayons
 ********************* */
void fusionnerRayons(T_Magasin *magasin) {
  printf("\nEntrez le nom du rayon premier rayon a fusionne : \n");
  char rayon_a[20];
  scanf("%s", rayon_a);
    viderBuffer();
  T_Rayon *premier_rayon = recherche_rayon(magasin, rayon_a);
  if (premier_rayon != NULL){
    printf("\nEntrez le nom du rayon deuxieme rayon a fusionne : \n");
    char rayon_b[20];
    scanf("%s", rayon_b);
      viderBuffer();
    T_Rayon *deuxieme_rayon = recherche_rayon(magasin, rayon_b);
    if (deuxieme_rayon != NULL && strcmp(rayon_a, rayon_b) != 0){
      printf("\nEntrez le nom du nouveau rayon : \n");
      char new_rayon[20];
      scanf("%s", new_rayon);
        viderBuffer();
      int result = ajouterRayon(magasin, new_rayon); // on l'ajoute
      if(result == 1){
        T_Rayon *nouveau_rayon =
            recherche_rayon(magasin, new_rayon); // on recup son adresse
      
        // on veut ajouter tous les produits des deux rayons dans un nouveau rayon
        T_Produit *produit = premier_rayon->liste_produits;
        while (produit != NULL) {
          ajouterProduit(nouveau_rayon, produit->designation, produit->prix,
                         produit->quantite_en_stock);
          produit = produit->suivant;
        }
        produit = deuxieme_rayon->liste_produits;
        while (produit != NULL) {
          ajouterProduit(nouveau_rayon, produit->designation, produit->prix,
                         produit->quantite_en_stock);
          produit = produit->suivant;
        }
      
        // on supprimer les deux ancien rayons
        supprimerRayon(magasin, rayon_a);
        supprimerRayon(magasin, rayon_b);
      }
      else {
        printf("Le nom du nouveau doit etre different. Fusion impossible");
      }
    }
    else{
      printf("Fusion impossible");
    }
  }
}



/* *********************
 * Fonctions utilitaires
 ********************* */
// Vider le buffer (utile quand on utlise des getchar() )
void viderBuffer(void)
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


//Recherche d'un rayon au sein du magasin partir de son nom pour recuperer son adresse
T_Rayon *recherche_rayon(T_Magasin *magasin, char *nomRayon) {
    if (magasin->liste_rayons == NULL) {
        printf("\nVotre magasin ne comptient aucun rayon\n");
        return NULL;
    }
    T_Rayon *rayon = magasin->liste_rayons; //on recup  le premier rayon du magasin liste
    while (rayon->suivant != NULL)
        {
            //on parcour la liste des rayons
            if (strcmp(nomRayon,rayon->nom_rayon)==0)
            {
                //on retourne son adresse :
                return rayon;
            }
            rayon=rayon->suivant;
        }
    //on arrive maintenant au dernier rayon :
    if (strcmp(nomRayon,rayon->nom_rayon)==0)
    {
        //si c'est le bon : on le retourne
        return rayon;
    }
    else {
        printf("\nVotre rayon n'existe pas\n");
        return NULL;
    }
    return NULL;
}

//CrŽation d'une liste de rayons pour afficher les rayons de recherche produits
int ajouterListeRayon(T_Magasin *magasin, char *nom_rayon) {
    if (magasin->liste_rayons == NULL) {
        //si pas encore de rayon dans notre liste de rayons, on cree le premier
        printf("nouvelle tete");
        T_Rayon *new_rayon = creerRayon(nom_rayon);
        magasin->liste_rayons=new_rayon;
        return 1;
    } else {
        //on va au bout de la liste sinon
        T_Rayon *rayon = magasin->liste_rayons;
        while (rayon->suivant!=NULL) {
            rayon = rayon->suivant;
        }
        //et on l'ajoute
        T_Rayon *new_rayon = creerRayon(nom_rayon);
        rayon->suivant=new_rayon;
        printf("nouvel element");
    }
    return 0;
}
