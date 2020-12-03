#include "emetteur.h"

/**
 * \file emetteur.c
 * \brief Fonctions relatives à l'émetteur
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int nbUtilisateursValide(int nb)
 * \brief Retourne 1 si le nombre d'utilisateurs passé en paramètre est valide.
 * \param int nb Nombre d'utilisateurs
 * \return 1 si le nombre d'utilisateurs est valide. 0 sinon.
*/
int nbUtilisateursValide(int nb){
  return ((nb == 1) || (nb == 2) || (nb == 4) || (nb == 8) || (nb == 16));
}

/**
 * \fn void choixNbUtilisateurs(int * nbUtilisateurs)
 * \brief Choix du nombre d'utilisateurs
 * \param int * nbUtilisateurs Nombre d'utilisateurs
 * \return Rien
*/
void choixNbUtilisateurs(int * nbUtilisateurs){
  do {
    printf("\nSaisir le nombre d'utilisateurs : ");
    scanf("%d",nbUtilisateurs);

    if(!nbUtilisateursValide(*nbUtilisateurs)){
      printf("Valeurs possibles pour le nombre d'utilisateurs : 1 / 2 / 4 / 8 / 16.\nVeuillez ressaisir.\n");
    }
  } while (!nbUtilisateursValide(*nbUtilisateurs));
}

/**
 * \fn void creeMatriceHadamard(int ** matrice, int dimMatH);
 * \brief Crée une matrice d'Hadamard dont la dimension est passée en paramètre
 * \param int ** matrice Matrice d'Hadamard
 * \param int dimMatH Dimension matrice d'Hadamard
 * \return Rien
*/
void creeMatriceHadamard(int ** matrice, int dimMatH){
  int l, c, depart, niveau;

  matrice[0][0] = 1; /* HO */

  //Suite des autres étapes : H1, H2, H3...
  niveau = 1;
  depart = 1;
  l = 0;
  c = 0;
  while((l < dimMatH) && (c < dimMatH)){
    for(l = 0; l <= niveau; l++){
      for(c = depart; c <= niveau; c++){
        matrice[l][c] = matrice[l][c-depart];
      }
    }
    for(l = depart; l <= niveau; l++){
      for(c = 0; c <= niveau; c++){
        if(c >= depart)
          matrice[l][c] = -matrice[l][c-depart];
        else
          matrice[l][c] = matrice[l-depart][c];
      }
    }
    depart = niveau+1;
    niveau = (depart*2)-1;
  }
}

/**
 * \fn void sequencesUtilisateurs(int ** matriceHadamard, int dimMatH, int * message, int longueurMessage, int ligne, int ** total)
 * \brief Stocke la séquence émise par l'utilisateur dans la matrice total
 * \param int ** matriceHadamard Matrice d'Hadamard
 * \param int dimMatH Dimension matrice d'Hadamard
 * \param int * message Tableau qui correspond au message émis par l'utilisateur
 * \param int longueurMessage Taille du tableau contenant le message
 * \param int ligne Ligne utilisée dans la matrice d'Hadamard pour coder la séquence
 * \param int ** total Matrice qui stocke le résultat
 * \return Rien
*/
void sequencesUtilisateurs(int ** matriceHadamard, int dimMatH, int * message, int longueurMessage, int ligne, int ** total){
  int i, c, j = 0;

  for (i = 0; i < longueurMessage; i++){

    for(c = 0; c < dimMatH; c++){
      if(message[i] == 1){
        total[ligne][j++] = matriceHadamard[ligne][c];
      }
      else if(message[i] == 0){
        switch(matriceHadamard[ligne][c]){
          case -1: total[ligne][j++] = 1; break;
          case 1: total[ligne][j++] = -1; break;
          default: break;
        }
      }
    }
  }
}

/**
 * \fn int * sequenceEtalee(int ** total, int ligne, int colonne)
 * \brief Retourne dans un tableau la valeur de la séquence du signal quand les utilisateurs émettent en même temps
 * \param int ** total
 * \param int ligne
 * \param int colonne
 * \return Tableau qui correspond à la séquence du signal quand les utilisateurs émettent en même temps
*/
int * sequenceEtalee(int ** total, int ligne, int colonne){
  int l, c, somme;
  int * tab = malloc(sizeof(int) * colonne);

  for(somme = 0, c = 0; c < colonne; c++,somme = 0){
    for(l = 0; l < ligne; l++){
      somme += total[l][c];
    }
    tab[c] = somme;
  }

  return tab;
}
