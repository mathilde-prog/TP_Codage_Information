#include "codeurs.h"

/**
 * \file codeurs.c
 * \brief Fonctions relatives aux codeurs HDBn et Arithmétique
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void calculer_codage_arithmetique(float ** matArithmetique, int * data, int nb_caracteres, int longueurData, float * f)
 * \brief Calcul du codage arithmétique avec les intervalles et récupération de la valeur définitive de f
 * \param float ** matArithmetique Matrice arithmétique
 * \param int * data Tableau de données d'entiers
 * \param int nb_caracteres Nombre de caractères
 * \param int longueurData Longueur des données
 * \param float * f Nombre à virgule flottante
*/
void calculer_codage_arithmetique(float ** matArithmetique, int * data, int nb_caracteres, int longueurData, float * f){
  int i, a;
  float bornInf, bornSup, intervalle;

  for(i=0; i<longueurData; i++){ //Parcours du message à coder
    for(a=0; a<nb_caracteres; a++){ //Parcours de la matrice où sont stockées les données
      if(matArithmetique[a][0] == (float)data[i]){
        if(i>0){
          intervalle = bornSup - bornInf;
          bornSup = bornInf+(matArithmetique[a][3]*intervalle);
          bornInf = bornInf+(matArithmetique[a][2]*intervalle);
        }
        else{ //Première lettre
          intervalle = matArithmetique[a][3] - matArithmetique[a][2];
          bornInf = matArithmetique[a][2];
          bornSup = matArithmetique[a][3];
        }
      }
    }
  }
  *f = bornInf;
}

/**
 * \fn void triBulle_Mat(int ** Mat, int lignes, int colonneComparaison)
 * \brief Tri bulle d'une matrice d'entiers en fonction de la colonne passée en paramètre
 * \param int ** Mat Matrice d'entiers
 * \param int lignes Nombre de lignes
 * \param int colonneComparaison Colonne de comparaison
*/
void triBulle_Mat(int ** Mat, int lignes, int colonneComparaison){
  int i, j, echange1, echange2;

  for(i = 0; i < lignes; i++){
    for(j = lignes-1; j > i; j--){
      if(Mat[j][colonneComparaison] < Mat[j-1][colonneComparaison]){
        echange1 = Mat[j-1][colonneComparaison];
        echange2 = Mat[j-1][1];

        Mat[j-1][colonneComparaison] = Mat[j][colonneComparaison];
        Mat[j-1][1] = Mat[j][1];

        Mat[j][colonneComparaison] = echange1;
        Mat[j][1] = echange2;
      }
    }
  }
}

/**
 * \fn void afficherMatrice_float(float ** matrice, int ligne, int colonne)
 * \brief Affichage d'une matrice de float
 * \param float ** matrice Matrice de float
 * \param int ligne Nombre de lignes
 * \param int colonne Nombre de colonnes
*/
void afficherMatrice_float(float ** matrice, int ligne, int colonne){
  int l;

  printf(" |--------------------------------|\n");
  printf(" | Carac | Fréq |   Intervalles   |\n");
  printf(" |--------------------------------|\n");
  for(l = 0; l < ligne; l++){
    printf(" |   %c   |  %d   | %.4f ; %.4f |\n", (char)matrice[l][0], (int)matrice[l][1], matrice[l][2], matrice[l][3]);
  }
  printf(" |--------------------------------|\n");
  printf("\n");
}

/**
 * \fn void tab2Mat(int * tab, int ** mat, int lignes, int * nb_caracteres)
 * \brief Copie des valeurs d'un tableau d'entiers dans une matrice d'entiers à la colonne 0 et ajout de la fréquence de chaque valeur dans la 2ème colonne
 * \param int ** tab Tableau d'entiers
 * \param int ** mat Matrice d'entiers
 * \param int lignes Nombre de lignes
 * \param int * nb_caracteres Pointeur sur nombre de caractères
*/
void tab2Mat(int * tab, int ** mat, int lignes, int * nb_caracteres){
  int compteur, i, j, m;
  *nb_caracteres = 0;
  /* Parcours du message à copier */
  for(i=0; i<lignes; i++){
    /* Test si la valeur de tab[i] est déjà inscrite dans la matrice */
    for(m=0; (m<i) && (mat[m][0]!=tab[i]); m++);
    //Valeur déjà enregistrée dans le tableau
    if(mat[m][0] == tab[i]){
      mat[i][0] = tab[i];
      mat[i][1] = 0; //fréquence mise à 0 pour pouvoir par la suite supprimer cette ligne de la matrice
    }
    //Nouveau caractere
    else{
      compteur = 1;
      (*nb_caracteres)++;
      //Comptage du nombre de fois où le caractère apparait dans le message
      for(j=i+1; j<lignes; j++){
        if(tab[j] == tab[i]){
          compteur++;
        }
      }
      mat[i][0] = tab[i];
      mat[i][1] = compteur;
    }
  }
}

