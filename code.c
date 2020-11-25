#include <stdio.h>
#include <stdlib.h>

// Alloue + initialise à zéro
int ** alloue_init_matrice (int lignes, int colonnes){
  int l, c;
  int ** matrice = malloc(lignes*sizeof(int*));

  for(l = 0; l < lignes; l++){
    matrice[l] = malloc(colonnes*sizeof(int));
  }

  for(l = 0; l < lignes; l++){
    for(c = 0; c < colonnes; c++){
      matrice[l][c] = 0;
    }
  }

  return matrice;
}

void free_matrice(int ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((int*) matrice[i]);
  }
}

void afficherMatrice(int ** matrice, int dimension){
  int l, c;

  for(l = 0; l < dimension; l++){
    for(c = 0; c < dimension; c++){
      printf("%2d ",matrice[l][c]);
    }
    printf("\n");
  }
}

int nbUtilisateursValide(int nb){
  return ((nb == 1) || (nb == 2) || (nb == 4) || (nb == 8) || (nb == 16));
}

void saisieNbUtilisateurs(int * nbUtilisateurs){
  do {
    printf("\nSaisir le nombre d'utilisateurs : ");
    scanf("%d",nbUtilisateurs);

    if(!nbUtilisateursValide(*nbUtilisateurs)){
      printf("Valeurs possibles pour le nombre d'utilisateurs : 1 / 2 / 4 / 8 / 16.\nVeuillez ressaisir.\n");
    }
  } while (!nbUtilisateursValide(*nbUtilisateurs));
}

int initMatriceHadamard(int ** matrice, int dimension){
  int l, c, depart, niveau;


  matrice[0][0] = 1; //HO

  //Suite des autres étapes : H1, H2, H3...
  niveau = 1;
  depart = 1;
  l = 0;
  c = 0;
  while((l < dimension) && (c < dimension)){
    for(l=0; l <= niveau; l++){
      for(c=depart; c <= niveau; c++){
        matrice[l][c] = matrice[l][c-depart];
      }
    }
    for(l=depart; l <= niveau; l++){
      for(c=0; c <= niveau; c++){
        if(c>=depart)
          matrice[l][c] = -matrice[l][c-depart];
        else
          matrice[l][c] = matrice[l-depart][c];
      }
    }
    depart = niveau+1;
    niveau = (depart*2)-1;
  }
}

int main(){
    int nbUtilisateurs;
    int ** matrice = alloue_init_matrice(8,8);

    saisieNbUtilisateurs(&nbUtilisateurs);

    printf("Matrice Hadamard : \n"); 
    initMatriceHadamard(matrice,8);
    afficherMatrice(matrice,8);

    free_matrice(matrice,8);
}
