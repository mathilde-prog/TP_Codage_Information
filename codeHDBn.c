#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherHDBn(int tab[23], int nb){
  for(int i=0; i<23; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}

int encodeurHDBn_Arithmetique(int reset[23], int data[23], int p, int n, int nb){
  int dernierViol = -1;
  int dernierUn = -1;
  int nbZero = 0;
  int i;

  for(i=0; i<23; i++){
    if(data[i] == 0){
      nbZero++;
      if(nbZero == nb+1){ //trop de zero à la suite
        if(dernierViol > 0){ //dernierViol positif
          reset[i] = -1; //V-
          if(dernierUn > 0){ //dernierUn positif
            reset[i-nb] = -1; //B-
            dernierUn = reset[i-nb];
          }
        }
        else{ //dernierViol négatif
          reset[i] = 1; //V+
          if(dernierUn < 0){ //dernierUn négatif
            reset[i-nb] = 1; //B+
            dernierUn = reset[i-nb];
          }
        }
        dernierViol = reset[i];
        nbZero=0;
      }
      else{
        reset[i] = 0;
      }
    }

    else{ //bite == 1 : code bipolaire
      nbZero=0;
      if(dernierUn < 0){ ///dernierUn negatif
        reset[i]=1;
      }
      else{//dernierUn positif
        reset[i]=-1;
      }
      dernierUn = reset[i];
    }
  }

  afficherHDBn(reset, nb);
}

int main(){
  int p, n, nb;
  printf("Veuillez saisir la valeur de n : ");
  scanf("%d", &nb);

  //int * data = malloc(sizeof(int)*23)
  int data[] = {1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0};
  int reset[23];
  encodeurHDBn_Arithmetique(reset, data, p, n, nb);

  float f;
}
