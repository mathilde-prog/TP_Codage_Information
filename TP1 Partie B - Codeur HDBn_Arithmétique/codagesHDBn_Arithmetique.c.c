#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* Affichage d'un tableau d'entier */
void afficherTab(int * tab, int nb){
  for(int i=0; i<nb; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
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
int tab2Mat(int * tab, int ** mat, int lignes, int * nb_caracteres){
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


int main(){
  int valHDBn, longueurData, i, code, encodeur, decodeur, rep;
  float f;

  printf("\n******** ENCODEURS / DECODEURS : HDBn & Arithmétique ********\n \n");
  do{
    printf("    0 : Encoder \n    1 : Décoder\n");
    printf(" Que souhaitez-vous faire ? ");
    scanf("%d", &code);
    if((code!=0) && (code!=1))
      printf("ERREUR : La valeur saisit doit être 0 ou 1.\n");
  }while((code!=0) && (code!=1));

  do{
    printf("\n Veuillez saisir la longueur de la séquence (>1) : ");
    scanf("%d", &longueurData);
    if(longueurData<=1)
      printf(" ERREUR : La longueur doit être supérieure à 1.\n");
  }while(longueurData<=1);

  int * data = malloc(sizeof(int)*longueurData);
  int * p = malloc(sizeof(int)*longueurData);
  int * n = malloc(sizeof(int)*longueurData);

  /* ************************* ENCODAGE ******************************** */
  switch(code){
    case 0 : {
      printf("\n\n******** ENCODEURS HDBn & Arithmétique ********\n");

      /* Récupération de la méthode d'encodage */
      do{
        printf("\n Méthodes de codage proposées :\n");
        printf("    0 : HDBn \n    1 : Arithmétique\n");
        printf(" Quelle méthode de codage voulez-vous utiliser ? ");
        scanf("%d", &encodeur);
        if((encodeur!=0) && (encodeur!=1))
          printf("ERREUR : La valeur saisit doit être 0 ou 1.\n");
      }while((encodeur!=0) && (encodeur!=1));

      switch(encodeur){
        /* ************************* ENCODAGE HDBn ******************************** */
        case 0 : {
          printf("\n\n ******** ENCODEUR HDBn ********\n");

          do{
            printf("\n HDBn disponibles :\n");
            printf("    2 : HDB2 \n    3 : HDB3\n    4 : HDB4\n");
            printf(" Avec quel HDBn voulez-vous coder ? ");
            scanf("%d", &encodeur);
            if((encodeur<2) || (encodeur>4))
              printf(" ERREUR : la valeur saisit doit être comprise entre 2 et 4.\n");
          }while((encodeur<2) || (encodeur>4));

          printf("\n Veuillez saisir la séquence à coder : \n");
          for(i=0; i<longueurData; i++){
            printf(" Bit n°%d : ", i);
            scanf("%d",&data[i]);
          }
          printf("\n");

          break;
        }

        /* ************************* ENCODAGE Arithmétique ******************************** */
        case 1 : {
          printf("\n\n ******** ENCODEUR Arithmétique ********\n");
          char chaine[longueurData];

          printf("\n Veuillez saisir la séquence à coder (entrée pour finir): ");
          scanf(" %[^\n]", chaine);
          printf("\n");

          for(i=0; i<longueurData; i++){
              data[i] = chaine[i];
          }

          break;
        }
        default : printf("ERREUR : encodeur = %d\n", encodeur);
                  break;
      }

      encodeurHDBn_Arithmetique(encodeur, longueurData, data, &f, p, n);
      if(encodeur == 1) //Code Arithmétique
        printf("\n Message codé : %.10f\n", f);
      else{ //code HDBn
        printf(" P : ");
        afficherTab(p, longueurData);
        printf(" N : ");
        afficherTab(n, longueurData);
      }

      /* Demande si l'utilisateur veut décoder le message qu'il vient de coder */
      do{
        printf("\n Souhaitez-vous maintenant décoder ce message ?\n");
        printf("    0 : Oui \n    1 : Non\n");
        printf(" Votre choix : ");
        scanf("%d", &rep);
        if((rep!=0) && (rep!=1))
          printf("ERREUR : La valeur saisit doit être 0 ou 1.\n");
      }while((rep!=0) && (rep!=1));


      if(rep == 0){
        if(encodeur != 1){ //HDBn
          decodeurHDBn(encodeur, longueurData, p, n, data);
          printf("\n Message décodé : ");
          afficherTab(data, longueurData);
        }
        else{ //Arithmétique
          printf("\n Message décodé : ");
        }
      }

      free(p);
      free(n);
      free(data);

      break;
    }

    /* ************************* DECODAGE ******************************** */
    case 1 : {

        printf("\n\n ******** DECODEURS HDBn & Arithmétique ********\n");

      do{
        printf("\n Décodeurs disponibles :\n");
        printf("    0 : HDBn \n    1 : Arithmétique\n");
        printf(" Quel décodeur voulez-vous utiliser ? ");
        scanf("%d", &decodeur);
        if((decodeur!=0) && (decodeur!=1))
          printf("ERREUR : La valeur saisit doit être 0 ou 1.\n");
      }while((decodeur!=0) && (decodeur!=1));

      switch(decodeur){
        /* ************************* DECODAGE HDBn ******************************** */
        case 0 : {

          printf("\n\n ******** DECODEUR HDBn ******** \n");
          do{
            printf("\n HDBn disponibles :\n");
            printf("    2 : HDB2 \n    3 : HDB3\n    4 : HDB4\n");
            printf(" Avec quel HDBn voulez-vous décocoder ? ");
            scanf("%d", &valHDBn);
            if((valHDBn<2) || (valHDBn>4))
              printf(" ERREUR : la valeur saisit doit être comprise entre 2 et 4.\n");
          }while((valHDBn<2) || (valHDBn>4));

          printf("\n Veuillez saisir la séquence séquence positive (P) : \n");
          for(i=0; i<longueurData; i++){
          printf(" Bit n°%d : ", i);
            scanf("%d",&p[i]);
          }
          printf("\n");

          printf("\n Veuillez saisir la séquence séquence négative (N) : \n");
          for(i=0; i<longueurData; i++){
            printf(" Bit n°%d : ", i);
            scanf("%d",&n[i]);
          }
          printf("\n");

          decodeurHDBn(valHDBn, longueurData, p, n, data);
          printf("\n Message décodé : ");
          afficherTab(data, longueurData);

          free(p);
          free(n);
          free(data);

          break;
        }

        /* ************************* DECODAGE Arithmétique ******************************** */
        case 1 : {
          printf("\n\n ******** DECODEUR Arithmétique ******** \n");


          break;
        }
        default : printf("ERREUR : decodeur = %d\n", decodeur);
                  break;
      }
      break;
    }
    default : printf("ERREUR : code = %d\n", code);
              break;
  }
}
