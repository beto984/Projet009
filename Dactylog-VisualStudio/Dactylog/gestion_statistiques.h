#ifndef GESTION_STATISTIQUES_H
#define GESTION_STATISTIQUES_H

// Module gestion_statistiques
// Contient l'ensemble des constantes et prototypes des fonctions
// de gestion des statistiques

// Informations contenus dans le tableau de statistiques
#define STAT_CLAVIER_NO         0       // num�ro du clavier s�lectionn� parmi la liste de clavier
#define STAT_CLAVIER_NB         1       // nombre de claviers dans le fichier de liste de clavier
#define STAT_EXERCICE_NO        2       // num�ro d'exercice actuel
#define STAT_EXERCICE_NB        3       // nombre d'exercices pour le clavier s�lectionn�
#define STAT_EXERCICE_TYPE      4       // type d'exercice (EXERCICE_PRATIQUE/EXERCICE_THEORIQUE/EXERCICE_INCONNU)
#define STAT_LETTRE_NB          5       // nombre de lettres pouvant appara�tre dans l'exercice pratique
#define STAT_SEPARATEUR_NB      6       // nombre de caract�res pouvant jouer le r�le de s�parateurs de mots
#define STAT_LONG_MOT_MIN       7       // longueur min d'un mot (pour g�n�ration al�atoire)
#define STAT_LONG_MOT_MAX       8       // longueur max d'un mot (pour g�n�ration al�atoire)
#define STAT_LIGNE_THEO_NB      9       // nombre de ligne de th�orie d'un exerce th�orique
#define STAT_CIBLE_POS          10      // position du curseur dans la ligne cible
#define STAT_SUCCES_NB          11      // nombre de bonnes frappes
#define STAT_ERREUR_NB          12      // nombre d'erreurs de frappe
#define STAT_SECONDE0_NB        13      // Nombre de secondes lors de la frappe de la premi�re lettre de l'exercie
#define STAT_SECONDE1_NB        14      // nombre de secondes lors de la derni�re frappe (temps �coul�=seconde1-seconde0)
#define STAT_MOT_NB             15      // nombre total de mot
#define STAT_LETTRE_NO          16      // num�ro de lettre pour le d�compte de lettres entr�es
#define STAT_MOT_NO             17      // num�ro de mot pour le d�compte de mots entr�s
#define STAT_VITESSE_WPM        18      // nombre de mot par minute
#define STAT_PRECISION_PC       19      // pourcentage de bonne lettre (nb succes/ nb lettre)
#define STAT_TAB_TAILLE         20      // taille du tableau de statistiques

// type de exercice
#define EXERCICE_INCONNU      0
#define EXERCICE_THEORIQUE    1
#define EXERCICE_PRATIQUE     2

// limites � atteindre pour conseiller de passer � l'exercice suivant
#define LIMITE_VITESSE_WPM_MIN  25  // mot par minute min
#define LIMITE_PRECISION_PC_MIN 90  // % de precision min (100%-%erreur)

// prototypes des fonctions d�di�es aux statistiques
void enregistrer_temps(int stat_tab[]);
void reset_statistiques(int stat_tab[]);

#endif
