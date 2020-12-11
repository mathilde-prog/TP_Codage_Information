#include <stdio.h>
#include <stdlib.h>

/**
 * \file matrice_tab.h
 * \brief Tous les prototypes de fonctions relatives aux matrices et tableaux
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int ** alloue_matrice (int lignes, int colonnes);
void free_matrice(int ** matrice, int lignes);
void afficherTableau (int * tab, int taille);
void afficherMatrice(int ** matrice, int lignes, int colonnes);
