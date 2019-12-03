// Module gestion_mode
// Contient l'ensemble des implémentations des fonctions
// de gestion des principaux modes et états de la machine à états

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>

#include "curses.h"                 // la librairie pdcurses
#include "gestion_fichier.h"
#include "gestion_statistiques.h"
#include "affichage_et_clavier.h"
#include "util.h"
#include "gestion_modes.h"

/*
----------------------------------------------------------
    Fonction: menu_principal
    En bref: gère les états du mode menu-principal
    Description:
        Gestion des états du mode menu-principal de l'initialisation jusqu'à la fin.
        Le menu principal est affiché puis une sélection est possible avec les flèches
        et Enter. Selon l'option choisie, le mode suivant est fixée au MODE_CHOIX_CLAVIER,
        MODE_CHOIX_EXERCICE, ou MODE_QUITTER. Le mode suivant est renvoyée par la fonction.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -menu_tab: le tableau des options du menu (chaînes de car.)
        -nb_menu: le nombre d'option (taille du tableau menu_tab)
        -clavier_tab: le tableau des différents claviers possibles
        -stat_tab: le tableau des statistiques
    Retour: Le mode suivant est renvoyée par la fonction.
----------------------------------------------------------
*/
int menu_principal(WINDOW* fenetre[],char menu_tab[][MAX_CAR],int nb_menu,char clavier_tab[][MAX_CAR],int stat_tab[]){
    int key_type;                             // type de touche reçue du clavier
    int highlight;                          // position de l'item surligné
    int mode_suivant=MODE_MENU_PRINCIPAL;   // mode suivant à appliqjer après le mode actuel
    int etat=ETAT_MENU_PRINCIPAL_INIT;      // état actuel
    do{
        switch(etat){
            case ETAT_MENU_PRINCIPAL_INIT:
                if(stat_tab[STAT_CLAVIER_NO]==NONE) highlight=MENU_CHOIX_CLAVIER;
                else highlight=MENU_CHOIX_EXERCICE;
                afficher_consignes(fenetre,TITRE_MENU_PRINCIPAL,MSG_NAV_MENU);
                afficher_statistiques(fenetre,clavier_tab,stat_tab);
                etat=ETAT_MENU_PRINCIPAL_MAJ;
                break;
            case ETAT_MENU_PRINCIPAL_MAJ:
                afficher_menu(fenetre,menu_tab,nb_menu,highlight);
                capture_clavier(fenetre,&key_type);
                clear_message(fenetre);
                switch(key_type){
                     case TOUCHE_ENTER:
                        switch(highlight){
                            case MENU_CHOIX_CLAVIER:
                                mode_suivant=MODE_CHOIX_CLAVIER;
                                etat=ETAT_MENU_PRINCIPAL_FIN;
                                break;
                            case MENU_CHOIX_EXERCICE:
                                mode_suivant=MODE_CHOIX_EXERCICE;
                                etat=ETAT_MENU_PRINCIPAL_FIN;
                                break;
                            case MENU_QUITTER:
                                mode_suivant=MODE_QUITTER;
                                etat=ETAT_MENU_PRINCIPAL_FIN;
                            default:
                                mode_suivant=MODE_QUITTER;
                                etat=ETAT_MENU_PRINCIPAL_FIN;
                                break;
                        }
                        break;
                    case TOUCHE_FLECHE_HAUT:
                        if (highlight>0) (highlight)--;
                        break;
                    case TOUCHE_FLECHE_BAS:
                        if (highlight<nb_menu-1) (highlight)++;
                        break;
                    case TOUCHE_ESCAPE:
                        etat=ETAT_MENU_PRINCIPAL_INIT;
                        break;
                }
                break;
        }
    }while(etat!=ETAT_MENU_PRINCIPAL_FIN);
    return mode_suivant;
}

/*
----------------------------------------------------------
    Fonction: choix_clavier
    En bref: gère les états du mode choix_clavier
    Description:
        Gestion des états du mode choix_clavier de l'initialisation jusqu'à la fin.
        La liste des claviers possible est affichée puis une sélection est possible avec les flèches
        et Enter. Selon l'option choisie, le mode suivant est toujours MODE_MENU_PRINCIPAL.
        Le mode suivant est renvoyée par la fonction.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -clavier_tab: le tableau des différents claviers possibles
        -stat_tab: le tableau des statistiques
        -nom_fichier_liste_clavier: nom du fichier ou se trouve la liste des claviers
    Retour: Le mode suivant est renvoyée par la fonction.
----------------------------------------------------------
*/
int choix_clavier(WINDOW* fenetre[], char clavier_tab[][MAX_CAR], int stat_tab[], char nom_fichier_liste_clavier[]) {
	int highlight;
	int key_type = TOUCHE_FLECHE_BAS;
	int mode_suivant = MODE_MENU_PRINCIPAL;
	int etat = ETAT_CHOIX_CLAVIER_INIT;

	do {
		switch (etat) {
		case ETAT_CHOIX_CLAVIER_INIT:

			stat_tab[STAT_CLAVIER_NB] = charger_item_etoile_fichier(clavier_tab, nom_fichier_liste_clavier);

			if (stat_tab[STAT_CLAVIER_NB] <= 0) {
				afficher_message(fenetre, MSG_LECT_CLV_IMPOSSIBLE, MSG_TYPE_BAD);
				etat = ETAT_CHOIX_CLAVIER_FIN;
			}
			else {
				highlight = 0;
				afficher_consignes(fenetre, TITRE_CHOIX_CLAVIER, MSG_NAV_MENU);
				etat = ETAT_CHOIX_CLAVIER_MAJ;
			}
			break;

		case ETAT_CHOIX_CLAVIER_MAJ:
			afficher_menu(fenetre, clavier_tab, stat_tab[STAT_CLAVIER_NB], highlight);
			capture_clavier(fenetre, &key_type);
			clear_message(fenetre);
			switch (key_type) {

			case TOUCHE_ENTER:

				etat = ETAT_CHOIX_CLAVIER_FIN;
				break;

			case TOUCHE_ESCAPE:

				etat = ETAT_CHOIX_CLAVIER_FIN;
				break;
			}
			break;
		}

	} while (etat != ETAT_CHOIX_CLAVIER_FIN);




	return mode_suivant;
}

