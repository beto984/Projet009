// Module util
// Contient l'ensemble des impl�mentations des fonctions
// utilitaires g�n�rales

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

/*
----------------------------------------------------------
    Fonction: rand_entre
    En bref: obtenir une valeur al�atoire comprise entre deux bornes
    Description:
        Obtient une valeur enti�re al�atoire (rand) comprise entre une borne minimum (min)
        et maximum (max). Les valeurs de bornes sont des tirages valides.
    Param�tres:
        -min: borne min
        -max: borne max
    Retour: la valeur al�atoire tir�e
----------------------------------------------------------
*/
int rand_entre(int min, int max){
	int random;

	random= (rand() % (max - min + 1)) + min;

}

/*
----------------------------------------------------------
    Fonction: generer_texte_aleatoire
    En bref: g�n�rer une ligne de texte al�atoire
    Description:
        G�n�re un ligne de texte al�atoirement en respectant certaines contraintes:
        -les lettres utilisables sont tir�es au hasard dans le tableau de lettres (l)
        -la longueur des mots est al�atoire et comprise entre lmin et lmax
        -les mots sont s�par�s par un caract�re tir� au hasard du tableau de s�parateurs (s)
        Aucune v�rification sur la validit� des donn�es initiales n'est faite (ex: nl<0). Si
        ces donn�es n'ont pas de sens, la fonction peut planter ou donner des r�sultats absurdes.
    Param�tres:
        -n: nombre total de lettres dans la ligne (longueur de la ligne � g�n�rer)
        -t: tableau dans lequel les caract�res al�atoires de la ligne sont plac�s
        -l: tableau de lettres permises
        -nl: nombre de lettre permises (taille du tableau l)
        -s: tableau de s�parateurs permis
        -ns: nombre de s�parateurs permis (taille du tableau s)
        -lmin: longueur minimum d'un mot
        -lmax: longueur maximum d'un mot

    Retour: renvoie le nombre de mot.
----------------------------------------------------------
*/

int generer_texte_aleatoire(int n, char t[], char l[],int nl, char s[], int ns, int lmin, int lmax){
    int i;      // it�rateur
    int lm;     // longueur du mot
    int nm=0;   // nombre de mot

    return nm;
}
/*
----------------------------------------------------------
    Fonction: initialiser_tableau_entier
    En bref: remplir un tableau avec une valeur
    Description:
        Parcoure un tableau d'entier pour fixer tous les entiers � la m�me valeur
    Param�tres:
        -tab: le tableau � remplir
        -taille: le nombre d'entier � �crire (taille du taleau tab)
        -val: la valeur � �crire dans toutes les cases du tableau
    Retour: aucun mais le tableau (tab) est modifi�
----------------------------------------------------------
*/
void initialiser_tableau_entier(int tab[],int taille, int val){

	printf("bobine");

}

