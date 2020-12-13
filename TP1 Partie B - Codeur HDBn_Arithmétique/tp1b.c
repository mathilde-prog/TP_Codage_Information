#include <stdio.h>
#include <stdlib.h>
#include "decodeurs.h"

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
          //goto decoderArithmetique;
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

          printf("\n Veuillez saisir la séquence positive (P) : \n");
          for(i=0; i<longueurData; i++){
            printf(" Bit n°%d : ", i);
            scanf("%d",&p[i]);
          }
          printf("\n");

          printf("\n Veuillez saisir la séquence négative (N) : \n");
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

          int nb_caracteres, caracSpecial=0;
          char caracteres[longueurData];
          int frequences[longueurData];
          float intervalleRef, bornInf=0;

          printf("\n Veuillez saisir la valeur à décoder (f) : ");
          scanf("%f",&f);
          printf("\n");

          /* Récupération des caractères dans l'ordre alphabétique */
          printf("\n Veuillez saisir les caractères du message dans l'ordre alphabétique, en majuscules. S'il y a des caractères spéciaux les écrire à la fin : ");
          scanf(" %[^\n]", caracteres);
          nb_caracteres = longueurData;

          /* Récupération de la fréquence de chacun des caractères */
          for(i=0; i<nb_caracteres; i++){
            printf(" Le caractère '%c' a une fréquence de : ", caracteres[i]);
            scanf("%d", &frequences[i]);
            if(frequences[i] > 1)
              nb_caracteres -= frequences[i]-1;
          }
          printf("\n");

          /* Initialisation à NULL du reste du tableau inutilisé pour le rendre plus propre*/
          if(nb_caracteres<longueurData){
            for(i=nb_caracteres; i<longueurData; i++){
              caracteres[i] = NULL;
              frequences[i] = NULL;
            }
          }

          /* Initialisation de la matrice qui va permettre le décodage avec les valeurs entrées par l'utilisateur (caractère & fréquence) + calculs des intervalles */
          float ** matDecodeur = alloue_matrice_float(nb_caracteres, 4);
          printf("longueurData = %.10f\n", (float)longueurData);
          intervalleRef = (float)1/(float)longueurData; //intervalles de référence pour une lettre
          printf("intervalleRef = %.10f\n", intervalleRef);
          for(i=0; i<nb_caracteres; i++){
            matDecodeur[i][0] = (float)caracteres[i];
            matDecodeur[i][1] = (float)frequences[i];
            if((caracteres[i] < 'A') || (caracteres[i] > 'Z'))
              caracSpecial = 1;
          }
          //La présence d'au moins un caractère spécial (autre que les lettres de l'alpahabet en majuscules) entraine le tri du tableau par ordre croissant
          if(caracSpecial == 1)
            triBulle_Mat_c0((int **)matDecodeur, nb_caracteres);

          for(i=0; i<nb_caracteres; i++){
            matDecodeur[i][2] = bornInf;
            matDecodeur[i][3] = bornInf+(matDecodeur[i][1]*intervalleRef);
            bornInf = matDecodeur[i][3];
          }

          decodeurArithmetique(longueurData, nb_caracteres, f, matDecodeur, data);

          printf("\n Message décodé : ");
          for(i=0; i<longueurData; i++){
            printf("%c", (char)data[i]);
          }
          printf("\n");

          free(p);
          free(n);
          free(data);
          free_matrice_float(matDecodeur,nb_caracteres);

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
