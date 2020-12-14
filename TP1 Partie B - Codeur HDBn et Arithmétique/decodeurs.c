#include "decodeurs.h"

/**
 * \file decodeurs.c
 * \brief Fonctions relatives aux décodeurs HDBn et Arithmétique
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn void decodeurHDBn(int valHDBn, int longueurData, int * p, int * n, int * data)
 * \brief Fonction de décodage HDBn
 * \param int valHDBn Valeur HDBn
 * \param int longueurData Longueur des données
 * \param int * p Tableau d'entiers pour contenir les valeurs positives
 * \param int * n Tableaux d'entiers pour contenir les valeurs négatives
 * \param int * data Tableau de données d'entiers
*/
void decodeurHDBn(int valHDBn, int longueurData, int * p, int * n, int * data){
  int i, nb;
  int dernierUn = 5;
  int * signal = NULL; //Tableau de int qui contiendra le signal à décoder

  if((signal = malloc(sizeof(int)*longueurData)) == NULL){
    fprintf(stderr,"decodeurHDBn: débordement mémoire lors de la création du tableau signal\n");
    exit(1);
  }

  /* Récupération du signal codé */
  for(i=0; i<longueurData; i++){
    signal[i] = p[i]-(1*n[i]);
  }
  //Affichage du signal
  printf("\n Signal : ");
  afficherTab(signal, longueurData);

  /* Décodage du signal */
  //Parcours du signal
  for(i=0; i<longueurData; i++){
    //Valeur de signal = 1 ou -1
    if(signal[i] != 0){
      //Ce n'est pas le premier 1
      if(dernierUn != 5){
        //Problème d'alternance des 1 dans le signal
        if(signal[i] == dernierUn){
          for(nb=i-valHDBn; nb<=i; nb++){
            data[nb] = 0;
          }
        }
        //Alternance des 1 : ok
        else{
          data[i] = 1;
        }
        dernierUn = signal[i]; //Actualisation du dernierUn
      }
      //Récupération du premier 1 du signal
      else{
        dernierUn = signal[i];
        data[i] = 1;
      }
    }
    //Valeur de signal = 0
    else{
      data[i] = 0;
    }
  }
}

/**
 * \fn void decodeurArithmetique(int longueurData, int nb_caracteres, float f, float ** matDecodeur, int * data)
 * \brief Fonction de décodage arithmétique
 * \param int longueurData Longueur des données
 * \param int nb_caracteres Nombre de caractères
 * \param float f Valeur arithmétique 
 * \param float ** matDecodeur Matrice
 * \param int * data Tableau de données d'entiers
*/
void decodeurArithmetique(int longueurData, int nb_caracteres, float f, float ** matDecodeur, int * data){
  int i, m, trouver;
  double dividende, diviseur;

  //Affichage de la matrice nécessaire au décodage
  printf("\n Matrice nécessaire au décodage : \n");
  afficherMatrice_float(matDecodeur, nb_caracteres, 4);

  printf("\n Valeur de f avant décodage : %.10f\n", f);

  /* Décodage de la valeur de f tantque toutes les lettres ne sont pas trouvées */
  for(m=0; m<longueurData; m++){
    trouver=0; //booléen pour savoir si la lettre correspondant à f est trouvée
    printf("\n Recherche du caractère %d :\n", m);
    /* Recherche des bornes qui encadrent la valeur de f */
    for(i=0; (i<nb_caracteres) && (trouver != 1); i++){
      if((matDecodeur[i][2] <= f) && (f < matDecodeur[i][3])){ //valeur codée (f) comprise dans entre les bornes de valeurs matDecodeur[i][2] et matDecodeur[i][3]
        printf("    f est compris entre : %.4f et %.4f\n", matDecodeur[i][2], matDecodeur[i][3]);
        data[m] = (int)matDecodeur[i][0];
        printf("    => donc le caractère n°%d du message est : '%c'\n", m, (char)data[m]);
        dividende = (double)f-(double)matDecodeur[i][2];
        diviseur = (double)matDecodeur[i][1]/longueurData;
        f = dividende/diviseur;
        trouver=1;
      }
    }
    printf("\n\n Nouvelle valeur de f : %.10f\n", f);
  }
}
