// Module gestion_fichier
// Contient l'ensemble des impl�mentations des fonctions
// de gestion de fichiers (lecture)

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <string.h>

#include "gestion_fichier.h"
#include "util.h"
#include "gestion_statistiques.h"

/*
----------------------------------------------------------
	Fonction: fichier_sauter_commentaires
	En bref: obtenir un ligne d'un fichier en sautant les lignes de commentaires
	Description:
		Permet de lire une ligne d'un fichier mais d'ignorer les lignes de commentaires.
		Une ligne de commentaire commence par le caract�re BALISE_COMMMENTAIRE ou un espace.
		La ligne lue se retrouve dans une chaine de caract�res (tmp).
	Param�tres:
		-tmp: espace pour stocker la ligne lue
	Retour: 1 en cas de succ�s de lecture. 0 sinon
----------------------------------------------------------
*/
int fichier_sauter_commentaires(FILE* file_ptr, char tmp[]) {
	char* test;
	while ((test = fgets(tmp, MAX_CAR, file_ptr))
		&& ((*tmp == BALISE_COMMMENTAIRE)
			|| (*tmp == ' ')));
	return (test != NULL);
}

/*
----------------------------------------------------------
	Fonction: charger_exercice_pratique
	En bref: charger toutes les informations d'un exercice pratique d'un fichier
	Description:
		Permet de lire un fichier d'exercice pour se positionner � un exercice donn� et
		obtenir toutes les caract�ristiques de cet exercice.
		Le fichier � lire est d�termin� par l'index dans le tableau de statistiques (STAT_CLAVIER_NO)
		et la liste de noms des claviers (clavier_tab).
		Les lettres de l'exercice sont �crites dans un tableau (lettre_tab),
		les s�parateurs sont �crits dans un autre tableau (separateur_tab).
		Le nombre de s�parateurs (STAT_SEPARATEUR_NB), le nombre de lettres (STAT_LETTRE_NB),
		la longueur de mot minimum (STAT_LONG_MOT_MIN) et maximum (STAT_LONG_MOT_MAX) sont
		�crits dans le tableau de statistiques (STAT_TAB).
	Param�tres:
		-clavier_tab: le tableau des diff�rents claviers possibles
		-stat_tab: le tableau des statistiques
		-lettre_tab: le tableau des lettres de l'exercice
		-separateur_tab: le tableau des s�parateurs de l'exercice
	Retour: VRAI si la lecture du fichier fonctionne. FAUX sinon.
	Param�tres modifi�s: stat_tab, clavier_tab, lettre_tab, sepatateur_tab
----------------------------------------------------------
*/
int charger_exercice_pratique(char clavier_tab[][MAX_CAR], int stat_tab[],
	char lettre_tab[], char separateur_tab[]) {
	FILE* file_ptr;
	char nomFichier[MAX_CAR];
	char* ptr;
	char tmp[MAX_CAR];
	char nom[MAX_CAR];
	short found = FAUX;   // indique si l'exercice est trouv� dans le fichier
	short fin = FAUX;     // indique si la fin du fichier est atteinte
	int resultat = FAUX;
	int i;              // it�rateur de boucle


	stat_tab[STAT_EXERCICE_TYPE] = EXERCICE_INCONNU;

	// d�terminer le nom du fichier de clavier � ouvrir
	sprintf(nomFichier, "%s", strtok(clavier_tab[stat_tab[STAT_CLAVIER_NO]], " "));

	// g�n�rer le nom � chercher pour trouver le exercice dans le fichier
	sprintf(nom, "%s%d", BALISE_EXERCICE, stat_tab[STAT_EXERCICE_NO]);

	// ouvrir le fichier d'un clavier contenant les diff�rents exercices
	file_ptr = fopen(nomFichier, "r");

	// si le fichier � pu �tre ouvert
	if (file_ptr != NULL) {
		// lire des lignes dans le fichier en ne consid�rant que celles qui commencent par *
		// jusqu'� atteindre l'exercice voulu
		do {
			if (fgets(tmp, MAX_CAR, file_ptr)) {
				if (strstr(tmp, nom) == tmp) {
					found = VRAI;
				}
			}
			else
				fin = VRAI;
		} while (!fin && !found);

		// si l'exercice est trouv�, charger cet exercice
		if (found) {
			if (strstr(tmp, BALISE_PRATIQUE)) {
				//sauter les commentaires
				if ((fichier_sauter_commentaires(file_ptr, tmp))
					&& (2 == sscanf(tmp, "%d-%d", &stat_tab[STAT_LONG_MOT_MIN], &stat_tab[STAT_LONG_MOT_MAX]))
					&& (fichier_sauter_commentaires(file_ptr, tmp))
					&& (1 == sscanf(tmp, "%d:", &stat_tab[STAT_SEPARATEUR_NB]))
					&& (ptr = strchr(tmp, ':'))
					&& (strlen(++ptr) >= (unsigned int)(stat_tab[STAT_SEPARATEUR_NB] + 1))) {

					for (i = 0;i < stat_tab[STAT_SEPARATEUR_NB];i++) {
						separateur_tab[i] = ptr[i];
					}
					if ((fichier_sauter_commentaires(file_ptr, tmp))
						&& (1 == sscanf(tmp, "%d:", &stat_tab[STAT_LETTRE_NB]))
						&& (ptr = strchr(tmp, ':'))
						&& (strlen(++ptr) >= (unsigned int)(stat_tab[STAT_LETTRE_NB] + 1))) {
						for (i = 0;i < stat_tab[STAT_LETTRE_NB];i++) {
							lettre_tab[i] = ptr[i];
						}
						stat_tab[STAT_EXERCICE_TYPE] = EXERCICE_PRATIQUE;
						resultat = VRAI;
					}
				}
			}
		}
		fclose(file_ptr);
	}

	return  resultat;
}

