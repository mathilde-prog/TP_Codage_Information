#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "emetteur.h"
#include "recepteur.h"
#include "matrice_tab.h"
#include "canal.h"

static struct option longopts[] = {
  {"verbose", no_argument, NULL, (int)'v'},
  {0, 0, 0, 0}
};

int main(int argc, char * argv[], char * env[]){
    char c;
    int verbose = 0, longueurMessages, nbUtilisateurs, i, nbit, numSequence = 0;

    // Option verbose : affiche tous les messages de trace si elle est positionnée.
    while ((c = getopt_long(argc,argv,"v",longopts,NULL)) != -1){
      if(c == 'v'){
        verbose = 1;
      }
    }

    choixNbUtilisateurs(&nbUtilisateurs);

    int dimMatH = (nbUtilisateurs > 8) ? 16 : 8;
    int ** matriceHadamard = alloue_matrice(dimMatH,dimMatH);

    creeMatriceHadamard(matriceHadamard,dimMatH);

    if(verbose){
      printf("\n Matrice Hadamard : \n");
      afficherMatrice(matriceHadamard,dimMatH,dimMatH);
    }

    do {
      printf("\nSaisir la longueur des messages : ");
      scanf("%d",&longueurMessages);
      if(longueurMessages <= 0){
        printf("La longueur des messages ne peut être négative ou nulle. Veuillez ressaisir.\n");
      }
    } while(longueurMessages <= 0);

    int ** resultat = alloue_matrice(dimMatH,dimMatH*longueurMessages);
    int * sequence = malloc(sizeof(int)* (dimMatH*longueurMessages));
    int * messages = malloc(sizeof(int)*longueurMessages);

    for(i = 0; i < nbUtilisateurs; i++){
      printf("\n[Saisie séquence émise par l'utilisateur %d]\n",i+1);

      for(nbit = 0; nbit < longueurMessages; nbit++){
        printf("Saisir le bit %d : ",nbit);
        scanf("%d",&messages[nbit]);
      }

      sequencesUtilisateurs(matriceHadamard,dimMatH,messages,longueurMessages,numSequence++,resultat);
    }

    if(verbose){
      printf("\n");
      afficherMatriceResultat(resultat,dimMatH,dimMatH*longueurMessages);
      printf("\n");
    }

    sequence = sequenceEtalee(resultat,dimMatH,dimMatH*longueurMessages);
    if(verbose){
      printf("Séquence après étalement : ");
      afficherTableau(sequence,dimMatH*longueurMessages);
    }

    printf("\nEnvoi de la séquence étalée dans le canal idéal\n");
    canalIdeal(sequence);

    int ** res = desetalementMessage(matriceHadamard,sequence,nbUtilisateurs,dimMatH,longueurMessages);
    afficherMessageRecu(res,longueurMessages,nbUtilisateurs);

    free_matrice(matriceHadamard,dimMatH);
    free_matrice(resultat,dimMatH);
    free(sequence);
    free(messages);

    return EXIT_SUCCESS;
}
