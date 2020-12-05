#include <stdio.h>
#include <stdlib.h>
#include "long_max.h"

/**
 * \file gold.h
 * \brief Structure et prototypes des fonctions permettant la mise en oeuvre d'un codeur de Gold
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
  * \struct gold_t
  * \brief Structure pour la mise en oeuvre d'un codeur de Gold
*/
typedef struct {
  codeLM_t codeLM1; /**< Code à Longueur Maximale 1 */
  codeLM_t codeLM2; /**< Code à Longueur Maximale 2 */
} gold_t;

gold_t initialiserGold();
int * coderGold(gold_t codeurGold);
void libereGold(gold_t codeurGold);
