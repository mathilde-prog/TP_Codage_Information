#include <stdio.h>
#include <stdlib.h>
#include "long_max.h"

/**
 * \file jpl.h
 * \brief Structure et prototypes des fonctions permettant la mise en oeuvre d'un codeur JPL
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
  * \struct jpl_t
  * \brief Structure pour la mise en oeuvre d'un codeur JPL
*/
typedef struct {
  codeLM_t * codesLM;     /**< Codes à longueur maximale */
  int nbCodesLM;        /**< Nombre de codes à longueur maximale */
  int longueurSequence; /**< Longueur de la séquence générée */
} jpl_t;

int pgcd(int a, int b);
int estPremier(int a, int b);
int tousLesNbEtagesSontPremiersEntreEux(jpl_t jpl, int nbCodeLM, int entier);
jpl_t initialiserJPL();
int * coderJPL(jpl_t codeurJPL);
void libereJPL(jpl_t codeurJPL);
