#include "emetteur.h"

/**
 * \file emetteur.c
 * \brief Fonctions relatives à l'émetteur
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int nbUtilisateursValide(int nb)
 * \brief Retourne 1 si le nombre d'utilisateurs passé en paramètre est valide.
 * \param int nb Nombre d'utilisateurs
 * \return 1 si le nombre d'utilisateurs est valide (valeurs possibles : 1/2/4/8/16 utilisateurs). 0 sinon.
*/
int nbUtilisateursValide(int nb){
  return ((nb == 1) || (nb == 2) || (nb == 4) || (nb == 8) || (nb == 16));
}

/**
 * \fn int choixNbUtilisateurs()
 * \brief Choix du nombre d'utilisateurs
 * \return Nombre d'utilisateurs choisi
*/
int choixNbUtilisateurs(){
  int nbUtilisateurs;

  do {
    printf("\nSaisir le nombre d'utilisateurs : ");
    scanf("%d",&nbUtilisateurs);

    if(!nbUtilisateursValide(nbUtilisateurs)){
      printf("Valeurs possibles pour le nombre d'utilisateurs : 1 / 2 / 4 / 8 / 16.\nVeuillez ressaisir.\n");
    }
  } while (!nbUtilisateursValide(nbUtilisateurs));

  return nbUtilisateurs;
}

/**
 * \fn int saisieLongueurMessages()
 * \brief Saisie de la longueur des messages
 * \return Longueur des messages
*/
int saisieLongueurMessages(){
  int longueurMessages;

  do {
    printf("\nSaisir la longueur des messages : ");
    scanf("%d",&longueurMessages);
    if(longueurMessages <= 0){
      printf("La longueur des messages ne peut être négative ou nulle. Veuillez ressaisir.\n");
    }
  } while(longueurMessages <= 0);

  return longueurMessages;
}

/**
 * \fn int ** creeMatriceHadamard(int dimension)
 * \brief Crée une matrice de Hadamard dont la dimension est passée en paramètre. Un seule paramètre car c'est une matrice carrée.
 * \param int dimension Dimension de la matrice de Hadamard
 * \return Matrice de Hadamard
*/
int ** creeMatriceHadamard(int dimension){
  int ** matrice = alloue_matrice(dimension,dimension);
  int l, c, depart, niveau;

  matrice[0][0] = 1; /* HO */

  //Suite des autres étapes : H1, H2, H3...
  niveau = 1;
  depart = 1;
  l = 0;
  c = 0;
  while((l < dimension) && (c < dimension)){
    for(l = 0; l <= niveau; l++){
      for(c = depart; c <= niveau; c++){
        matrice[l][c] = matrice[l][c-depart];
      }
    }
    for(l = depart; l <= niveau; l++){
      for(c = 0; c <= niveau; c++){
        if(c >= depart)
          matrice[l][c] = -matrice[l][c-depart];
        else
          matrice[l][c] = matrice[l-depart][c];
      }
    }
    depart = niveau+1;
    niveau = (depart*2)-1;
  }

  return matrice;
}

/**
 * \fn int ** codageSequences (int nbUtilisateurs, int ** matriceHadamard, int dimensionHadamard, int ** messages, int longueurMessages, int verbose)
 * \brief Code les séquences/messages émis par le(s) utilisateur(s) à l'aide de la matrice de Hadamard
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \param int ** matriceHadamard Matrice de Hadamard
 * \param int dimensionHadamard Dimension de la matrice de Hadamard
 * \param int ** messages Matrice contenant les messages émis par les utilisateurs
 * \param int longueurMessages Longueur des messages
 * \param int verbose Indicateur si affichage détaillé ou non
 * \return Matrice contenant les séquences codées
*/
int ** codageSequences (int nbUtilisateurs, int ** matriceHadamard, int dimensionHadamard, int ** messages, int longueurMessages, int verbose){
  int i, c, numMessage, j = 0;

  // Tableau pour contenir les séquences codées de tous les messages
  int ** sequencesCodees = alloue_matrice(nbUtilisateurs,dimensionHadamard*longueurMessages);

  /* On code chaque message (séquence) à partir de la matrice de Hadamard */
  for(numMessage = 0; numMessage < nbUtilisateurs; j = 0, numMessage++){
    for (i = 0; i < longueurMessages; i++){
      for(c = 0; c < dimensionHadamard; c++){
        if(messages[numMessage][i] == 1){
          sequencesCodees[numMessage][j++] = matriceHadamard[numMessage][c];
        }
        else if(messages[numMessage][i] == 0){
          // Inversion
          switch(matriceHadamard[numMessage][c]){
            case -1: sequencesCodees[numMessage][j++] = 1; break;
            case 1: sequencesCodees[numMessage][j++] = -1; break;
            default: break;
          }
        }
      }
    }
  }

  if(verbose){
    printf("\n");
    afficherSequencesCodees(sequencesCodees,nbUtilisateurs,dimensionHadamard*longueurMessages);
    printf("\n");
  }

  return sequencesCodees;
}

