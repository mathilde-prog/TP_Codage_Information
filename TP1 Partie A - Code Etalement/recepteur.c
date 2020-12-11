#include "recepteur.h"
#include "matrice_tab.h"
#include "emetteur.h"
/**
 * \file recepteur.c
 * \brief Fonctions relatives au récepteur
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int ** desetalement(int nbUtilisateurs, int * sequenceSignal, int longueurMessages)
 * \brief Appelle la fonction nécessaire pour créer la matrice de Hadamard et ainsi procèder au désetalement du message
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \param int * sequenceSignal Séquence du signal à désétaler
 * \param int longueurMessage Longueur des messages
 * \return Retourne une matrice contenant les messages reçus (après désétalement)
*/
int ** desetalement(int nbUtilisateurs, int * sequenceSignal, int longueurMessages){
  int i, k, j, c, somme;

  /* Initialisation de la dimension de la matrice de Hadamard
  *  Dimension 8 si le nombre d'utilisateurs vaut 1, 2, 4 ou 8
  *  Dimension 16 si nombre de l'utilisateurs vaut 16.
  */
  int dimensionHadamard = (nbUtilisateurs > 8) ? 16 : 8;

  // Création de la matrice de Hadamard qui sera essentielle pour le désétalement
  int ** matriceHadamard = creeMatriceHadamard(dimensionHadamard);

  // La matrice messages est crée pour contenir les messages reçus (après désétalement).
  int ** messages = alloue_matrice(nbUtilisateurs,longueurMessages);

  // Opération de désétalement
  for(i = 0, j = 0; i < nbUtilisateurs; j = 0, i++){

    for(somme = 0, c = 0, k = 0; c < (dimensionHadamard*longueurMessages); somme = 0, k = 0){

      do {
        somme = somme + (sequenceSignal[c]*matriceHadamard[i][k++]);
        c++;
      } while(c%dimensionHadamard != 0);

      messages[i][j++] = (somme > 0) ? 1 : 0;
    }
  }

  free_matrice(matriceHadamard,dimensionHadamard);
  return messages;
}

/**
 * \fn void afficherMessagesRecus(int nbUtilisateurs, int ** messagesRecus, int longueurMessages)
 * \brief Affiche le message reçu
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \param int messagesRecus Matrice contenant les messages reçus (après désétalement)
 * \param int longueurMessages Longueur des messages
 * \return Rien
*/
void afficherMessagesRecus(int nbUtilisateurs, int ** messagesRecus, int longueurMessages){
  int l, c;

  printf("\n");
  for (l = 0; l < nbUtilisateurs; l++){
    printf("Message reçu par l'utilisateur %2d : ", l+1);
    for(c = 0; c < longueurMessages; c++){
      printf("%d ",messagesRecus[l][c]);
    }
    printf("\n");
  }
}
