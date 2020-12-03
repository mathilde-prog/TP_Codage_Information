#include "recepteur.h"
#include "matrice_tab.h"

/**
 * \file recepteur.c
 * \brief Fonctions relatives au récepteur 
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int ** desetalementMessage (int ** matriceHadamard, int * sequence, int nbUtilisateurs, int dimMatH, int longueurMessage)
 * \brief Procède au désetalement du message
 * \param int ** matriceHadamard Matrice d'Hadamard
 * \param int * sequence Séquence à désétaler
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \param int dimMatH Dimension Matrice d'Hadamard
 * \param int longueurMessage Longueur du message
 * \return Retourne le message après désétalement
*/
int ** desetalementMessage (int ** matriceHadamard, int * sequence, int nbUtilisateurs, int dimMatH, int longueurMessage){
  int ** message = alloue_matrice(nbUtilisateurs,longueurMessage);
  int i, k, j, c, somme;

  for(j = 0, i = 0; i < nbUtilisateurs; j = 0, i++){

    for(somme = 0, c = 0, k = 0; c < (dimMatH*longueurMessage); somme = 0, k = 0){

      do {
        somme = somme + (sequence[c]*matriceHadamard[i][k++]);
        c++;
      } while(c%dimMatH != 0);

      message[i][j++] = (somme > 0) ? 1 : 0;
    }
  }

  return message;
}

/**
 * \fn void afficherMessageRecu (int ** message, int longueurMessage, int nbUtilisateurs)
 * \brief Affiche le message reçu
 * \param int ** message Message reçu
 * \param int longueurMessage Longueur du message
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \return Rien
*/
void afficherMessageRecu (int ** message, int longueurMessage, int nbUtilisateurs){
  int l, c;

  printf("\n");
  for (l = 0; l < nbUtilisateurs; l++){
    printf("Message reçu par l'utilisateur %2d : ", l+1);
    for(c = 0; c < longueurMessage; c++){
      printf("%d ",message[l][c]);
    }
    printf("\n");
  }
}
