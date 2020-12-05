#include <stdio.h>
#include <stdlib.h>
#include "long_max.h"

/**
 * \file tp2_long_max.c
 * \brief Programme principal pour tester le codeur à Longueur Maximale
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int main(){
    int i;
    codeLM_t codeur = initialiserLM();
    int * resultat = coderLM(codeur);

		printf("\nSéquence générée par le codeur à Longueur Maximale = ");
		for(i = 0; i < codeur.longueurSequence; i++){
			printf("%d ",resultat[i]);
		}
		printf("\n");

		libereLM(codeur);
		free(resultat);

    return EXIT_SUCCESS;
}
