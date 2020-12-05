#include "jpl.h"

/**
 * \file jpl.c
 * \brief Génération d'un codeur JPL
 * \author Mathilde Mottay, Anaïs Mottier
 * \version 1.0
 * \date 2020
*/

/**
 * \fn int pgcd(int a, int b);
 * \brief Calcule le pgcd des deux entiers passés en paramètres
 * \param int a Entier 1
 * \param int b Entier 2
 * \return pgcd de a et b
*/
int pgcd(int a, int b){
	int pgcd = 1;
	int dividende = (a > b) ? a : b;
	int diviseur = (a > b) ? b : a;

	if(diviseur) {
		int reste = dividende%diviseur;
		pgcd = diviseur;

		while(reste){
			pgcd = reste;
			dividende = diviseur;
			diviseur = reste;
			reste = dividende%diviseur;
		}
	}

	return pgcd;
}

/**
 * \fn int estPremier(int a, int b);
 * \brief Vérifie si les entiers passés en paramètres sont premiers entre eux (PGCD égal à 1)
 * \param int a Entier 1
 * \param int b Entier 2
 * \return 1 si les entiers sont premiers entre eux. 0 sinon.
*/
int estPremier(int a, int b){
  return pgcd(a,b) == 1;
}

/**
 * \fn int tousLesNbEtagesSontPremiersEntreEux(jpl_t jpl, int nbCodeLM, int entier);
 * \brief Vérifie si tous les nombres d'étages des registres sont premiers entre eux
 * \param jpl_t jpl
 * \param int nbCode Nombre de code LM
 * \param int entier
 * \return 1 tous les nombres d'étages des registres sont premiers entre eux. 0 sinon.
*/
int tousLesNbEtagesSontPremiersEntreEux(jpl_t jpl, int nbCodeLM, int entier){
  int i;

  for(i = 0; i < nbCodeLM; i++){
    if(!estPremier(jpl.codesLM[i].registres.nbEtages,entier)){
      return 0;
    }
  }
  return 1;
}

/**
 * \fn jpl_t initialiserJPL();
 * \brief Initialise une structure du type jpl_t (nombre de codes LM, codes LM (registes + polynôme), longueur de la séquence à générer)
 * \return Structure du type jpl_t initialisée
*/
jpl_t initialiserJPL(){
  jpl_t codeurJPL;
  int i, j;

	/* Saisie du nombre de codes à longueur maximale  */
  do {
    printf("\nSaisir le nombre de codes à Longueur Maximale (minimum 2) : ");
    scanf("%d",&codeurJPL.nbCodesLM);
    if(codeurJPL.nbCodesLM  < 2){
      printf("Un code JPL nécessite au minimum 2 codes à Longueur Maximale. Veuillez ressaisir.\n");
    }
  } while(codeurJPL.nbCodesLM  < 2);

  if((codeurJPL.codesLM = malloc(sizeof(codeLM_t) * codeurJPL.nbCodesLM)) == NULL){
		fprintf(stderr,"initialiserJPL: débordement mémoire lors de la création du tableau pour les codes à longueur maximale\n");
    exit(1);
  }

	/* Saisie de la longueur de la séquence à générer */
  printf("\nSaisir la longueur de la séquence à générer : ");
  scanf("%d",&codeurJPL.longueurSequence);

	/* On initialise chaque code à longueur maximale */
  for(i = 0; i < codeurJPL.nbCodesLM; i++){
    printf("\n*** Code à longueur maximale %d ***\n",i+1);

		// Même longueur de séquence à générer pour tous les codes à longueur maximale
    codeurJPL.codesLM[i].longueurSequence = codeurJPL.longueurSequence;

		/*
			Saisie du nombre d'étages pour les registres
		 	+ Vérification qu'il soit premier avec le nombre d'étages des registres des autres codes à longueur maximale
		*/
		printf("\n[REGISTRES]\n");
    do {
      printf("Saisir le nombre d'étages pour les registres : ");
      scanf("%d",&codeurJPL.codesLM[i].registres.nbEtages);
      if(!tousLesNbEtagesSontPremiersEntreEux(codeurJPL,i,codeurJPL.codesLM[i].registres.nbEtages)){
        printf("Les nombres d'étages des registres des différents codes doivent être premiers entre eux.\n");
      }
    } while(!tousLesNbEtagesSontPremiersEntreEux(codeurJPL,i,codeurJPL.codesLM[i].registres.nbEtages));

    if((codeurJPL.codesLM[i].registres.vecteur = malloc(sizeof(int) * codeurJPL.codesLM[i].registres.nbEtages)) == NULL){
			fprintf(stderr,"initialiserJPL: débordement mémoire lors de la création du vecteur pour les registres du code LM %d\n",i);
      exit(1);
    }

		// Saisie des registres
    printf("Saisir les registres :\n");
    for(j = 0; j < codeurJPL.codesLM[i].registres.nbEtages; j++){
			printf("\tRegistre %d : ",j+1);
      scanf("%d",&codeurJPL.codesLM[i].registres.vecteur[j]);
    }

		printf("\n[POLYNÔME DE GENERATION]\n");
		// Saisie de la longueur du polynôme de génération
    printf("Saisir la longueur du polynome de génération : ");
    scanf("%d",&codeurJPL.codesLM[i].polynome.taille);

    if((codeurJPL.codesLM[i].polynome.tab = malloc(sizeof(int) * codeurJPL.codesLM[i].polynome.taille)) == NULL){
			fprintf(stderr,"initialiserJPL: débordement mémoire lors de la création du tableau pour le polynôme du code LM %d\n",i);
      exit(1);
    }

		// Saisie du polynôme de génération
    printf("\nSaisir le polynome de génération :\n");
    for(j = 0; j < codeurJPL.codesLM[i].polynome.taille; j++){
			printf("\tIndice %d : ",j);
      scanf("%d",&codeurJPL.codesLM[i].polynome.tab[j]);
    }
  }

  return codeurJPL;
}

