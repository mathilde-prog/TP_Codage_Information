#include "gold.h"

/**
 * \file gold.c
 * \brief Génération d'un codeur de Gold
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn gold_t initialiserGold();
 * \brief Initialise une structure du type gold_t (longueur de la séquence à générer, polynôme et registres pour les 2 codes LM)
 * \return Structure du type gold_t initialisée
*/
gold_t initialiserGold(){
  gold_t codeurGold;
  int i;

  /*
    * Initialisation de la longueur de la séquence à générer
    * Remarque : La longueur de la séquence est identique pour les deux codes LM.
  */
  printf("\nSaisir la longueur de la séquence à générer : ");
  scanf("%d",&codeurGold.codeLM1.longueurSequence);
  codeurGold.codeLM2.longueurSequence = codeurGold.codeLM1.longueurSequence;

  /*
    * Initialisation des registres
    * Remarque : Les deux codes LM ont le même nombre d'étages pour les registres.
  */
  printf("\n[REGISTRES]\n");
  printf("Saisir le nombre d'étages pour les registres : ");
  scanf("%d",&codeurGold.codeLM1.registres.nbEtages);
  codeurGold.codeLM2.registres.nbEtages = codeurGold.codeLM1.registres.nbEtages;

  if((codeurGold.codeLM1.registres.vecteur = malloc(sizeof(int)*codeurGold.codeLM1.registres.nbEtages))== NULL){
    fprintf(stderr,"initialiserGold: débordement mémoire lors de la création du vecteur pour les registres du code LM 1\n");
    exit(1);
  }

  if((codeurGold.codeLM2.registres.vecteur = malloc(sizeof(int)*codeurGold.codeLM2.registres.nbEtages)) == NULL){
    fprintf(stderr,"initialiserGold: débordement mémoire lors de la création du vecteur pour les registres du code LM 2\n");
    exit(1);
  }

  /*
    * Code LM 1
  */

  /*
    * Saisie du vecteur des registres
  */
  printf("\n*** Code Longueur Maximale 1 ***\n");
  printf("\nSaisir les registres du code LM 1 :\n");
  for(i = 0; i < codeurGold.codeLM1.registres.nbEtages; i++){
    printf("\tRegistre %d : ", i+1);
    scanf("%d",&codeurGold.codeLM1.registres.vecteur[i]);
  }

  /*
    * Initialisation du polynôme de génération
  */
  printf("\nSaisir la longueur du polynôme de génération du code LM 1: ");
  scanf("%d",&codeurGold.codeLM1.polynome.taille);

  if((codeurGold.codeLM1.polynome.tab = malloc(sizeof(int)*codeurGold.codeLM1.polynome.taille)) == NULL){
    fprintf(stderr,"initialiserGold: débordement mémoire lors de la création du polynome du code LM 1\n");
    exit(1);
  }

  printf("\nSaisir le polynôme de génération du code LM 1 : \n");
  for(i = 0; i < codeurGold.codeLM1.polynome.taille; i++){
    printf("\tIndice %d : ", i);
    scanf("%d",&codeurGold.codeLM1.polynome.tab[i]);
  }

  /*
    * Code LM 2
  */

  printf("\n*** Code Longueur Maximale 2 ***\n");

  /*
    * Saisie du vecteur des registres
  */
  printf("\nSaisir le registres du code LM 2 :\n");
  for(i = 0; i < codeurGold.codeLM2.registres.nbEtages; i++){
    printf("\tRegistre %d : ", i+1);
    scanf("%d",&codeurGold.codeLM2.registres.vecteur[i]);
  }

  /*
    * Initialisation du polynôme de génération
  */
  printf("\nSaisir la longueur du polynôme de génération du code LM 2 : ");
  scanf("%d",&codeurGold.codeLM2.polynome.taille);

  if((codeurGold.codeLM2.polynome.tab = malloc(sizeof(int)*codeurGold.codeLM2.polynome.taille)) == NULL){
    fprintf(stderr,"initialiserGold: débordement mémoire lors de la création du polynome du code LM 2\n");
    exit(1);
  }

  printf("\nSaisir le polynôme de génération du code LM 2 : \n");
  for(i = 0; i < codeurGold.codeLM2.polynome.taille; i++){
    printf("\tIndice %d : ", i);
    scanf("%d",&codeurGold.codeLM2.polynome.tab[i]);
  }

  return codeurGold;
}

/**
 * \fn int * coderGold (gold_t codeurGold);
 * \brief Codeur de Gold
 * \param gold_t codeurGold Structure contenant tous les paramètres nécessaires pour générer la séquence codée
 * \return Retourne la séquence codée générée par le codeur à Longueur Maximale
*/
int * coderGold (gold_t codeurGold){
  int i;

  // Tableau pour la séquence générée par le codeur de Gold
  int * sequenceGeneree;
  if((sequenceGeneree = malloc(sizeof(int) * codeurGold.codeLM1.longueurSequence)) == NULL){
    fprintf(stderr,"coderGold: débordement mémoire lors de la création du tableau pour la séquence générée\n");
    exit(1);
  }

  // Tableaux pour récupérer les séquences générées par les codes LM 1 et LM 2
  int * sg_codeLM1 = coderLM(codeurGold.codeLM1);
  int * sg_codeLM2 = coderLM(codeurGold.codeLM2);

  // L'opération logique XOR est effectuée sur les deux séquences générées par les codes LM
  for(i = 0; i < codeurGold.codeLM1.longueurSequence; i++){
    sequenceGeneree[i] = sg_codeLM1[i] ^ sg_codeLM2[i];
  }

  free(sg_codeLM1);
  free(sg_codeLM2);

  // La séquence générée par le codeur de Gold (de longueur souhaitée par l'utilisateur) est retournée.
  return sequenceGeneree;
}

/**
 * \fn void libereGold(gold_t codeurGold)
 * \brief Libère l'espace alloué dynamiquement pour l'objet de type gold_t passé en paramètre
 * \param gold_t codeurGold
 * \return Rien
*/
void libereGold(gold_t codeurGold){
  libereLM(codeurGold.codeLM1);
  libereLM(codeurGold.codeLM2);
}
