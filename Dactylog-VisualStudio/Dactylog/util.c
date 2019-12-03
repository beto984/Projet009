// Module util
// Contient l'ensemble des implémentations des fonctions
// utilitaires générales

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

/*
----------------------------------------------------------
    Fonction: rand_entre
    En bref: obtenir une valeur aléatoire comprise entre deux bornes
    Description:
        Obtient une valeur entière aléatoire (rand) comprise entre une borne minimum (min)
        et maximum (max). Les valeurs de bornes sont des tirages valides.
    Paramètres:
        -min: borne min
        -max: borne max
    Retour: la valeur aléatoire tirée
----------------------------------------------------------
*/
int rand_entre(int min, int max){
	int random;

	random= (rand() % (max - min + 1)) + min;

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
    En bref: générer une ligne de texte aléatoire
    Description:
        Génère un ligne de texte aléatoirement en respectant certaines contraintes:
        -les lettres utilisables sont tirées au hasard dans le tableau de lettres (l)
        -la longueur des mots est aléatoire et comprise entre lmin et lmax
        -les mots sont séparés par un caractère tiré au hasard du tableau de séparateurs (s)
        Aucune vérification sur la validité des données initiales n'est faite (ex: nl<0). Si
        ces données n'ont pas de sens, la fonction peut planter ou donner des résultats absurdes.
    Paramètres:
        -n: nombre total de lettres dans la ligne (longueur de la ligne à générer)
        -t: tableau dans lequel les caractères aléatoires de la ligne sont placés
        -l: tableau de lettres permises
        -nl: nombre de lettre permises (taille du tableau l)
        -s: tableau de séparateurs permis
        -ns: nombre de séparateurs permis (taille du tableau s)
        -lmin: longueur minimum d'un mot
        -lmax: longueur maximum d'un mot

    Retour: renvoie le nombre de mot.
----------------------------------------------------------
*/
int generer_texte_aleatoire(int n, char t[], char l[], int nl, char s[], int ns, int lmin, int lmax) {
	int i;      // itérateur
	int lm;     // longueur du mot
	int nm = 0;   // nombre de mot


	// tire une longueur de mot aléatoire

	nm++;


	for (i = 0; i < n; i++) {

		// si toutes les lettres du mots ne sont pas placé

			// ajoute une lettre aléatoire
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
        Parcoure un tableau d'entier pour fixer tous les entiers à la même valeur
    Paramètres:
        -tab: le tableau à remplir
        -taille: le nombre d'entier à écrire (taille du taleau tab)
        -val: la valeur à écrire dans toutes les cases du tableau
    Retour: aucun mais le tableau (tab) est modifié
----------------------------------------------------------
*/
void initialiser_tableau_entier(int tab[],int taille, int val){



}

