// Module gestion_statistque
// Contient l'ensemble des implémentations des fonctions
// de gestion des statistiques


#include <time.h>       // pour mesurer le temps écoulé avec clock

#include "gestion_statistiques.h"

/*
----------------------------------------------------------
    Fonction: enregistrer_temps
    En bref: enregistre le temps (en secondes) du moment actuel
    Description:
        Enregistrer le temps actuel (en secondes) dans la statistique du temps
        actuel (STAT_SECONDE1_NB).
        S'il s'agit de la première lettre entrée, enregistrer également ce temps
        comme temps initial (STAT_SECONDE0_NB).
        De cette façons, il est possible de calculer le temps écoulé pendant l'exercice
        en faisant la différence entre ces deux temps. Les valeurs sont en secondes.
        Le temps est obtenu par la fonction clock() de la librairie time.h.
        Pour obtenir un temps en seconde il faut diviser le résultat de l'appel par la
        constante CLOCKS_PER_SEC. ex: t=clock()/CLOCKS_PER_SEC;
    Paramètres:
        -stat_tab: le tableau des statistiques ou les temps sont sauvegardés
    Retour: aucun, mais les temps sont enregistrés dans le tableau de statistiques
----------------------------------------------------------
*/
void enregistrer_temps(int stat_tab[]){
    stat_tab[STAT_SECONDE1_NB]=clock()/CLOCKS_PER_SEC;
    if (stat_tab[STAT_LETTRE_NO]==0) // temps au départ
        stat_tab[STAT_SECONDE0_NB]=stat_tab[STAT_SECONDE1_NB];
}

/*
----------------------------------------------------------
    Fonction: reset_statistiques
    En bref: remets les statistiques d'un exercice à 0
    Description:
       Fixe les statistiques de nombre de lettre (STAT_LETTRE_NO), nombre de mot (STAT_MOT_NO)
       succès(STAT_SUCCES_NB) et erreurs(STAT_ERREUR_NB) à 0. Utile lors du démarrage d'un ç
       nouvel exercice.
    Paramètres:
        -stat_tab: le tableau des statistiques
    Retour: aucun, mais les valeurs sont modifiées dans le tableau de statistiques
----------------------------------------------------------
*/
// remettre les statistiques à 0 avant l'écriture d'une ligne
void reset_statistiques(int stat_tab[]){
    stat_tab[STAT_LETTRE_NO]=0;
    stat_tab[STAT_MOT_NO]=0;
    stat_tab[STAT_SUCCES_NB]=0;
    stat_tab[STAT_ERREUR_NB]=0;
}
