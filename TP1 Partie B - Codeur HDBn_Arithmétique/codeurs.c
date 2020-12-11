#include "codeurs.h"

/* Calcul du codage Arithmétique avec les intervalles */
void calculer_codage_arithmetique(float ** matArithmetique, int * data, int nb_caracteres, int longueurData, float * f){
  int i, a;
  float bornInf, bornSup, intervalle;

  for(i=0; i<longueurData; i++){ //Parcours du message à coder
    for(a=0; a<nb_caracteres; a++){ //parcours de la matrice où sont stockés les données
      if(matArithmetique[a][0] == (float)data[i]){
        if(i>0){
          intervalle = bornSup - bornInf;
          bornSup = bornInf+(matArithmetique[a][3]*intervalle);
          bornInf = bornInf+(matArithmetique[a][2]*intervalle);
        }
        else{ //Première lettre
          intervalle = matArithmetique[a][3] - matArithmetique[a][2];
          bornInf = matArithmetique[a][2];
          bornSup = matArithmetique[a][3];
        }
      }
    }
  }
  *f = bornInf;
}

/* Tri bulle d'une matrice d'entier en fonction de la colonne 0 */
void triBulle_Mat_c0(int ** Mat, int lignes){
  int i, j, echange1, echange2;

  for(i = 0; i < lignes; i++){
    for(j = lignes-1; j > i; j--){
      if(Mat[j][0] < Mat[j-1][0]){
        echange1 = Mat[j-1][0];
        echange2 = Mat[j-1][1];

        Mat[j-1][0] = Mat[j][0];
        Mat[j-1][1] = Mat[j][1];

        Mat[j][0] = echange1;
        Mat[j][1] = echange2;
      }
    }
  }
}


/* Affichage d'une matrice de float */
void afficherMatrice_float(float ** matrice, int ligne, int colonne){
  int l;

  printf(" |--------------------------------|\n");
  printf(" | Carac | Fréq |   Intervalles   |\n");
  printf(" |--------------------------------|\n");
  for(l = 0; l < ligne; l++){
    printf(" |   %c   |  %d   | %.4f ; %.4f |\n", (char)matrice[l][0], (int)matrice[l][1], matrice[l][2], matrice[l][3]);
  }
  printf(" |--------------------------------|\n");
  printf("\n");
}

/* Copie un tableau d'entiers dans un matrice d'entiers à la colonne 0 et ajoute la fréquence de la valeur dans la 2ème colonne */
void tab2Mat(int * tab, int ** mat, int lignes, int * nb_caracteres){
  int compteur, i, j, v;
  *nb_caracteres = 0;
  //Parcours la séquence
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

void encodeurHDBn_Arithmetique(int encodeur, int longueurData, int * data, float * f, int * p, int * n){
  int i;

  switch(encodeur){
    /* HDBn */
    case 2 : case 3 : case 4 : {
      int nb = encodeur; //Nombre de '0' a ne pas dépasser
      int * code = malloc(sizeof(int)*longueurData);

      int dernierViol = -1;
      int dernierUn = -1;
      int nbZero = 0;

      for(i=0; i<longueurData; i++){
        if(data[i] == 0){
          nbZero++;
          if(nbZero == nb+1){ //trop de zero à la suite
            if(dernierViol > 0){ //dernierViol positif
              code[i] = -1; //V-
              if(dernierUn > 0){ //dernierUn positif
                code[i-nb] = -1; //B-
                dernierUn = code[i-nb];
              }
            }
            else{ //dernierViol négatif
              code[i] = 1; //V+
              if(dernierUn < 0){ //dernierUn négatif
                code[i-nb] = 1; //B+
                dernierUn = code[i-nb];
              }
            }
            dernierViol = code[i];
            nbZero=0;
          }
          else{
            code[i] = 0;
          }
        }

        else{ //bite == 1 : code bipolaire
          nbZero=0;
          if(dernierUn < 0){ ///dernierUn negatif
            code[i]=1;
          }
          else{//dernierUn positif
            code[i]=-1;
          }
          dernierUn = code[i];
        }
      }
      printf(" Message codé : ");
      afficherTab(code, longueurData);

      /* Récupération des valeurs positives et négatives du signal : implémentation de p et n */
      for(i=0; i<longueurData; i++){
        switch (code[i]) {
          case 0 :  p[i] = 0;
                    n[i] = 0;
                    break;
          case 1 :  p[i] = 1;
                    n[i] = 0;
                    break;
          case -1 : p[i] = 0;
                    n[i] = 1;
                    break;
          default : printf("ERREUR : valeur code[%d] incorrecte: %d .\n", i, code[i]);
                    break;
        }
      }

      free(code);
      break;
    }

    /* Arithmétique */
    case 1 : {
      int ** matOrdreAlpha_Freq = alloue_matrice(longueurData, 2);
      int nb_caracteres, ll, le, c;
      float intervalleRef = 1/(float)longueurData;
      float interMin = 0.00, interMax;

      /* Copie de data dans une matrice 'matOrdreAlpha_Freq' de taille 2 */
      tab2Mat(data, matOrdreAlpha_Freq, longueurData, &nb_caracteres);
      /* Tri par ordre croissant des valeurs ascii (ordre alphabétique) */
      triBulle_Mat_c0(matOrdreAlpha_Freq, longueurData);

      //Allocation d'une matrice de taille 4
      float ** matArithmetique = alloue_matrice_float(nb_caracteres, 4);

      /* Copie de matOrdreAlpha_Freq dans une matrice 'matArithmetique' + ajout intervalles */
      for(ll=0, le=0; ll<longueurData; ll++){ // ll : ligne lecture, le : ligne écriture
        //Ajout qu'une seule fois des caractères apparaissant plusieurs fois dans la séquence à coder
        if(matOrdreAlpha_Freq[ll][1] != 0){
          for(c=0; c<2; c++){
            matArithmetique[le][c] = matOrdreAlpha_Freq[ll][c];
          }
          /* Ajout des intervalles */
          matArithmetique[le][2] = interMin;
          interMax = interMin+(matArithmetique[le][1]*intervalleRef);
          matArithmetique[le][3] = interMax;
          interMin = interMax;
          le++;
        }
      }
      afficherMatrice_float(matArithmetique, nb_caracteres, 4);

      calculer_codage_arithmetique(matArithmetique, data, nb_caracteres, longueurData, f);

      free_matrice(matOrdreAlpha_Freq,longueurData);
      free_matrice_float(matArithmetique,nb_caracteres);
    }
  }

}

/* Affichage d'un tableau d'entier */
void afficherTab(int * tab, int nb){
  for(int i=0; i<nb; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}


/* Allocation d'une matrice d'entiers */
int ** alloue_matrice (int lignes, int colonnes){
  int l;
  int ** matrice = malloc(lignes*sizeof(int*));

  for(l = 0; l < lignes; l++){
    matrice[l] = malloc(colonnes*sizeof(int));
  }

  return matrice;
}

/* Allocation d'une matrice d'entiers */
float ** alloue_matrice_float (int lignes, int colonnes){
  int l;
  float ** matrice = malloc(lignes*sizeof(float*));

  for(l = 0; l < lignes; l++){
    matrice[l] = malloc(colonnes*sizeof(float));
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

void free_matrice_float(float ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((float*) matrice[i]);
  }

  free(matrice);
}
