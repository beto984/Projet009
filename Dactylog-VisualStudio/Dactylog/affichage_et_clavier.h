#ifndef AFFICHAGE_ET_CLAVIER_H
#define AFFICHAGE_ET_CLAVIER_H

// Module affichage_et_clavier
// Contient l'ensemble des constantes et prototypes des fonctions
// de gestion des fenêtres, d'affichage et de captures d'entrées au clavier

#include "curses.h"

// dimension de la fenetre prinpale
#define FENETRE_NL  33
#define FENETRE_NC  100

// différentes zones de la fenetre
#define NB_ZONE             4   // 4 zones dans la fenêtre
#define ZONE_CONSIGNE       0   // zone pour afficher des consignes
#define ZONE_INTERAC        1   // zone d'interaction avec l'utilisateur
#define ZONE_STATIST        2   // zone d'affichage de résultat ou statistiques
#define ZONE_MESSAGE        3   // zone d'affichage de messages (avertissement/conseil)

// les titres des zones

#define ZONE_CONSIGNE_TITRE     "Consignes"
#define ZONE_INTERAC_TITRE      "Interaction"
#define ZONE_STATIST_TITRE      "Statistiques"
#define ZONE_MESSAGE_TITRE      "Message"

// dimensions des zones:
//  NL/NC: nb. de lignes/colonnes
//  L0/C0: position de la ligne/colonne 0
#define ZONE_MESSAGE_NL     3                                   // nb ligne de la zone de message
#define ZONE_MESSAGE_NC     (FENETRE_NC)
#define ZONE_MESSAGE_L0     (ZONE_STATIST_L0+ZONE_STATIST_NL)
#define ZONE_MESSAGE_C0    0
#define ZONE_CONSIGNE_NL    7
#define ZONE_CONSIGNE_NC    (FENETRE_NC)
#define ZONE_CONSIGNE_L0    0
#define ZONE_CONSIGNE_C0    0
#define ZONE_INTERAC_NL     (FENETRE_NL-ZONE_MESSAGE_NL-ZONE_CONSIGNE_NL-ZONE_STATIST_NL)
#define ZONE_INTERAC_NC     (FENETRE_NC)
#define ZONE_INTERAC_L0     (ZONE_CONSIGNE_L0+ZONE_CONSIGNE_NL)
#define ZONE_INTERAC_C0     0
#define ZONE_STATIST_NL     9
#define ZONE_STATIST_NC     (FENETRE_NC)
#define ZONE_STATIST_L0     (ZONE_INTERAC_L0+ZONE_INTERAC_NL)
#define ZONE_STATIST_C0     0

// position de la ligne de texte à recopier dans les exercices pratiques
#define TEXTE_CIBLE_L0      (ZONE_INTERAC_NL/2)
#define TEXTE_CIBLE_C0      (12)

// position de départ pour l'affichage des lignes de théorie
// et nombre max de lignes de théorie affichable
#define TEXTE_THEORIE_L0            2
#define TEXTE_THEORIE_C0            3
#define TEXTE_THEORIE_MAX_L         (ZONE_INTERAC_NL-TEXTE_THEORIE_L0)

#define MAX_CAR     100 // nb max de caractères par ligne dans un fichier

// choix de couleur Noir sur fond rouge / Noir sur fonc vert
#define COULEUR_BAD     20  // paire de couleurs pour les avertissements (noir sur fond rouge)
#define COULEUR_GOOD    21  // paire de couleurs pour le encouragements (noir sur fond vert)

// type de message de feedback (pour le choix de la couleur d'affichage)
#define MSG_TYPE_BAD    0   // message négatif (afficher sur fond rouge)
#define MSG_TYPE_GOOD   1   // message positif (afficher sur fond vert)


// taille maximum du texte de théorie pour entrer dans la fenetre (nombre de lignes max)
#define MAX_LIGNE_THEORIE   (ZONE_INTERAC_NL-2)

// longueur de la ligne de pratique (texte à reproduire)
#define LONGUEUR_LIGNE_PRATIQUE 75
#define CAR_SOUS_LIGNE_PRATIQUE '.'

// quelques types de touches utiles à la navigation
#define TOUCHE_ESPACE                     100
#define TOUCHE_ENTER                      101
#define TOUCHE_ESCAPE                     102
#define TOUCHE_FLECHE_HAUT                103
#define TOUCHE_FLECHE_BAS                 104
#define TOUCHE_AUTRE                      105

// certains codes de caractères spéciaux
#define KEY_ESPACE ' '
#define KEY_ESCAPE 27

// les en-têtes de statistiques
#define STAT_TITRE_CLAVIER          "       clavier:"
#define STAT_TITRE_EXERCICE         "      exercice:"
#define STAT_TITRE_TYPE_PRATIQUE    "          type: Pratique"
#define STAT_TITRE_TYPE_THEORIQUE   "          type: Theorique"
#define STAT_TITRE_TYPE_INCONNU     "          type: Inconnu"

#define STAT_TITRE_NB_LETTRE        "    nb lettres:"
#define STAT_TITRE_NB_SEPARATEUR    "nb separateurs:"
#define STAT_TITRE_NB_LIGNE_THEO    "     nb lignes:"
#define STAT_TITRE_NO_MOT           "           mot:"
#define STAT_TITRE_NO_LETTRE        "        lettre:"
#define STAT_TITRE_NB_CORRECT       "    nb correct:"
#define STAT_TITRE_NB_ERREUR        "     nb erreur:"
#define STAT_TITRE_PRECISION        "     %% correct:"
#define STAT_TITRE_TEMPS            "         temps:"
#define STAT_TITRE_LPM              "lettre par min:"
#define STAT_TITRE_WPM              "   mot par min:"

// position d'affichage des statistiques
#define STAT_L0               2
#define STAT_C0               3       // position de la première col. de stat
#define STAT_C1               35      // position de la seconde col. de stat
#define STAT_C2               70      // position de la troisième col. de stat

#define TEXTE_THEORIE_MAX_L         (ZONE_INTERAC_NL-TEXTE_THEORIE_L0)


// gestion des fenetres
void initialiser_fenetre(WINDOW* fenetre[]);
void quitter_fenetre(WINDOW* fenetre[]);
void clear_fenetre(WINDOW* w,char *titre);

// affichage
void afficher_curseur(WINDOW* zone,int l, int c);
void masquer_curseur(WINDOW* zone);
void afficher_menu(WINDOW* fenetre[],char option_tab[][MAX_CAR],int nb_option,int s);
void afficher_statistiques(WINDOW* fenetre[],char clavier_tab[][MAX_CAR], int stat_tab[]);
void afficher_consignes(WINDOW* fenetre[], char* titre, char* msg);
void afficher_message(WINDOW* fenetre[],char* message, int type);
void clear_message(WINDOW* fenetre[]);
void afficher_texte_cible(WINDOW* fenetre[],char texte_cible[]);
void afficher_exercice_theorique(WINDOW* fenetre[],char theorie_tab[][MAX_CAR], int nb_ligne);
void afficher_lettre(WINDOW* zone,char lettre, int ligne, int col, int couleur);

// analyse des statistiques et affichage des faiblesse en rouge
short analyse_statistiques(WINDOW* fenetre[],int stat_tab[]);

// capture clavier
int obtenir_char(WINDOW* fenetre[]);
int capture_clavier(WINDOW* fenetre[], int *etat);

#endif
