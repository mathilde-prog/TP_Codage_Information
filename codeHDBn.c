#include <stdio.h>
#include <stdlib.h>

int encodeurHDBn_Arithmetique(int reset, int data, int p, int n){
  int dernierViol = -1;
  int dernierUn = -1;
  int nbZero = 0;

  for(int i=0; !data; i++){
    if(data[i]==0){
      nbZero++;
      if(nbZero > n){ //trop de zero à la suite
        if(dernierViol > 0){ //dernierViol positif
          if(dernierUn > 0){ //dernierUn positif
            reset[i]=-1;
          }
          else{ //dernierUn negatif
            reset[i]=1;
          }
          dernierUn*=-1;
        }
        else{ //dernierViol négatif

        }
      }
    }
    else{ //bite == 1 : code bipolaire
      if(dernierUn < 0){ ///dernierUn negatif
        reset[i]=1;
      }
      else{//dernierUn positif
        reset[i]=-1;
      }
      dernierUn*=-1;
    }
  }
}

int main(){
  int p, n, nb;
  print("Veuillez saisir la valeur de n : ");
  scanf("%d\n", &nb);

  //int * data = malloc(sizeof(int)*23)
  int data = [1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0];
  int reset[data.length];
  encodeurHDBn_Arithmetique(reset, data, p, n);

  float f;
}
