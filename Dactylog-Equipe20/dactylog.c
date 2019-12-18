/*
 * Programme d'apprentissage de dactylographie
 * David Marche
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>


#include "util.h"
#include "affichage_et_clavier.h"
#include "gestion_statistiques.h"
#include "gestion_fichier.h"
#include "gestion_modes.h"

#define NOM_FICHIER_LISTE_CLAVIER "clavier.lst"

int main(void)
{

    WINDOW *fenetre[NB_ZONE];
    int mode=MODE_COMMENCER;
    short fin=FALSE;

    char clavier_tab[MAX_CLAVIER][MAX_CAR]={{0}};
    char exercice_tab[MAX_EXERCICE][MAX_CAR]={{0}};
    int stat_tab[STAT_TAB_TAILLE]={0};

    int nb_menu=MENU_NB_ITEM;
    char menu_tab[][MAX_CAR]=   {   STR_CHOIX_CLAVIER,
                                    STR_CHOIX_EXERCICE,
                                    STR_QUITTER
                                };
    do{
        switch(mode){

            case MODE_COMMENCER:
                initialiser_tableau_entier(stat_tab,STAT_TAB_TAILLE,NONE);
                initialiser_fenetre(fenetre);
                mode=MODE_MENU_PRINCIPAL;
                break;
            case MODE_MENU_PRINCIPAL:
                mode=menu_principal(fenetre,menu_tab,nb_menu,clavier_tab,stat_tab);
                break;
            case MODE_CHOIX_CLAVIER:
                mode=choix_clavier(fenetre,clavier_tab,stat_tab, NOM_FICHIER_LISTE_CLAVIER);
                break;
            case MODE_CHOIX_EXERCICE:
                mode=choix_exercice(fenetre,clavier_tab,exercice_tab,stat_tab);
                break;
            case MODE_EXERCICE_SUIVANT:
                mode=exercice_suivant(fenetre,exercice_tab,stat_tab);
                break;
            case MODE_EXERCICE_THEORIQUE:
                mode=exercice_theorique(fenetre,clavier_tab,exercice_tab,stat_tab);
                break;
            case MODE_EXERCICE_PRATIQUE:
                mode=exercice_pratique(fenetre,clavier_tab,exercice_tab,stat_tab);
                break;
            case MODE_QUITTER:
                quitter_fenetre(fenetre);
                fin = VRAI;

        }
    }while(!fin);

    return EXIT_SUCCESS;
}








