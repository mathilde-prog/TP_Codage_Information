#include <stdio.h>
#include <stdlib.h>

/**
 * \file recepteur.h
 * \brief Tous les prototypes de fonctions relatives au récepteur 
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int ** desetalementMessage (int ** matriceHadamard, int * sequence, int nbUtilisateurs, int dimMat, int longueurMessage);
void afficherMessageRecu (int ** message, int longueurMessage, int nbUtilisateurs);