/*
----------------------------------------------------------
	Fonction: charger_exercice_theorique
	En bref: charger toutes les informations d'un exercice th�orique d'un fichier
	Description:
		Permet de lire un fichier d'exercice pour se positionner � un exercice donn� et
		obtenir toutes les lignes de th�orie de cet exercice.
		Le fichier � lire est d�termin� par l'index dans le tableau de statistiques (STAT_CLAVIER_NO)
		et la liste de noms des claviers (clavier_tab).
		Les lignes sont �crites dans un tableau (theorie_tab).
	Param�tres:
		-clavier_tab: le tableau des diff�rents claviers possibles
		-stat_tab: le tableau des statistiques
		-theorie_tab: le tableau des lignes de th�orie
	Retour: VRAI si la lecture du fichier fonctionne. FAUX sinon.
	Param�tres modifi�s: stat_tab, clavier_tab, theorie_tab
----------------------------------------------------------
*/
int charger_exercice_theorique(char clavier_tab[][MAX_CAR], int stat_tab[], char theorie_tab[][MAX_CAR]) {
	FILE* file_ptr;
	char nomFichier[MAX_CAR];
	char tmp[MAX_CAR];
	char nom[MAX_CAR];
	short found = FAUX;  // indique si l'exercice est trouv� dans la fichier
	short fin = FAUX;    // indique si la fin du fichier est atteinte

	// d�terminer le nom du fichier de clavier � ouvrir
	sprintf(nomFichier, "%s", strtok(clavier_tab[stat_tab[STAT_CLAVIER_NO]], " "));

	// g�n�rer le nom � chercher pour trouver l'exercice dans le fichier
	sprintf(nom, "%s%d", BALISE_EXERCICE, stat_tab[STAT_EXERCICE_NO]);

	// ouvrir le fichier d'un clavier contenant les diff�rents exercices
	file_ptr = fopen(nomFichier, "r");

	// initialiser le nombre de lignes lues
	stat_tab[STAT_LIGNE_THEO_NB] = 0;

	// si le fichier � pu �tre ouvert
	if (file_ptr != NULL) {
		// lire des lignes dans le fichier en ne consid�rant que celles qui commencent par *
		// jusqu'� atteindre l'exercice voulu
		do {
			if (fgets(tmp, MAX_CAR, file_ptr)) {
				if (strstr(tmp, nom) == tmp) {
					found = VRAI;
				}
			}
			else
				fin = VRAI;
		} while (!fin && !found);

		// si le exercice est trouv�, charger ce exercice
		if (found) {
			if (strstr(tmp, BALISE_THEORIQUE)) {

				// charger le texte de la th�orie dans le tableau
				while ((fgets(tmp, MAX_CAR, file_ptr)) && (*tmp != '*')) {
					if ((*tmp != BALISE_COMMMENTAIRE) && (*tmp != '\n') && (*tmp != ' ')) {
						strcpy(theorie_tab[stat_tab[STAT_LIGNE_THEO_NB]++], tmp);
					}
				}
			}
		}
		fclose(file_ptr);
	}
	return  stat_tab[STAT_LIGNE_THEO_NB];
}

