#include "long_max.h"

/**
 * \file long_max.c
 * \brief Génération d'un codeur à Longueur Maximale
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

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

/**
 * \fn int ** alloue_matrice (int lignes, int colonnes)
 * \brief Alloue une matrice dont les dimensions sont passées en paramètres
 * \param int lignes Nombre de lignes
 * \param int colonnes Nombre de colonnes
 * \return Matrice allouée dynamiquement
*/
int ** alloue_matrice (int lignes, int colonnes){
  int l;
  int ** matrice = NULL;

  if((matrice = malloc(lignes*sizeof(int*))) == NULL){
    fprintf(stderr,"alloue_matrice: débordement mémoire lors de la création d'une matrice\n");
    exit(1);
  }

  for(l = 0; l < lignes; l++){
    if((matrice[l] = malloc(colonnes*sizeof(int))) == NULL){
      fprintf(stderr,"alloue_matrice: débordement mémoire lors de la création d'une matrice\n");
      exit(1);
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
 * \fn codeLM_t initialiserLM();
 * \brief Initialise une structure du type codeLM_t (longueur de la séquence à générer, polynôme et registres)
 * \return Structure du type codeLM_t initialisée
*/
codeLM_t initialiserLM(){
  codeLM_t codeur;
  int i;

  /*
    Initialisation de la longueur de la séquence à générer
  */
  printf("\nSaisir la longueur de la séquence à générer : ");
  scanf("%d",&codeur.longueurSequence);

  /*
    Initialisation des registres
  */
  printf("\n[REGISTRES]\n");
  printf("Saisir le nombre d'étages pour les registres : ");
  scanf("%d",&codeur.registres.nbEtages);

  if((codeur.registres.vecteur = malloc(sizeof(int) * codeur.registres.nbEtages)) == NULL){
    fprintf(stderr,"initialiserLM: débordement mémoire lors de la création du vecteur pour les registres\n");
    exit(1);
  }

  printf("Saisir les registres :\n");
  for(i = 0; i < codeur.registres.nbEtages; i++){
    printf("\tRegistre %d : ",i+1);
    scanf("%d",&codeur.registres.vecteur[i]);
  }

  /*
    * Initialisation du polynôme de génération
  */
  printf("\n[POLYNÔME DE GENERATION]\n");
  printf("Saisir la longueur du polynôme de génération : ");
  scanf("%d",&codeur.polynome.taille);

  if((codeur.polynome.tab = malloc(sizeof(int) * codeur.polynome.taille)) == NULL){
    fprintf(stderr,"initialiserLM: débordement mémoire lors de la création du tableau pour le polynôme\n");
    exit(1);
  }

  printf("Saisir le polynôme de génération :\n");
  for(i = 0; i < codeur.polynome.taille; i++){
    printf("\tIndice %d : ",i);
    scanf("%d",&codeur.polynome.tab[i]);
  }

  return codeur;
}

/**
 * \fn void libereLM(codeLM_t codeur);
 * \brief Libère l'espace alloué dynamiquement pour l'objet de type codeLM_t passé en paramètre
 * \param codeLM_t codeur
 * \return Rien
*/
void libereLM(codeLM_t codeur){
  free(codeur.registres.vecteur);
  free(codeur.polynome.tab);
}

/**
  * \fn int * coderLM(codeLM_t codeur);
  * \brief Codeur à Longueur Maximale
  * \param codeLM_t codeur Structure contenant tous les paramètres nécessaires pour générer la séquence codée
  * \return Retourne la séquence codée générée par le codeur à Longueur Maximale
*/
int * coderLM(codeLM_t codeur){
  int i, j, l, c, val, k;

  // Calcul de la longueur maximale : 2^n+1
  int long_max = pow(2,codeur.registres.nbEtages)-1;

  // Matrice pour les combinaisons des registres
  int ** combiRegistres = alloue_matrice(long_max,codeur.registres.nbEtages);

   // Tableau pour la séquence générée par le codeur à Longueur Maximale
  int * sequenceGeneree;
  if((sequenceGeneree = malloc(sizeof(int) * codeur.longueurSequence)) == NULL){
    fprintf(stderr,"coder: débordement mémoire lors de la création du tableau pour la séquence générée\n");
    exit(1);
  }

  // La première ligne des combinaisons des registres est initialisée avec le vecteur des registres (initialisé par l'utilisateur)
  for(i = 0; i < codeur.registres.nbEtages; i++){
    combiRegistres[0][i] = codeur.registres.vecteur[i];
  }

  // On remplit la matrice de combinaisons des registres.
  for(l = 1; l < long_max; l++){
    // L'opération logique XOR est effectuée sur les colonnes indiquées dans le polynôme de génération
    for(val = 0, j = 0; j < codeur.polynome.taille; j++){
      val = combiRegistres[l-1][codeur.polynome.tab[j]-1] ^ val;
    }
    // Décalage à droite des registres
    for(c = 1; c < codeur.registres.nbEtages; c++){
      combiRegistres[l][c] = combiRegistres[l-1][c-1];
    }
    // La valeur obtenue après l'opération XOR est affectée au premier registre.
    combiRegistres[l][0] = val;
  }

  //printf("\t--> DEBOGAGE\n");
  //afficherMatrice(res,long_max,codeur.registres.nbEtages);

  // Les valeurs de la dernière colonne de la matrice des combinaisons des registres constituent la séquence générée.
  for(k = l = 0; l < codeur.longueurSequence; l++){
    sequenceGeneree[l] = combiRegistres[k][codeur.registres.nbEtages-1];
    k = ((k == long_max-1) ? 0 : k+1);
  }

  free_matrice(combiRegistres,long_max);
  // La séquence générée par le codeur à Longueur Maximale (de longueur souhaitée par l'utilisateur) est retournée.
  return sequenceGeneree;
}
