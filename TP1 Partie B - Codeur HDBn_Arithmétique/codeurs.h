#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculer_codage_arithmetique(float ** matArithmetique, int * data, int nb_caracteres, int longueurData, float * f);
void triBulle_Mat_c0(int ** Mat, int lignes);
void afficherMatrice_float(float ** matrice, int ligne, int colonne);
void tab2Mat(int * tab, int ** mat, int lignes, int * nb_caracteres);
void encodeurHDBn_Arithmetique(int encodeur, int longueurData, int * data, float * f, int * p, int * n);
void afficherTab(int * tab, int nb);
int ** alloue_matrice (int lignes, int colonnes);
float ** alloue_matrice_float (int lignes, int colonnes);
void free_matrice(int ** matrice, int lignes);
void free_matrice_float(float ** matrice, int lignes);