/*
----------------------------------------------------------
	Fonction: charger_item_etoile_fichier
	En bref: lire un fichier texte et charger en m�moire toutes les lignes (items) pr�c�d�es d'une �toile
	Description:
		Permet de lire un fichier (nomFichier), parcourir chaque ligne pour m�moriser
		uniquement celles qui commencent par une �toile (*, BALISE_ETOILE).
		Chaque ligne ainsi trouv�e est ajout�e � un tableau (item_tab).
		(Ce tableau pourra ensuite �tre utilis� pour cr�er un menu par exemple).
	Param�tres:
		-item_tab: le tableau ou �crire les lignes trouv�es commen�ant par une �toile
		-nomFichier: le nom du fichier � lire
	Retour: le nombre d'item charg�.
			-1 en cas de probl�me d'ouverture de fichier.
			0 si aucun item trouv�
	Param�tres modifi�s: item_tab
----------------------------------------------------------
*/
int charger_item_etoile_fichier(char item_tab[][MAX_CAR], char* nomFichier) {
	FILE* file_ptr;     // pointeur au fichier
	char tmp[MAX_CAR];  // chaine temporaire pour les lectures du fichier
	int nb = -1;          // nombre de lignes charg�es dans le tableau
	short fin = FAUX;    // indicateur d'atteinte de fin du fichier


	// ouvrir le fichier d'un clavier contenant les diff�rents exercices
	file_ptr = fopen(nomFichier, "r");

	// si le fichier n'a pu �tre ouvert
	if (file_ptr == NULL) {
		return -1;
	}

	// lire des lignes dans le fichier en ne consid�rant que celle qui commence par *
	// jusqu'� atteindre l'exercice voulu
	do {

		if (fgets(tmp, MAX_CAR, file_ptr)) {
			printf("%c\n", tmp[0]);
		}
		else {
			fin = VRAI;
		}

	} while (!fin);


	fclose(file_ptr);

	// renvoyer le nombre de lignes ajout�es au tableau
	return  nb;
}
int test_charger_item_etoile_fichier() {

	char item_tab[10][MAX_CAR];
	char* nomFichier = "clavier.lst";

	charger_item_etoile_fichier(item_tab, nomFichier);

	system("pause");
}
/*
----------------------------------------------------------
	Fonction: determiner_type_exercice
	En bref: d�terminer s'il s'agit d'un exercice pratique ou th�orique
	Description:
		Analyse la ligne d'en-t�te d'un exercice pour d�terminer s'il
		s'agit d'un exercice pratique ou th�orique.
		Exemple d'en-t�te:
			*EXERCICE 3: lettres fj - pratique
		Si la balise "- pratique" (BALISE_PRATIQUE) est trouv�e dans cette ligne,
		il s'agit d'un exercice pratique (EXERCICE_PRATIQUE).
		Si la balise "- theorie" (BALISE_THEORIQUE) est trouv�e dans cette ligne,
		il s'agit d'un exercice th�orique (EXERCICE_THEORIQUE).
		Si aucune des balises n'est trouv�e dans cette ligne,
		il s'agit d'un exercice de type inconnu (EXERCICE_INCONNU)
	Param�tres:
		-exercice: la chaine de caract�re d�crivant l'exercice (ex:"*EXERCICE 3: lettres fj - pratique")
	Retour: EXERCICE_PRATIQUE/EXERCICE_THEORIQUE/EXERCICE_INCONNU selon la balise trouv�e
----------------------------------------------------------
*/
int determiner_type_exercice(char exercice[]) {
	int type;
	if (strstr(exercice, BALISE_THEORIQUE)) type = EXERCICE_THEORIQUE;
	else if (strstr(exercice, BALISE_PRATIQUE)) type = EXERCICE_PRATIQUE;
	else type = EXERCICE_INCONNU;
	return type;
}
