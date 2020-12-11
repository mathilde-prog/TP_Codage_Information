#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "emetteur.h"
#include "recepteur.h"
#include "matrice_tab.h"
#include "canal.h"

/*
   L'option verbose permet d'afficher tous les messages de trace si elle est positionnée :
    - Affichage de la matrice de Hadamard
    - Affichage des séquences codées
    - Affichage de la séquence après étalement
    Exécutez ./tp1a --verbose OU ./tp1a -v
*/

static struct option longopts[] = {
  {"verbose", no_argument, NULL, (int)'v'},
  {0, 0, 0, 0}
};

/*
  * Programme principal pour tester le code à étalement
  */

int main(int argc, char * argv[], char * env[]){
    int verbose = 0, nbUtilisateurs, longueurMessages;
    char c;

    // Option verbose : affiche tous les messages de trace si elle est positionnée.
    while ((c = getopt_long(argc,argv,"v",longopts,NULL)) != -1){
      if(c == 'v'){
        verbose = 1;
      }
    }

    // Choix du nombre d'utilisateurs
    nbUtilisateurs = choixNbUtilisateurs();

    // Saisie de la longueur des messages
    longueurMessages = saisieLongueurMessages();

    /*
      * EMETTEUR
    */
    int * sequenceSignal = emetteur(nbUtilisateurs,longueurMessages,verbose);

    /*
      * CANAL IDEAL
    */
    canalIdeal(sequenceSignal);

    /*
      * RECEPTEUR
    */
    int ** messagesRecus = desetalement(nbUtilisateurs,sequenceSignal,longueurMessages);

    afficherMessagesRecus(nbUtilisateurs,messagesRecus,longueurMessages);

    free(sequenceSignal);
    free_matrice(messagesRecus,nbUtilisateurs);

    return EXIT_SUCCESS;
}