/**
 * \fn void encodeurHDBn_Arithmetique(int encodeur, int longueurData, int * data, float * f, int * p, int * n)
 * \brief Fonction d'encodage HDBn et arithmétique
 * \param int encodeur
 * \param int longueurData
 * \param int * data Tableau de données d'entiers
 * \param int * p Tableau d'entiers pour contenir les valeurs positives
 * \param int * n Tableaux d'entiers pour contenir les valeurs négatives
*/
void encodeurHDBn_Arithmetique(int encodeur, int longueurData, int * data, float * f, int * p, int * n){
  int i;

  switch(encodeur){
    /* ******* ENCODEUR HDBn ******* */
    case 2 : case 3 : case 4 : {
      int nb = encodeur; //Nombre de '0' a ne pas dépasser
      int * code = NULL;

      if((code = malloc(sizeof(int)*longueurData)) == NULL){
        fprintf(stderr,"encodeurHDBn_Arithmetique: débordement mémoire lors de la création du tableau code\n");
        exit(1);
      }

      int dernierViol = -1;
      int dernierUn = -1;
      int nbZero = 0;

      /* Parcours de la séquence à coder */
      for(i=0; i<longueurData; i++){
        //Le bit courant est 0
        if(data[i] == 0){
          nbZero++;
          //Trop de '0' à la suite, nbZero > nb
          if(nbZero == nb+1){
            //dernierViol positif
            if(dernierViol > 0){
              code[i] = -1; //V-
              //dernierUn positif
              if(dernierUn > 0){
                code[i-nb] = -1; //B-
                dernierUn = code[i-nb]; //Actualisation du dernierUn
              }
            }
            //dernierViol négatif
            else{
              code[i] = 1; //V+
              //dernierUn négatif
              if(dernierUn < 0){
                code[i-nb] = 1; //B+
                dernierUn = code[i-nb]; //Actualisation du dernierUn
              }
            }
            dernierViol = code[i]; //Actualisation du dernierViol
            nbZero = 0; //Actualisation du nbZero : remise à 0
          }
          //nbZero < n donc valeur encodé : 0
          else{
            code[i] = 0;
          }
        }
        //Le bit courant est 1
        else{
          nbZero=0; //Actualisation du nbZero : remise à 0
          //dernierUn négatif
          if(dernierUn < 0){
            code[i]=1;
          }
          //dernierUn positif
          else{
            code[i]=-1;
          }
          dernierUn = code[i]; //Actualisation du dernierUn
        }
      }
      /* Affichage du message codé */
      printf(" Message codé : ");
      afficherTab(code, longueurData);

      /* Récupération des valeurs positives et négatives du signal : implémentation de p et n */
      for(i=0; i<longueurData; i++){
        switch (code[i]) {
          case 0 :  p[i] = 0;
                    n[i] = 0;
                    break;
          case 1 :  p[i] = 1;
                    n[i] = 0;
                    break;
          case -1 : p[i] = 0;
                    n[i] = 1;
                    break;
          default : printf("ERREUR : valeur code[%d] incorrecte: %d .\n", i, code[i]);
                    break;
        }
      }

      free(code);
      break;
    }

    /* ******* ENCODEUR Arithmétique ******* */
    case 1 : {
      int ** matOrdreAlpha_Freq = alloue_matrice(longueurData, 2); //Matrice dans laquelle se trouvera le message à coder avec la fréquence d'apparition de chaque caractère
      int nb_caracteres, ll, le, c;
      float intervalleRef = 1/(float)longueurData; //Valeur de l'intervalle de référence pour un caractère
      float interMin = 0.00, interMax; //Bornes d'un intervalle : [interMin interMax]

      /* Copie du message à coder (data) dans une matrice 'matOrdreAlpha_Freq' de taille 2 + ajout des fréquences de chaque caractère */
      tab2Mat(data, matOrdreAlpha_Freq, longueurData, &nb_caracteres);
      /* Tri par ordre croissant des caractères (ordre alphabétique) */
      triBulle_Mat(matOrdreAlpha_Freq, longueurData, 0);

      //Allocation d'une matrice de taille 4
      float ** matArithmetique = alloue_matrice_float(nb_caracteres, 4); //Matrice dans laquelle se trouvera les informations nécéssaires à l'encodage

      /* Copie de matOrdreAlpha_Freq dans une matrice 'matArithmetique' & calculs + ajoute les bornes d'intervalles de chaque caractère */
      for(ll=0, le=0; ll<longueurData; ll++){ // ll : ligne lecture, le : ligne écriture
        //Ajoute chaque caractères une seule fois : si la fréquence est de 0, la lettre apparait plus d'une fois, sa véritable fréquence est enregistrée au moment de sa première apparition
        if(matOrdreAlpha_Freq[ll][1] != 0){
          for(c=0; c<2; c++){
            matArithmetique[le][c] = matOrdreAlpha_Freq[ll][c];
          }
          /* Ajout des intervalles */
          matArithmetique[le][2] = interMin;
          interMax = interMin+(matArithmetique[le][1]*intervalleRef);
          matArithmetique[le][3] = interMax;
          interMin = interMax;
          le++;
        }
      }
      //Affichage de la matrice contenant les informations nécéssaires à l'encodage
      afficherMatrice_float(matArithmetique, nb_caracteres, 4);

      //Lancement du calcul arithmétique : f
      calculer_codage_arithmetique(matArithmetique, data, nb_caracteres, longueurData, f);

      /* Libération de mémoire */
      free_matrice(matOrdreAlpha_Freq,longueurData);
      free_matrice_float(matArithmetique,nb_caracteres);
    }
  }

}

