/*
 * Programme d'apprentissage de dactylographie
 * David Marche
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>


#include "util.h"                   // la librairie utilitaire générale
#include "affichage_et_clavier.h"   // la librairie d'affichage et de capture de clavier
#include "gestion_statistiques.h"   // la librairie de statistiques
#include "gestion_fichier.h"        // la librairie de lecture de fichiers
#include "gestion_modes.h"          // la librairie de gestion des modes

// nom du fichier contenant la liste des claviers
#define NOM_FICHIER_LISTE_CLAVIER "clavier.lst"



// programme principal de gestion de la machine à états (mode)
int programme_principal(void)
{

    WINDOW *fenetre[NB_ZONE];       // référence aux fenêtres "graphiques"
    int mode=MODE_COMMENCER;        // mode initial de la machine à états
    short fin=FALSE;                // flag pour quitter le programme quand le mode quitter est atteint

    char clavier_tab[MAX_CLAVIER][MAX_CAR]={{0}};     // tableau contenant la liste des claviers possibles
    char exercice_tab[MAX_EXERCICE][MAX_CAR]={{0}};   // tableau avec les titres des exercices
    int stat_tab[STAT_TAB_TAILLE]={0};                // tableau contenant toutes les statistiques

    // tableau contenant les options du menu principal
    int nb_menu=MENU_NB_ITEM;   // taille du tableau
    char menu_tab[][MAX_CAR]=   {   STR_CHOIX_CLAVIER,
                                    STR_CHOIX_EXERCICE,
                                    STR_QUITTER
                                };
    // machine à état qui gère le passage d'un mode à l'autre (modes principaux)
    do{
        switch(mode){
                initialiser_tableau_entier(stat_tab,STAT_TAB_TAILLE,NONE);
                initialiser_fenetre(fenetre);
                mode=MODE_MENU_PRINCIPAL;
                break;
			case MODE_MENU_PRINCIPAL:
				mode = menu_principal(fenetre, menu_tab, nb_menu, clavier_tab, stat_tab);
				break;
			case MODE_CHOIX_CLAVIER:
				mode = choix_clavier(fenetre, clavier_tab, stat_tab, NOM_FICHIER_LISTE_CLAVIER);
				break;
        }
    }while(!fin);

    // fin du programme
    return EXIT_SUCCESS;
}


int main() {

	//return test_rand_entre();
	//return test_genere_texte_aleatoire();
	//return test_charger_item_etoile_fichier();
	return programme_principal();

}