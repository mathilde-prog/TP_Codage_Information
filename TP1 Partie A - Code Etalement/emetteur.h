#include <stdio.h>
#include <stdlib.h>

#include "matrice_tab.h"
/**
 * \file emetteur.h
 * \brief Tous les prototypes de fonctions relatives à l'émetteur
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int nbUtilisateursValide(int nb);
int choixNbUtilisateurs();
int saisieLongueurMessages();
int ** creeMatriceHadamard(int dimension);
void afficherSequencesCodees(int ** sequencesCodees, int lignes, int colonnes);
int ** codageSequences (int nbUtilisateurs, int ** matriceHadamard, int dimensionHadamard, int ** messages, int longueurMessages, int verbose);
int * etalement(int nbUtilisateurs, int dimensionHadamard, int longueurMessages, int ** sequencesCodees, int verbose);
int * emetteur (int nbUtilisateurs, int longueurMessages, int verbose);
