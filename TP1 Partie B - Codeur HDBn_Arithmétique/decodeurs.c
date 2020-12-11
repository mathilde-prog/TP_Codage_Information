#include "decodeurs.h"

void decodeurHDBn(int valHDBn, int longueurData, int * p, int * n, int * data){
  int i, nb;
  int dernierUn = 5;
  int * signal = malloc(sizeof(int)*longueurData);

  /* Récupération du signal codé */
  for(i=0; i<longueurData; i++){
    signal[i] = p[i]-(1*n[i]);
  }
  printf("\n Signal : ");
  afficherTab(signal, longueurData);

  /* Récupération de la séquence d'origine*/
  for(i=0; i<longueurData; i++){ //Parcours du signal
    //Valeur de signal = 1 ou -1
    if(signal[i] != 0){
      if(dernierUn != 5){ //Premier 1 déjà récupéré
        if(signal[i] == dernierUn){ //Problème d'alternance des 1 dans le signal
          for(nb=i-valHDBn; nb<=i; nb++){
            data[nb] = 0;
          }
        }
        else{ //Alternance des 1 : ok
          data[i] = 1;
        }
        dernierUn = signal[i];
      }
      else{ //Récupération du premier 1 du signal
        dernierUn = signal[i];
        data[i] = 1;
      }
    }
    //Valeur de signal = 0
    else{
      data[i] = 0;
    }
  }
}
