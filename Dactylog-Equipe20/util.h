#ifndef UTIL_H
#define UTIL_H

// Module util
// Contient l'ensemble des constantes et prototypes des fonctions
// utilitaires g�n�rales

#define VRAI 1              // pour bool�en
#define FAUX 0              // pour bool�en

#define NONE -1             // valeur pour une information ind�finie

int rand_entre(int min, int max);
int generer_texte_aleatoire(int n, char t[], char l[],int nl, char s[], int ns, int lmin, int lmax);
void initialiser_tableau_entier(int tab[],int taille, int val);


#endif
