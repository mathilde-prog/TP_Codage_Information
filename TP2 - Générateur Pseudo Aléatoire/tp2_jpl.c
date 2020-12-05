#include "jpl.h"

/**
 * \file tp2_jpl.c
 * \brief Programme principal pour tester le codeur JPL
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

int main(){
  jpl_t codeurJPL = initialiserJPL();
	int * resultat =	coderJPL(codeurJPL);
  int i;

	printf("\nSéquence générée par le codeur JPL : ");
	for(i = 0; i < codeurJPL.longueurSequence; i++){
		printf("%i ",resultat[i]);
	}
	printf("\n");

	libereJPL(codeurJPL);
	free(resultat);

  return EXIT_SUCCESS; 
}
