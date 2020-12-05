#include <stdio.h>
#include "gold.h"

/**
 * \file tp2_gold.c
 * \brief Programme principal pour tester le codeur de Gold
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int main(){
  int i;
  gold_t codeur = initialiserGold();
  int * resultat = coderGold(codeur);

  printf("\nSéquence générée par le codeur de Gold : ");
  for(i = 0; i < codeur.codeLM1.longueurSequence; i++){
    printf("%d ",resultat[i]);
  }
  printf("\n");

  libereGold(codeur);
  free(resultat);

  return EXIT_SUCCESS; 
}
