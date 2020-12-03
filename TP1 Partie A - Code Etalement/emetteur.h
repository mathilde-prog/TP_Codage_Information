#include <stdio.h>
#include <stdlib.h>

/**
 * \file emetteur.h
 * \brief Tous les prototypes de fonctions relatives à l'émetteur
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int nbUtilisateursValide(int nb);
void choixNbUtilisateurs(int * nbUtilisateurs);
void creeMatriceHadamard(int ** matriceHadamard, int dimension);
void sequencesUtilisateurs(int ** matriceHadamard, int dimension, int * emission, int taille, int ligne, int ** total);
int * sequenceEtalee (int ** total, int ligne, int colonne);
