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
int rand_entre(int min, int max) {
	int random;

	random = (rand() % (max - min + 1)) + min;

	return random;
}

int test_rand_entre() {

	srand(time(0));

	for (int i = 0; i < 25; i++) {
		printf("rand_entre(50,59):\n");
		printf("%d\n\n", rand_entre(50, 59));
	}

	system("pause");
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
int generer_texte_aleatoire(int n, char t[], char l[], int nl, char s[], int ns, int lmin, int lmax) {
	int i;      // it�rateur
	int lm;     // longueur du mot
	int nm = 0;   // nombre de mot


	// tire une longueur de mot al�atoire

	nm++;


	for (i = 0; i < n; i++) {

		// si toutes les lettres du mots ne sont pas plac�

			// ajoute une lettre al�atoire
		int idx_alea = rand_entre(0, nl - 1);
		t[i] = l[idx_alea];

		// sinon, 

			// ajoute un separateur

			// tire une nouvelle longueur de mot
		nm++;

	}

	return nm;
}

int test_genere_texte_aleatoire() {

	int resultat = 0;
	int taille_chaine = 10;
	char chaine_caractere[10] = { ' ' };

	int taille_lettre_permise = 3;
	char lettre_permise[3] = { 'a','k','z' };

	srand(time(0));

	resultat = generer_texte_aleatoire(taille_chaine, chaine_caractere,
		lettre_permise, taille_lettre_permise,
		NULL, 0, 0, 0);

	for (int i = 0; i < 10; i++) {
		printf("%c\n", chaine_caractere[i]);
	}

	system("pause");

	return EXIT_SUCCESS;

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
void initialiser_tableau_entier(int tab[], int taille, int val) {

	printf("bobine");

}

