#include "matrice_tab.h"

/**
 * \file matrice_tab.c
 * \brief Fonctions relatives aux matrices et tableaux 
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int ** alloue_matrice (int lignes, int colonnes)
 * \brief Alloue une matrice dont les dimensions sont passées en paramètres
 * \param int lignes Nombre de lignes
 * \param int colonnes Nombre de colonnes
 * \return Matrice allouée dynamiquement
*/
int ** alloue_matrice (int lignes, int colonnes){
  int l;
  int ** matrice = malloc(lignes*sizeof(int*));

  for(l = 0; l < lignes; l++){
    matrice[l] = malloc(colonnes*sizeof(int));
  }

  return matrice;
}

/**
 * \fn void free_matrice(int ** matrice, int lignes)
 * \brief Libère la mémoire allouée pour la matrice
 * \param int ** matrice Matrice
 * \param int lignes Nombre de lignes
 * \return Rien
*/
void free_matrice(int ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((int*) matrice[i]);
  }

  free(matrice);
}

/**
 * \fn void afficherTableau (int * tab, int taille)
 * \brief Affiche le tableau passé en paramètre
 * \param int * tab
 * \param int taille
 * \return Rien
*/
void afficherTableau (int * tab, int taille){
  int i;

  for(i = 0; i < taille; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}

/**
 * \fn void afficherMatrice(int ** matrice, int ligne, int colonne )
 * \brief Affiche la matrice passée en paramètre
 * \param int ** matrice Matrice
 * \param int ligne Nombre de lignes
 * \param int colonne Nombre de colonnes
 * \return Rien
*/
void afficherMatrice(int ** matrice, int ligne, int colonne ){
  int l, c;

  for(l = 0; l < ligne; l++){
    for(c = 0; c < colonne; c++){
      printf("%2d ",matrice[l][c]);
    }
    printf("\n");
  }
}

void afficherMatriceResultat(int ** matrice, int ligne, int colonne ){
  int l, c;

  for(l = 0; l < ligne; l++){
    if(matrice[l][0] != 0){
      printf("Séquence %2d : ",l+1);
    }
    for(c = 0; c < colonne; c++){
      if(matrice[l][c] != 0){
        printf("%2d ",matrice[l][c]);
      }
    }
    if(matrice[l][c-1] != 0){
      printf("\n");
    }
  }
}