/*
----------------------------------------------------------
    Fonction: choix_exercice
    En bref: gère les états du mode choix_exercice
    Description:
        Gestion des états du mode choix_exercice de l'initialisation jusqu'à la fin.
        La liste des exercicess possible est affichée puis une sélection est possible avec les flèches
        et Enter. Selon l'option choisie, le mode suivant est soit
        MODE_MENU_PRINCIPAL ou MODE_EXERCICE_SUIVANT.
        Le mode suivant est renvoyée par la fonction.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -clavier_tab: le tableau des différents claviers possibles
        -exercice_tab: la tableau des différents exercices possibles
        -stat_tab: le tableau des statistiques
    Retour: Le mode suivant est renvoyée par la fonction.
----------------------------------------------------------
*/
int choix_exercice(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],char exercice_tab[][MAX_CAR],int stat_tab[]){
    int key_type;
    int highlight;
    int mode_suivant=MODE_CHOIX_EXERCICE;
    int etat=ETAT_CHOIX_EXERCICE_INIT;

    return mode_suivant;
}

/*
----------------------------------------------------------
    Fonction: exercice_suivant
    En bref: gère la détermination de l'exercice_suivant
    Description:
        Selon le type d'exercice (EXERCICE_THEORIQUE/EXERCICE_PRATIQUE), fixe le
        mode suivant à MODE_EXERCICE_THEORIQUE ou MODE_EXERCICE_PRATIQUE. Si l'exercice
        excède le nombre d'exercice disponible fixe le mode à MODE_MENU_PRINCIPAL
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -exercice_tab: la tableau des différents exercices possibles
        -stat_tab: le tableau des statistiques
    Retour: Le mode suivant est renvoyée par la fonction.
----------------------------------------------------------
*/
int exercice_suivant(WINDOW* fenetre[],char exercice_tab[][MAX_CAR],int stat_tab[]){
    int mode=MODE_EXERCICE_SUIVANT;

    return mode;
}

/*
----------------------------------------------------------
    Fonction: exercice_pratique
    En bref: gère la détermination de l'exercice_pratique
    Description:
        Gestion des états du mode exercice_pratique de l'initialisation jusqu'à la fin.
        Une ligne de texte à reproduire est affichée. Les entrées du clavier sont analysées
        et colorés en rouge ou vert selon que les caractères sont correctement ou non recopiés.
        A la fin de la ligne, les statistiques sont analysées pour conseiller ou non de passer
        à l'exercice suivant. Selon le choix de l'utilisateur, la fonction fixe le
        mode suivant a MODE_MENU_PRINCIPAL ou MODE_EXERCICE_SUIVANT.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -clavier_tab: le tableau des différents claviers possibles
        -exercice_tab: la tableau des différents exercices possibles
        -stat_tab: le tableau des statistiques
    Retour: Le mode suivant est renvoyée par la fonction.
----------------------------------------------------------
*/
int exercice_pratique(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],char exercice_tab[][MAX_CAR],int stat_tab[]){
    int mode_suivant=MODE_EXERCICE_PRATIQUE;
    int etat=ETAT_EXERCICE_PRATIQUE_INIT;

    // caractéristique d'un exercice lettres/separateurs
    char lettre_tab[MAX_CAR]={0};           // tableau de lettres de l'exercice
    char separateur_tab[MAX_CAR]={0};       // tableau de séparateurs de l'exercice

    // texte a écrire pour compléter un exercice
    char texte_cible[LONGUEUR_LIGNE_PRATIQUE+1]={0};    // ligne de texte à recopier pendant l'exercice

    // capture clavier
    int key_type;         // type de touche
    int key_code;            // code du caractère reçu du clavier


    return mode_suivant;
}

/*
----------------------------------------------------------
    Fonction: exercice_theorique
    En bref: gère la détermination de l'exercice_theorique
    Description:
        Gestion des états du mode exercice_theorique de l'initialisation jusqu'à la fin.
        Les lignes de théorie sont affichées. Selon le choix de l'utilisateur, la fonction fixe
        le mode suivant a MODE_MENU_PRINCIPAL ou MODE_EXERCICE_SUIVANT
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -clavier_tab: le tableau des différents claviers possibles
        -exercice_tab: la tableau des différents exercices possibles
        -stat_tab: le tableau des statistiques
    Retour: Le mode suivant est renvoyée par la fonction.
----------------------------------------------------------
*/
int exercice_theorique(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],char exercice_tab[][MAX_CAR],int stat_tab[]){
    int key_type;
    int mode_suivant=MODE_EXERCICE_THEORIQUE;
    int etat=ETAT_EXERCICE_THEORIQUE_INIT;
    char theorie_tab[MAX_LIGNE_THEORIE][MAX_CAR];   // tableau pour contenir les lignes de théorie d'un exercice


    return mode_suivant;
}