/**
 * \fn void afficherTab(int * tab, int nb)
 * \brief Affichage d'un tableau d'entiers
 * \param int * tab Tableau d'entiers
 * \param int nb Taille du tableau
*/
void afficherTab(int * tab, int nb){
  for(int i=0; i<nb; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}

/**
 * \fn int ** alloue_matrice (int lignes, int colonnes)
 * \brief Alloue une matrice d'entiers dont les dimensions sont passées en paramètres
 * \param int lignes Nombre de lignes
 * \param int colonnes Nombre de colonnes
 * \return Matrice d'entiers allouée dynamiquement
*/
int ** alloue_matrice (int lignes, int colonnes){
  int l;
  int ** matrice = NULL;

  if((matrice = malloc(lignes*sizeof(int*))) == NULL){
    fprintf(stderr,"alloue_matrice: débordement mémoire lors de la création d'une matrice\n");
    exit(1);
  }

  for(l = 0; l < lignes; l++){
    if((matrice[l] = malloc(colonnes*sizeof(int))) == NULL){
      fprintf(stderr,"alloue_matrice: débordement mémoire lors de la création d'une matrice\n");
      exit(1);
    }
  }

  return matrice;
}

/**
 * \fn float ** alloue_matrice_float (int lignes, int colonnes)
 * \brief Alloue une matrice de float dont les dimensions sont passées en paramètres
 * \param int lignes Nombre de lignes
 * \param int colonnes Nombre de colonnes
 * \return Matrice de float allouée dynamiquement
*/
float ** alloue_matrice_float (int lignes, int colonnes){
  int l;
  float ** matrice = NULL;

  if((matrice = malloc(lignes*sizeof(float*))) == NULL){
    fprintf(stderr,"alloue_matrice: débordement mémoire lors de la création d'une matrice\n");
    exit(1);
  }

  for(l = 0; l < lignes; l++){
    if((matrice[l] = malloc(colonnes*sizeof(float))) == NULL){
      fprintf(stderr,"alloue_matrice: débordement mémoire lors de la création d'une matrice\n");
      exit(1);
    }
  }

  return matrice;
}

/**
 * \fn void free_matrice(int ** matrice, int lignes)
 * \brief Libère la mémoire allouée pour la matrice d'entiers
 * \param int ** matrice Matrice
 * \param int lignes Nombre de lignes
*/
void free_matrice(int ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((int*) matrice[i]);
  }

  free(matrice);
}

/**
 * \fn void free_matrice_float(float ** matrice, int lignes)
 * \brief Libère la mémoire allouée pour la matrice de float
 * \param float ** matrice Matrice
 * \param int lignes Nombre de lignes
*/
void free_matrice_float(float ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((float*) matrice[i]);
  }

  free(matrice);
}
