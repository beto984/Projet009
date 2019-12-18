#ifndef GESTION_MODES_H
#define GESTION_MODES_H

// Module gestion_mode
// Contient l'ensemble des constantes et prototypes des fonctions
// de gestion des principaux modes et états de la machine à états

#define MODE_COMMENCER                  0

#define MODE_QUITTER                    1

#define MODE_MENU_PRINCIPAL             2
#define ETAT_MENU_PRINCIPAL_INIT        20
#define ETAT_MENU_PRINCIPAL_MAJ         21
#define ETAT_MENU_PRINCIPAL_FIN         22

#define MODE_CHOIX_CLAVIER              3
#define ETAT_CHOIX_CLAVIER_INIT         30
#define ETAT_CHOIX_CLAVIER_MAJ          31
#define ETAT_CHOIX_CLAVIER_FIN          33

#define MODE_CHOIX_EXERCICE             4
#define ETAT_CHOIX_EXERCICE_INIT        40
#define ETAT_CHOIX_EXERCICE_MAJ         41
#define ETAT_CHOIX_EXERCICE_SELECT      42
#define ETAT_CHOIX_EXERCICE_FIN         43

#define MODE_EXERCICE_SUIVANT           5

#define MODE_EXERCICE_THEORIQUE         6
#define ETAT_EXERCICE_THEORIQUE_INIT    60
#define ETAT_EXERCICE_THEORIQUE_MAJ     61
#define ETAT_EXERCICE_THEORIQUE_FIN     62

#define MODE_EXERCICE_PRATIQUE          7
#define ETAT_EXERCICE_PRATIQUE_INIT     70
#define ETAT_EXERCICE_PRATIQUE_MAJ      71
#define ETAT_EXERCICE_PRATIQUE_SUCCES   72
#define ETAT_EXERCICE_PRATIQUE_ERREUR   73
#define ETAT_EXERCICE_PRATIQUE_NEXT     74
#define ETAT_EXERCICE_PRATIQUE_ANALYSE  75
#define ETAT_EXERCICE_PRATIQUE_FIN      76

// caractère à afficher lors d'une mauvaise frappe
#define LETTRE_BAD          'X'

// options du menu principal
#define MENU_NB_ITEM        3
#define MENU_CHOIX_CLAVIER  0
#define MENU_CHOIX_EXERCICE 1
#define MENU_QUITTER        2
#define STR_CHOIX_CLAVIER   "Choix de clavier"
#define STR_CHOIX_EXERCICE  "Choix d'exercice"
#define STR_QUITTER         "Quitter"

// les titres a afficher dans la zone Consignes
#define TITRE_MENU_PRINCIPAL    "MENU PRINCIPAL"
#define TITRE_CHOIX_CLAVIER     "CHOIX DE CLAVIER"
#define TITRE_CHOIX_EXERCICE    "CHOIX D'EXERCICE"
#define TITRE_EXE_THEORIQUE     "EXERCICE THEORIQUE"
#define TITRE_EXE_PRATIQUE      "EXERCICE PRATIQUE"
#define TITRE_FIN_EXERCICE      "FIN DE l'EXERCICE"

// certains messages prédéfinis
#define MSG_NAV_MENU            "<FLECHES> -> Naviguer; <ENTER> -> Selectionner; <ESCAPE> -> retour au menu"
#define MSG_NAV_THEORIE         "<Espace> -> Niveau suivant; <ESCAPE> -> retour au menu"
#define MSG_NAV_PRATIQUE        "Entrer les lettres dans l'odre indique; <ESCAPE> -> retour au menu"
#define MSG_NAV_FIN_EXERCICE    "<Espace> -> Meme exercice; <ENTER> -> Niveau suivant; <ESCAPE> -> retour au menu"
#define MSG_TOUCHE_INVALIDE     "Touche invalide !"
#define MSG_CLAVIER_NON_DEFINI  "Definir un clavier avant de choisir l'exercice !"
#define MSG_LECT_EXE_IMPOSSIBLE "Probleme de lecture de fichier pour obtenir les informations d'un exercice !"
#define MSG_LECT_CLV_IMPOSSIBLE "Probleme de lecture de fichier pour obtenir la liste de claviers !"
#define MSG_PERFORMANCE_BAD     "Conseil: Refaire cet exercice pour ameliorer la vitesse et/ou la precision."
#define MSG_PERFORMANCE_GOOD    "Conseil: Passer a l'exercice suivant suite a cette bonne performance !"
#define MSG_TYPE_EXERCICE_BAD   "Type d'exercice inconnu (ni pratique ni theorique)"

// gestion des principaux mode
int menu_principal(WINDOW* fenetre[],char menu_tab[][MAX_CAR],int nb_menu,char clavier_tab[][MAX_CAR],int stat_tab[]);
int choix_clavier(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],int stat_tab[],char nom_fichier_liste_clavier[]);
int choix_exercice(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],char exercice_tab[][MAX_CAR],int stat_tab[]);
int exercice_suivant(WINDOW* fenetre[],char exercice_tab[][MAX_CAR],int stat_tab[]);
int exercice_theorique(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],char exercice_tab[][MAX_CAR],int stat_tab[]);
int exercice_pratique(WINDOW* fenetre[],char clavier_tab[][MAX_CAR],char exercice_tab[][MAX_CAR],int stat_tab[]);

#endif
