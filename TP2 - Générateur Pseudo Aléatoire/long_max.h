#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * \file long_max.h
 * \brief Structures et prototypes des fonctions permettant la génération d'un codeur à Longueur Maximale
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
  * \struct registres_t
  * \brief Structure pour les registres
*/
typedef struct {
  int nbEtages;  /**< Nombre d'étages */
  int * vecteur; /**< Vecteur pour initialiser les registres */
} registres_t;

/**
  * \struct polynome_t
  * \brief Structure pour le polynôme de génération
*/
typedef struct  {
  int taille; /**< Taille du polynôme */
  int * tab;  /**< Tableau qui contient le polynôme */
} polynome_t;

/**
  * \struct codeLM_t
  * \brief Structure pour générer un code à longueur maximale
*/
typedef struct {
  int longueurSequence; /**< Longueur de la séquence à générer */
  polynome_t polynome;  /**< Polynôme de génération */
  registres_t registres;  /**< Registres */
} codeLM_t;

codeLM_t initialiserLM();
void libereLM(codeLM_t codeur);
int * coderLM(codeLM_t codeur);
