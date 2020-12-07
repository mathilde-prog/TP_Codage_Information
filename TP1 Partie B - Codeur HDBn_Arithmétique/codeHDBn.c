#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficherTab(int * tab, int nb){
  for(int i=0; i<nb; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}

//Tri bulle d'une matrice en fonction de la colonne 0
int ** triBulle_Mat_c0(int ** Mat, int lignes){
  int i, j, copy0, copy1;
  for(j=0; j < lignes; j++){
    for(i = 0; i < lignes; i++){
      if(Mat[i][0] > Mat[i+1][0]){
        copy0 = Mat[i][0];
        copy1 = Mat[i][1];

        Mat[i][0] = Mat[i+1][0];
        Mat[i][1] = Mat[i+1][1];

        Mat[i+1][0] = copy0;
        Mat[i+1][1] = copy1;
      }
    }
  }
}

void afficherMatrice(int ** matrice, int ligne, int colonne ){
  int l, c;

  for(l = 0; l < ligne; l++){
    for(c = 0; c < colonne; c++){
      printf("%2d ",matrice[l][c]);
    }
    printf("\n");
  }
}

int copie_Tab2Mat(int * tab, int ** mat, int lignes, int * nb_caracteres){
  int compteur, i, j, v;
  *nb_caracteres = 0;
  for(i=0; i<lignes; i++){
    /* Test si la valeur de tab[i] est déjà inscrite dans la matrice */
    for(v=0; (v<i) && (mat[v][0]!=tab[i]); v++);
    if(mat[v][0] == tab[i]){
      mat[i][0] = tab[i];
      mat[i][1] = 0;
    }
    else{ //Nouveau caractere
      compteur = 1;
      (*nb_caracteres)++;
      for(j=i+1; j<lignes; j++){
        if(tab[j] == tab[i]){
          compteur++;
        }
      }
      mat[i][0] = tab[i];
      mat[i][1] = compteur;
    }
  }
}

int ** alloue_matrice (int lignes, int colonnes){
  int l;
  int ** matrice = malloc(lignes*sizeof(int*));

  for(l = 0; l < lignes; l++){
    matrice[l] = malloc(colonnes*sizeof(int));
  }

  return matrice;
}

void free_matrice(int ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((int*) matrice[i]);
  }

  free(matrice);
}


int encodeurHDBn_Arithmetique(int encodeur, int longueurData, int * reset, int * data, float * f, int * p, int * n){
  int i;

  switch(encodeur){
    /* HDBn */
    case 2 : case 3 : case 4 : {
      int nb = encodeur; //Nombre de '0' a ne pas dépasser

      int dernierViol = -1;
      int dernierUn = -1;
      int nbZero = 0;

      for(i=0; i<longueurData; i++){
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

      afficherTab(reset, longueurData);
      break;
    }

    /* Arithmétique */
    case 1 : {
      int ** matOrdreAlpha_Freq = alloue_matrice(longueurData, 2);
      int nb_caracteres, ll, le, c, l;

      /* Copie de data dans un tableau 'matOrdreAlpha_Freq' */
      copie_Tab2Mat(data, matOrdreAlpha_Freq, longueurData, &nb_caracteres);
      afficherMatrice(matOrdreAlpha_Freq, longueurData, 2);
      printf("\n");
      /* Tri par ordre croissant des valeurs ascii (ordre alphabétique) */
      //triBulle_Mat_c0(matOrdreAlpha_Freq, longueurData);
      printf("Matrice triée : \n");
      afficherMatrice(matOrdreAlpha_Freq, longueurData, 2);
      printf("\n");

      //Allocation d'une matrice
      float ** matArithmetique = malloc(nb_caracteres*sizeof(float*));
      for(l = 0; l < nb_caracteres; l++){
        matArithmetique[l] = malloc(4*sizeof(float));
      }
      float intervalleRef = 1/longueurData;
      float interMin = 0, interMax;

      /* Copie de matOrdreAlpha_Freq dans une matrice 'matArithmetique' + ajout intervalles */
      for(ll=0, le=0; ll<longueurData; ll++){
        //Ajout qu'une seule fois des caractères apparaissant plusieurs fois dans la séquence à coder
        if(matOrdreAlpha_Freq[ll][1] != 0){
          for(c=0, c=0; c<2; c++){
            matArithmetique[le][c] = matOrdreAlpha_Freq[ll][c];
          }
          le++;
        }
        /* Ajout des intervalles */
        matArithmetique[le][2] = interMin;
        interMax = interMin+(matArithmetique[le][1]*intervalleRef);
        matArithmetique[le][3] = interMax;
        interMin = interMax;
      }


      afficherMatrice(matArithmetique, longueurData, 4);

      free_matrice(matOrdreAlpha_Freq,longueurData);
      free_matrice(matArithmetique,nb_caracteres);

    }

  }
}


int main(){
  int p, n, encodeur, longueurData, i;
  float f;

  /* Récupération de la méthode d'encodage */
  do{
    printf("Quelle méthode de codage voulez-vous utiliser ?\n");
    printf("0 : HDBn \n1 : Arithmétique\n");
    scanf("%d", &encodeur);
    if((encodeur!=0) && (encodeur!=1))
      printf("ERREUR : La valeur saisit doit être 0 ou 1.\n");
  }while((encodeur!=0) && (encodeur!=1));

  do{
    printf("Veuillez saisir la longueur de la séquence à coder (>1) : ");
    scanf("%d", &longueurData);
    if(longueurData<=1)
      printf("ERREUR : La longueur doit être supérieure à 1.\n");
  }while(longueurData<=1);

  int * data = malloc(sizeof(int)*longueurData);
  int * reset = malloc(sizeof(int)*longueurData);

  switch(encodeur){
    /* Code HDBn */
    case 0 : {
      do{
        printf("Avec quel HDBn voulez-vous coder ?\n");
        printf("2 : HDB2 \n 3 : HDB3\n 4 : HDB4\n");
        scanf("%d", &encodeur);
        if((encodeur<2) || (encodeur>4))
          printf("ERREUR : la valeur saisit doit être comprise entre 2 et 4.\n");
      }while((encodeur<2) || (encodeur>4));

      printf("Veuillez saisir la séquence à coder : \n");
      for(i=0; i<longueurData; i++){
        printf("Bit n°i : ");
        scanf("%d",&data[i]);
      }

      break;
    }

    /* Code Arithmétique */
    case 1 : {
      char chaine[longueurData];

      printf("Veuillez saisir la séquence à coder (entrée pour finir): \n");
      scanf(" %[^\n]", chaine);

      for(i=0; i<longueurData; i++){
          data[i] = chaine[i];
      }

      break;
    }
  }

  encodeurHDBn_Arithmetique(encodeur, longueurData, reset, data, &f, &p, &n);

  free(data);
  free(reset);

}