/**
 * \fn void afficherSequencesCodees(int ** sequencesCodees, int lignes, int colonnes)
 * \brief Affiche les séquences codées (appelée dans la fonction codageSequences si verbose)
 * \param int ** sequencesCodees Matrice contenant les séquences codées
 * \param int lignes Nombre de lignes de la matrice sequencesCodees
 * \param int colonnes Nombre de colonnes de la matrice sequencesCodees
 * \return Rien
*/
void afficherSequencesCodees(int ** sequencesCodees, int lignes, int colonnes){
  int l, c;

  for(l = 0; l < lignes; l++){
    if(sequencesCodees[l][0] != 0){
      printf("Séquence %2d : ",l+1);
    }
    for(c = 0; c < colonnes; c++){
      if(sequencesCodees[l][c] != 0){
        printf("%2d ",sequencesCodees[l][c]);
      }
    }
    if(sequencesCodees[l][c-1] != 0){
      printf("\n");
    }
  }
}

/**
 * \fn int * etalement(int nbUtilisateurs, int dimensionHadamard, int longueurMessages, int ** sequencesCodees, int verbose)
 * \brief Effectue l'opération d'étalement. Retourne dans un tableau la valeur de la séquence du signal quand les utilisateurs émettent en même temps.
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \param int dimensionHadamard Dimension de la matrice de Hadamard
 * \param int longueurMessages Longueur des messages
 * \param int ** sequencesCodees Matrice contenant les séquences codées
 * \param int verbose Indicateur si affichage détaillé ou non
 * \return Tableau qui correspond à la séquence du signal quand les utilisateurs émettent en même temps
*/
int * etalement(int nbUtilisateurs, int dimensionHadamard, int longueurMessages, int ** sequencesCodees, int verbose){
  // Tableau pour contenir la séquence générée quand les utilisateurs émettent en mêmes temps
  int * sequenceSignal;
  int somme, c, l;

  if((sequenceSignal = malloc(sizeof(int) * (dimensionHadamard * longueurMessages))) == NULL){
    fprintf(stderr,"etalement: débordement mémoire lors de la création du tableau pour la séquence générée par le code d'étalement\n");
    exit(1);
  }

  /* Pour chaque colonne de la matrice sequencesCodees, les bits sont additionnés et la somme est ajoutée au tableau sequenceSignal */
  for(somme = 0, c = 0; c < (dimensionHadamard * longueurMessages); c++, somme = 0){
    for(l = 0; l < nbUtilisateurs; l++){
      somme += sequencesCodees[l][c];
    }
    sequenceSignal[c] = somme;
  }

  if(verbose){
    printf("Séquence après étalement : ");
    afficherTableau(sequenceSignal,dimensionHadamard * longueurMessages);
  }

  return sequenceSignal;
}

/**
 * \fn int * emetteur (int nbUtilisateurs, int longueurMessages, int verbose)
 * \brief Correspond à l'émetteur : il permet à l'utilisateur de saisir les messages et appelle les fonctions nécessaires pour créer la matrice de Hadamard, coder les séquences et effectuer l'opération d'étalement.
 * \param int nbUtilisateurs Nombre d'utilisateurs
 * \param int longueurMessages Longueur des messages
 * \param int verbose Indicateur si affichage détaillé ou non
 * \return Tableau qui contient la séquence émise après le codage des messages et l'opération d'étalement
*/
int * emetteur (int nbUtilisateurs, int longueurMessages, int verbose){
  int i, nbit;

  /* Initialisation de la dimension de la matrice de Hadamard
  *  Dimension 8 si le nombre d'utilisateurs vaut 1, 2, 4 ou 8
  *  Dimension 16 si nombre de l'utilisateurs vaut 16.
  */
  int dimensionHadamard = (nbUtilisateurs > 8) ? 16 : 8;   

  // Création de la matrice de Hadamard qui sera essentielle pour coder les séquences
  int ** matriceHadamard = creeMatriceHadamard(dimensionHadamard);

  // Affichage de la matrice de Hadamard si option verbose
  if(verbose){
    printf("\n Matrice de Hadamard : \n");
    afficherMatrice(matriceHadamard,dimensionHadamard,dimensionHadamard);
  }

  // La matrice messages est créée pour contenir les messages émis par les utilisateurs.
  int ** messages = alloue_matrice(nbUtilisateurs,longueurMessages);

  // Saisie des messages émis par les utilisateurs
  for(i = 0; i < nbUtilisateurs; i++){
    printf("\n[Saisie du message émis par l'utilisateur %d]\n",i+1);
    for(nbit = 0; nbit < longueurMessages; nbit++){
      printf("\tBit %d : ",nbit);
      scanf("%d",&messages[i][nbit]);
    }
  }

  // Codage des messages/séquences
  int ** sequencesCodees = codageSequences(nbUtilisateurs,matriceHadamard,dimensionHadamard,messages,longueurMessages, verbose);

  // Opération d'étalement
  int * sequenceSignal = etalement(nbUtilisateurs,dimensionHadamard,longueurMessages,sequencesCodees,verbose);

  free_matrice(sequencesCodees,nbUtilisateurs);
  free_matrice(messages,nbUtilisateurs);
  free_matrice(matriceHadamard,dimensionHadamard);

  return sequenceSignal;
}
