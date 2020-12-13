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


void decodeurArithmetique(int longueurData, int nb_caracteres, float f, float ** matDecodeur, int * data){
  int i, m, trouver;
  double dividende, diviseur;

  printf("\n Matrice nécessaire au décodage : \n");
  afficherMatrice_float(matDecodeur, nb_caracteres, 4);

  printf("\n Valeur de f avant décodage : %.10f\n", f);

  /* Décodage de la valeur de f tant que celle-ci est supérieur à 0 et que toutes les lettres ne sont pas trouvés */
  for(m=0; m<longueurData; m++){
    trouver=0;
    printf("\n Recherche du caractère %d :\n", m);
    //Recherche des bornes qui encadrent la valeur de f
    for(i=0; (i<nb_caracteres) && (trouver != 1); i++){
      if((matDecodeur[i][2] <= f) && (f < matDecodeur[i][3])){ //valeur codé (f) comprise dans entre les bornes de valeurs matDecodeur[i][2] et matDecodeur[i][3]
        printf("    f est compris entre : %.4f et %.4f\n", matDecodeur[i][2], matDecodeur[i][3]);
        data[m] = (int)matDecodeur[i][0];
        dividende = (double)f-(double)matDecodeur[i][2];
        printf("bornInf = %.10f \n", (double)matDecodeur[i][2]);
        printf("dividende = %.10lf \n", dividende);
        float x = (float)1/(float)10;
        printf("1/10 = %f\n", x);
        diviseur = (double)matDecodeur[i][1]/longueurData;
        printf("diviseur = %.10lf\n", diviseur);
        printf("    => donc le caractère n°%d du message est : %c\n", m, (char)data[m]);
        f = dividende/diviseur;
        trouver=1;
      }
    }
    printf("\n\n Nouvelle valeur de f : %.10f\n", f);
  }

}
