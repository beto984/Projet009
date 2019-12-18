#ifndef UTIL_FICHIER_H
#define UTIL_FICHIER_H

// Module gestion_fichier
// Contient l'ensemble des constantes et prototypes des fonctions
// de gestion de fichier (lecture)

// texte particulier a rechercher dans les fichiers
#define BALISE_PRATIQUE         "- pratique"
#define BALISE_THEORIQUE        "- theorie"
#define BALISE_EXERCICE         "*EXERCICE "
#define BALISE_COMMMENTAIRE     '#'
#define BALISE_ETOILE           '*'

// quelques limites
#define MAX_CAR         100 // nb max de caractères par ligne dans un fichier
#define MAX_CLAVIER     10  // nb max de claviers pouvant être proposés
#define MAX_EXERCICE    100 // nb max de exercice pour apprendre un clavier


// chargement de données à partir de fichiers texte
int charger_item_etoile_fichier(char item_tab[][MAX_CAR],char *nomFichier);
int charger_exercice_theorique(char clavier_tab[][MAX_CAR], int stat_tab[],char theorie_tab[][MAX_CAR]);
int charger_exercice_pratique(char clavier_tab[][MAX_CAR], int stat_tab[],char lettre_tab[],char separateur_tab[]);
int fichier_sauter_commentaires(FILE *file_ptr,char tmp[]);
int determiner_type_exercice(char exercice[]);
#endif
