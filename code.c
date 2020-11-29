#include <stdio.h>
#include <stdlib.h>

/**
 * \file code.c
 * \brief Mise en oeuvre d'un codeur de Hadamard. Programmation en C.
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int ** alloue_init_matrice (int lignes, int colonnes)
 * \brief Alloue et initialise une matrice à 0
 * \param int lignes Nombre de lignes
 * \param int colonnes Nombre de colonnes
 * \return Matrice allouée dynamiquement et initialisée
*/
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

/**
 * \fn void free_matrice(int ** matrice, int lignes)
 * \brief Libère la mémoire allouée pour la matrice
 * \param int ** matrice Matrice
 * \param int lignes Nombre de lignes
 * \return Rien
*/
void free_matrice(int ** matrice, int lignes){
  int i;

  for(i = 0; i < lignes; i++){
    free((int*) matrice[i]);
  }

  free(matrice);
}

/**
 * \fn void afficherTableau (int * tab, int taille)
 * \brief Affiche le tableau passé en paramètre
 * \param int * tab
 * \param int taille
 * \return Rien
*/
void afficherTableau (int * tab, int taille){
  int i;

  for(i = 0; i < taille; i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}

/**
 * \fn void emetteur(int ** matriceHadamard, int dimension, int * emission, int taille, int ligne, int ** total)
 * \brief Code chaque séquence
 * \param int ** matriceHadamard Matrice d'Hadamard
 * \param int dimension Dimension matrice d'Hadamard
 * \param int * emission Tableau qui correspond à la séquence émise
 * \param int taille Taille de la séquence émise
 * \param int ligne Ligne utilisée dans la matrice d'Hadamard pour coder la séquence
 * \param int ** total Matrice qui stocke le résultat
 * \return Rien
*/
void emetteur(int ** matriceHadamard, int dimension, int * emission, int taille, int ligne, int ** total){
  int ligne_usr = ligne;
  int i, c, j = 0;

  for (i = 0; i < taille; i++){

    for(c = 0; c < dimension; c++){
      if(emission[i] == 1){
        total[ligne][j++] = matriceHadamard[ligne_usr][c];
      }
      else if(emission[i] == 0){
        switch(matriceHadamard[ligne_usr][c]){
          case -1: total [ligne][j++] = 1; break;
          case 1: total[ligne][j++] = -1; break;
          default: break;
        }
      }
    }

  }
}

/**
 * \fn int * somme (int ** total, int ligne, int colonne)
 * \brief Retourne dans un tableau la valeur de la séquence du signal quand les utilisateurs émettent en même temps
 * \param int ** total
 * \param int ligne
 * \param int colonne
 * \return Tableau qui correspond à la séquence du signal quand les utilisateurs émettent en même temps
*/
int * somme (int ** total, int ligne, int colonne){
  int l, c;
  int * tab = malloc(sizeof(int) * colonne);
  int somme;

  for(somme = 0, c = 0; c < colonne; c++,somme = 0){
    for(l = 0; l < ligne; l++){
      somme += total[l][c];
    }
    tab[c] = somme;
  }

  return tab;

}

/**
 * \fn void afficherMatrice(int ** matrice, int ligne, int colonne )
 * \brief Affiche la matrice passée en paramètre
 * \param int ** matrice Matrice
 * \param int ligne Nombre de lignes
 * \param int colonne Nombre de colonnes
 * \return Rien
*/
void afficherMatrice(int ** matrice, int ligne, int colonne ){
  int l, c;

  for(l = 0; l < ligne; l++){
    for(c = 0; c < colonne; c++){
      printf("%2d ",matrice[l][c]);
    }
    printf("\n");
  }
}

void afficherMatriceResultat(int ** matrice, int ligne, int colonne ){
  int l, c;

  for(l = 0; l < ligne; l++){
    if(matrice[l][0] != 0){
      printf("Séquence %2d : ",l+1);
    }
    for(c = 0; c < colonne; c++){
      if(matrice[l][c] != 0){
        printf("%2d ",matrice[l][c]);
      }
    }
    if(matrice[l][c-1] != 0){
      printf("\n");
    }
  }
}

/**
 * int nbUtilisateursValide(int nb)
 * \brief Retourne 1 si le nombre d'utilisateurs passé en paramètre est valide.
 * \param int nb Nombre d'utilisateurs
 * \return 1 si vrai. 0 si faux.
*/
int nbUtilisateursValide(int nb){
  return ((nb == 1) || (nb == 2) || (nb == 4) || (nb == 8) || (nb == 16));
}

/**
 * void saisieNbUtilisateurs(int * nbUtilisateurs)
 * \brief Saisie du nombre d'utilisateurs
 * \param int * nbUtilisateurs Nombre d'utilisateurs
 * \return Rien
*/
void saisieNbUtilisateurs(int * nbUtilisateurs){
  do {
    printf("\nSaisir le nombre d'utilisateurs : ");
    scanf("%d",nbUtilisateurs);

    if(!nbUtilisateursValide(*nbUtilisateurs)){
      printf("Valeurs possibles pour le nombre d'utilisateurs : 1 / 2 / 4 / 8 / 16.\nVeuillez ressaisir.\n");
    }
  } while (!nbUtilisateursValide(*nbUtilisateurs));
}

/**
 * \fn int creeMatriceHadamard(int ** matriceHadamard, int dimension)
 * \brief Crée une matrice d'Hadamard
 * \param int ** matriceHadamard Matrice
 * \param int dimension Dimension matrice d'Hadamard
 * \return Rien
*/
int creeMatriceHadamard(int ** matriceHadamard, int dimension){
  int l, c, depart, niveau;

  matriceHadamard[0][0] = 1; //HO

  //Suite des autres étapes : H1, H2, H3...
  niveau = 1;
  depart = 1;
  l = 0;
  c = 0;
  while((l < dimension) && (c < dimension)){
    for(l = 0; l <= niveau; l++){
      for(c = depart; c <= niveau; c++){
        matriceHadamard[l][c] = matriceHadamard[l][c-depart];
      }
    }
    for(l = depart; l <= niveau; l++){
      for(c = 0; c <= niveau; c++){
        if(c >= depart)
          matriceHadamard[l][c] = -matriceHadamard[l][c-depart];
        else
          matriceHadamard[l][c] = matriceHadamard[l-depart][c];
      }
    }
    depart = niveau+1;
    niveau = (depart*2)-1;
  }
}

int main(){
    int nbUtilisateurs;
    saisieNbUtilisateurs(&nbUtilisateurs);

    int dimMat = (nbUtilisateurs > 8) ? 16 : 8;
    int ** matriceHadamard = alloue_init_matrice(dimMat,dimMat);
    int emission[3];
    int i, num_sequence = 0;

    printf("\nMatrice Hadamard : \n");
    creeMatriceHadamard(matriceHadamard,dimMat);
    afficherMatrice(matriceHadamard,dimMat,dimMat);

    int ** resultat = alloue_init_matrice(dimMat,dimMat*3);

    for(i = 0; i < nbUtilisateurs; i++){
      printf("Saisir séquence émise par l'utilisateur %d : ",i);
      scanf("%d %d %d",&emission[0],&emission[1],&emission[2]);
      emetteur(matriceHadamard,dimMat,emission,3,num_sequence++,resultat);
    }

    printf("\n");

    afficherMatriceResultat(resultat,dimMat,dimMat*3);

    printf("\n\n");
    afficherTableau(somme(resultat,dimMat,dimMat*3),dimMat*3);

    free_matrice(matriceHadamard,dimMat);
    free_matrice(resultat,dimMat);
}
