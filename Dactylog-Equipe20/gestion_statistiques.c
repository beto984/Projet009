// Module gestion_statistque
// Contient l'ensemble des impl�mentations des fonctions
// de gestion des statistiques


#include <time.h>       // pour mesurer le temps �coul� avec clock

#include "gestion_statistiques.h"

/*
----------------------------------------------------------
    Fonction: enregistrer_temps
    En bref: enregistre le temps (en secondes) du moment actuel
    Description:
        Enregistrer le temps actuel (en secondes) dans la statistique du temps
        actuel (STAT_SECONDE1_NB).
        S'il s'agit de la premi�re lettre entr�e, enregistrer �galement ce temps
        comme temps initial (STAT_SECONDE0_NB).
        De cette fa�ons, il est possible de calculer le temps �coul� pendant l'exercice
        en faisant la diff�rence entre ces deux temps. Les valeurs sont en secondes.
        Le temps est obtenu par la fonction clock() de la librairie time.h.
        Pour obtenir un temps en seconde il faut diviser le r�sultat de l'appel par la
        constante CLOCKS_PER_SEC. ex: t=clock()/CLOCKS_PER_SEC;
    Param�tres:
        -stat_tab: le tableau des statistiques ou les temps sont sauvegard�s
    Retour: aucun, mais les temps sont enregistr�s dans le tableau de statistiques
----------------------------------------------------------
*/
void enregistrer_temps(int stat_tab[]){
    stat_tab[STAT_SECONDE1_NB]=clock()/CLOCKS_PER_SEC;
    if (stat_tab[STAT_LETTRE_NO]==0) // temps au d�part
        stat_tab[STAT_SECONDE0_NB]=stat_tab[STAT_SECONDE1_NB];
}

/*
----------------------------------------------------------
    Fonction: reset_statistiques
    En bref: remets les statistiques d'un exercice � 0
    Description:
       Fixe les statistiques de nombre de lettre (STAT_LETTRE_NO), nombre de mot (STAT_MOT_NO)
       succ�s(STAT_SUCCES_NB) et erreurs(STAT_ERREUR_NB) � 0. Utile lors du d�marrage d'un �
       nouvel exercice.
    Param�tres:
        -stat_tab: le tableau des statistiques
    Retour: aucun, mais les valeurs sont modifi�es dans le tableau de statistiques
----------------------------------------------------------
*/
// remettre les statistiques � 0 avant l'�criture d'une ligne
void reset_statistiques(int stat_tab[]){
   stat_tab[STAT_LETTRE_NO]=0;
   stat_tab[STAT_MOT_NO]=0;
   stat_tab[STAT_SUCCES_NB]=0;
   stat_tab[STAT_ERREUR_NB]=0;
}