/**
 * \fn int * coderJPL (jpl_t codeurJPL);
 * \brief Codeur JPL
 * \param jpl_t codeurJPL Structure contenant tous les paramètres nécessaires pour générer la séquence codée
 * \return Retourne la séquence codée générée par le codeur JPL
*/
int * coderJPL (jpl_t codeurJPL){
  int * sequenceGeneree; 	// Tableau pour la séquence générée par le codeur JPL
	int * sg_codeLM; 			  // Tableau pour récupérer les séquences générées par les codes LM
  int i, j;

	if((sequenceGeneree = malloc(sizeof(int) * codeurJPL.longueurSequence)) == NULL){
    fprintf(stderr,"coderJPL: débordement mémoire lors de la création du tableau pour la séquence générée\n");
    exit(1);
  }

	// Initialisation à 0 de la séquence générée (car on appliquera ensuite XOR)
  for(i = 0; i < codeurJPL.longueurSequence; i++){
    sequenceGeneree[i] = 0;
  }

	// On applique XOR entre chaque séquence obtenue par les codes à longueur maximale pour obtenir la séquence générée par le codeur JPL
  for(i = 0; i < codeurJPL.nbCodesLM; i++){
    sg_codeLM = coderLM(codeurJPL.codesLM[i]);
    for(j = 0; j < codeurJPL.longueurSequence; j++){
      sequenceGeneree[j] = sequenceGeneree[j] ^ sg_codeLM[j];
    }
  }

  free(sg_codeLM);
	// La séquence générée par le codeur JPL (de longueur souhaitée par l'utilisateur) est retournée.
  return sequenceGeneree;
}

/**
 * \fn void libereJPL(jpl_t codeurJPL);
 * \brief Libère l'espace alloué dynamiquement pour l'objet de type jpl_t passé en paramètre
 * \param jpl_t codeurJPL
 * \return Rien
*/
void libereJPL(jpl_t codeurJPL){
  int i;

  for(i = 0; i < codeurJPL.nbCodesLM; i++){
    libereLM(codeurJPL.codesLM[i]);
  }
}
