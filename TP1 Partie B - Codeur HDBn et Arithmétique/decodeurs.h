#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codeurs.h"

/**
 * \file decodeurs.h
 * \brief Tous les prototypes de fonctions relatives aux décodeurs HDBn et Arithmétique
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

void decodeurHDBn(int valHDBn, int longueurData, int * p, int * n, int * data);
void decodeurArithmetique(int longueurData, int nb_caracteres, float f, float ** matDecodeur, int * data);
