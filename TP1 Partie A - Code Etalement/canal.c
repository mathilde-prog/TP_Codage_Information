#include "canal.h"

/**
 * \file canal.c
 * \brief Fonction relative au canal
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int * canalIdeal(int * sequence)
 * \brief Représente un canal idéal
 * \param int * sequence Séquence qui traverse le canal
 * \return La séquence envoyée dans le canal car c'est un canal IDEAL
*/
int * canalIdeal(int * sequence){
  printf("\nEnvoi de la séquence dans le canal idéal\n");
  return sequence;
}
