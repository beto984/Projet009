// Module affichage_et_clavier
// Contient l'ensemble des implémentation des fonctions
// de gestion des fenêtres, d'affichage et de captures d'entrées au clavier
//

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "curses.h"
#include "gestion_statistiques.h"
#include "affichage_et_clavier.h"
#include "util.h"
#include <string.h>

/*
----------------------------------------------------------
    Fonction: initialiser_fenetre
    En bref: initialise l'affichage "semi graphique"
    Description:
        Initialise la fenêtre avec une division en 4 zones encadrées et
        avec leur titre (Consignes/Interaction/Statistiques/Message). La fonction
        définie également des paire de couleurs (COULEUR_BAD/COULEUR_GOOD) pour des
        affichage futurs
    Paramètres:
        -fenetre: un tableau de pointeurs. Chaque pointeur pointe vers une des 4 zones
    Retour: Aucun, mais les pointeurs aux zones ont été ajustés.
----------------------------------------------------------
*/
void initialiser_fenetre(WINDOW* fenetre[]){

    // configuration
    initscr();              // initialisation pour pdcurses
    cbreak();               // obtenir les entrées du clavier immédiatement (ne pas attendre le ENTER)
    noecho();               // désactiver l'affichage automatique des caractères entrés
    keypad(stdscr, TRUE);   // activer les car. spéciaux (flèche, delete, backspace, ...)
    curs_set(0);            // cacher le curseur

    // activer les couleurs
    start_color();
    init_pair(COULEUR_BAD, COLOR_BLACK,COLOR_RED);
    init_pair(COULEUR_GOOD, COLOR_BLACK,COLOR_GREEN);

    // ajuster la taille de la fenetre principale
    resize_term(FENETRE_NL, FENETRE_NC);

    // par défaut, une fenetre "stdscr" est crée par pdcurses.
    // Il reste à la diviser en 3 zones (info, interaction, statistiques)
    // 1- zone message
    fenetre[ZONE_CONSIGNE]=newwin(ZONE_CONSIGNE_NL, ZONE_CONSIGNE_NC, ZONE_CONSIGNE_L0, ZONE_CONSIGNE_C0);
    clear_fenetre(fenetre[ZONE_CONSIGNE],ZONE_CONSIGNE_TITRE);

    // 2- zone interaction
    fenetre[ZONE_INTERAC]=newwin(ZONE_INTERAC_NL, ZONE_INTERAC_NC, ZONE_INTERAC_L0, ZONE_INTERAC_C0);
    clear_fenetre(fenetre[ZONE_INTERAC],ZONE_INTERAC_TITRE);


    // 3- zone statistiques
    fenetre[ZONE_STATIST]=newwin(ZONE_STATIST_NL, ZONE_STATIST_NC, ZONE_STATIST_L0, ZONE_STATIST_C0);
    clear_fenetre(fenetre[ZONE_STATIST],ZONE_STATIST_TITRE);


    // 3- zone messages
    fenetre[ZONE_MESSAGE]=newwin(ZONE_MESSAGE_NL, ZONE_MESSAGE_NC, ZONE_MESSAGE_L0, ZONE_MESSAGE_C0);
    clear_fenetre(fenetre[ZONE_MESSAGE],ZONE_MESSAGE_TITRE);

}

/*
----------------------------------------------------------
    Fonction: clear_fenetre
    En bref: reset d'une zone
    Description:
        Efface le contenu d'une zone, redessine l'encadrement et
        reaffiche le titre. Permet de vider le contenu de la zone.
    Paramètres:
        -zone: le pointeurs vers la fenêtres (zone) à effacer.
        -titre: le titre de la zone à réafficher après l'effacement du contenu.
    Retour: Aucun
----------------------------------------------------------
*/
void clear_fenetre(WINDOW* zone,char *titre){
    wclear(zone);
    wborder(zone, 0, 0, 0, 0, 0, 0, 0, 0);
    mvwaddstr(zone,0,0, titre);
    wrefresh(zone);
}

/*
----------------------------------------------------------
    Fonction: quitter_fenetre
    En bref: quitter les fenêtres
    Description:
        Supprimer les fenêtres et libérer la mémoire associée.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
    Retour: Aucun
----------------------------------------------------------
*/
void quitter_fenetre(WINDOW* fenetre[]){
    int i;

    // libérer la mémoire associée à chacune des fenêtres (zones)
    for(i=0;i<NB_ZONE;i++){
        delwin(fenetre[i]);
    }

    //delwin(fenetre);
    endwin();
}

/*
----------------------------------------------------------
    Fonction: afficher_menu
    En bref: afficher un menu avec une option surlignée dans la zone d'interaction
    Description:
        Afficher un menu dans la zone d'interation. La liste des options du menu est
        donnée par un tableau (option_tab) et chaque option occupe une ligne d'affichage.
        Une option est surlignée pour indiquer l'item actif du menu. La fonction prend en
        charge le défilement du menu: si l'item à surligner (s) dépasse le nombre de lignes
        affichable, les lignes affichées sont limitées à la place d'affichage disponible et la
        dernière est toujours celle qui est surlignée.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -option_tab: le tableau des options du menu (chaînes de car.)
        -nb_option: le nombre d'option (taille du tableau option_tab)
        -s: l'index de l'optoin à surligner
    Retour: Aucun
----------------------------------------------------------
*/
void afficher_menu(WINDOW* fenetre[], char option_tab[][MAX_CAR], int nb_option, int s){
    int c,l;            // colonne et ligne d'écriture
    int nl;             // nombre de ligne disponible pour l'écriture (pour gérer le scroll)
    int i;              // itérateur de boucle
    int imin=0;         // index min d'affichage (pour scroll)
    int imax=nb_option; // index max d'affichage (pour scroll)

    clear_fenetre(fenetre[ZONE_INTERAC],ZONE_INTERAC_TITRE);

    // colonne et ligne d'affichage
    c=3;
    l=2;
    nl=ZONE_INTERAC_NL-l-3;

    // ajustement des bornes d'affichage
    imin=s-nl+1;
    if (imin<0) imin=0;
    imax=imin+nl;
    if (imax>nb_option) imax=nb_option;

    // affichage des options
    for(i=imin; i<imax; i++){
        if (i==s) wattrset(fenetre[ZONE_INTERAC],A_REVERSE);
        mvwaddstr(fenetre[ZONE_INTERAC],l++,c,option_tab[i]);
        if (i==s) wattrset(fenetre[ZONE_INTERAC],A_NORMAL);
    }

    // mise à jour de l'affichage
    wrefresh(fenetre[ZONE_INTERAC]);

}

/*
----------------------------------------------------------
    Fonction: afficher_exercice_theorique
    En bref: afficher toutes les informations d'un exercice théorique
    Description:
        Afficher les lignes de théorie dans la zone Interaction. Les lignes sont lues
        d'un tableau de chaînes de caractères (theorie_tab). Si le nombre de lignes dépasse
        la capacité d'affichage (TEXTE_THEORIE_MAX_L) les dernières lignes sont ignorées.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -theorie_tab: le tableau des lignes de théorie (chaînes de car.)
        -nb_ligne: le nombre de ligne de théorie (taille du tableau theorie_tab)
    Retour: Aucun
----------------------------------------------------------
*/
void afficher_exercice_theorique(WINDOW* fenetre[], char theorie_tab[][100], int nb_ligne){
    int c,l;            // colonne et ligne d'écriture
    int i;              // itérateur de boucle

    clear_fenetre(fenetre[ZONE_INTERAC],ZONE_INTERAC_TITRE);

    // colonne et ligne d'affichage
    c=TEXTE_THEORIE_C0;
    l=TEXTE_THEORIE_L0;

    // limiter le nombre de ligne à la zone d'affichage
    if (nb_ligne>TEXTE_THEORIE_MAX_L) nb_ligne=TEXTE_THEORIE_MAX_L;

    // affichage des options
    for(i=0; i<nb_ligne; i++){
        mvwaddstr(fenetre[ZONE_INTERAC],l++,c,theorie_tab[i]);
    }

    // mise à jour de l'affichage
    wrefresh(fenetre[ZONE_INTERAC]);

}

/*
----------------------------------------------------------
    Fonction: afficher_consignes
    En bref: afficher les consignes de navigation
    Description:
        Afficher consignes de navigation dans la zone Consignes. Les consignes
        sont données par une chaîne de caractère (msg) et précédés d'un titre affiché
        en gras (titre).
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -titre: le titre à afficher en gras
        -msg: le message aves les consignes à afficher
    Retour: Aucun
----------------------------------------------------------
*/
void afficher_consignes(WINDOW* fenetre[], char* titre, char* msg){

    // afficher les instructions dans la zone de consignes
    clear_fenetre(fenetre[ZONE_CONSIGNE],ZONE_CONSIGNE_TITRE);

    wattrset(fenetre[ZONE_CONSIGNE],A_BOLD);
    mvwaddstr(fenetre[ZONE_CONSIGNE],2,2,titre);
    wattrset(fenetre[ZONE_CONSIGNE],A_NORMAL);

    mvwaddstr(fenetre[ZONE_CONSIGNE],4,5,msg);
    wrefresh(fenetre[ZONE_CONSIGNE]);
}

/*
----------------------------------------------------------
    Fonction: afficher_message
    En bref: afficher un message
    Description:
        Afficher un message dans la zone Message. Le message est donné par
        une chaîne de caractère (message). La couleur du message est spécifié
        par son type (type) soit MSG_TYPE_BAD (pour un affichage sur fond rouge)
        soit MSG_TYPE_GOOD (pour un affichage sur fond vert)
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -message: le message à afficher
        -type: MSG_TYPE_BAD ou MSG_TYPE_GOOD pour ajuster la couleur
    Retour: Aucun
----------------------------------------------------------
*/
void afficher_message(WINDOW* fenetre[],char *message, int type)
{

    clear_fenetre(fenetre[ZONE_MESSAGE],ZONE_MESSAGE_TITRE);

    switch(type){
        case MSG_TYPE_BAD:
            // activer couleur pour les avertissements
            wattrset(fenetre[ZONE_MESSAGE],COLOR_PAIR(COULEUR_BAD));
            break;
        case MSG_TYPE_GOOD:
            // activer couleur pour les conseils/encouragements
            wattrset(fenetre[ZONE_MESSAGE],COLOR_PAIR(COULEUR_GOOD));

            break;
        default:
            // activer couleur pour les autres types (inconnus)
            wattrset(fenetre[ZONE_MESSAGE],COLOR_PAIR(COULEUR_BAD));
    }

    // afficher l'avertissement
    mvwprintw(fenetre[ZONE_MESSAGE],1,2,message);
    wrefresh(fenetre[ZONE_MESSAGE]);


    // désactiver couleur des avertissements
    wattroff(fenetre[ZONE_MESSAGE],COLOR_PAIR(COULEUR_BAD));
    wattroff(fenetre[ZONE_MESSAGE],COLOR_PAIR(COULEUR_GOOD));
}

/*
----------------------------------------------------------
    Fonction: clear_message
    En bref: Efface le message affiché
    Description:
        Vide la zone de Messages
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
    Retour: Aucun
----------------------------------------------------------
*/
void clear_message(WINDOW* fenetre[]){
    clear_fenetre(fenetre[ZONE_MESSAGE],ZONE_MESSAGE_TITRE);
}

/*
----------------------------------------------------------
    Fonction: afficher_statistiques
    En bref: affiche les statistiques
    Description:
        Affiche les statistiques dans la zone Statistiques. La position des affichage
        et les en-têtes des statistiques sont données par des constantes
        (position: STAT_L0,STAT_C... texte: STAT_TITRE...). Les statistiques sont affichés
        seulement si elles ont un sens (le test à commencé, le temps écoulé n'est plus nul)
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -clavier_tab: le tableau des claviers (pour pouvoir afficher le clavier actuel)
        -stat_tab: le tableau des statistiques (données à afficher ou permettant des calculs)
    Retour: Aucun
----------------------------------------------------------
*/
void afficher_statistiques(WINDOW* fenetre[],char clavier_tab[][MAX_CAR], int stat_tab[])
{

    int l=STAT_L0; // ligne d'affichage (en haut de la colonne)

    // vider la fenêtre de statistique puis afficher ...
    clear_fenetre(fenetre[ZONE_STATIST],ZONE_STATIST_TITRE);

    // le clavier
    if (stat_tab[STAT_CLAVIER_NO]!=NONE)
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0,STAT_TITRE_CLAVIER " %s",strtok(clavier_tab[stat_tab[STAT_CLAVIER_NO]]," "));


    if ((stat_tab[STAT_EXERCICE_NO]>=0)&&(stat_tab[STAT_EXERCICE_NO]<=stat_tab[STAT_EXERCICE_NB])){
        // le exercice
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0,STAT_TITRE_EXERCICE " %d/%d",stat_tab[STAT_EXERCICE_NO],stat_tab[STAT_EXERCICE_NB]-1);
        // le type
        switch(stat_tab[STAT_EXERCICE_TYPE]){
            case EXERCICE_PRATIQUE:
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0,STAT_TITRE_TYPE_PRATIQUE);
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0,STAT_TITRE_NB_LETTRE " %d",stat_tab[STAT_LETTRE_NB]);
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0,STAT_TITRE_NB_SEPARATEUR " %d",stat_tab[STAT_SEPARATEUR_NB]);
                break;
            case EXERCICE_THEORIQUE:
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0, STAT_TITRE_TYPE_THEORIQUE);
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0, STAT_TITRE_NB_LIGNE_THEO " %d",stat_tab[STAT_LIGNE_THEO_NB]);
                break;
            case EXERCICE_INCONNU:
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0, STAT_TITRE_TYPE_INCONNU);
                break;
            default:
                mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C0, STAT_TITRE_TYPE_INCONNU);
                break;
        }
    }


    // statistique d'erreur et succes et vitesses de frappe
    if ((stat_tab[STAT_SUCCES_NB]+stat_tab[STAT_ERREUR_NB])>0){
        l=STAT_L0;  // revenir en haut de lal colonne d'affichage
        stat_tab[STAT_PRECISION_PC]=100*stat_tab[STAT_SUCCES_NB]/(stat_tab[STAT_SUCCES_NB]+stat_tab[STAT_ERREUR_NB]);
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C1, STAT_TITRE_NO_MOT " %3d",stat_tab[STAT_MOT_NO]);
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C1, STAT_TITRE_NO_LETTRE " %3d",stat_tab[STAT_LETTRE_NO]);
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C1, STAT_TITRE_NB_CORRECT " %3d",stat_tab[STAT_SUCCES_NB]);
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C1, STAT_TITRE_NB_ERREUR " %3d",stat_tab[STAT_ERREUR_NB]);
        mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C1, STAT_TITRE_PRECISION " %3d (%%)",stat_tab[STAT_PRECISION_PC]);

        int temps=stat_tab[STAT_SECONDE1_NB]-stat_tab[STAT_SECONDE0_NB];
        if (temps>0){
            l=STAT_L0;  // revenir en haut de lal colonne d'affichage
            stat_tab[STAT_VITESSE_WPM]=60*stat_tab[STAT_MOT_NO]/temps;
            mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C2, STAT_TITRE_TEMPS " %4d (s)",temps);
            mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C2, STAT_TITRE_LPM " %4d (LPM)",60*stat_tab[STAT_LETTRE_NO]/temps);
            mvwprintw(fenetre[ZONE_STATIST],l++,STAT_C2, STAT_TITRE_WPM " %4d (WPM)",stat_tab[STAT_VITESSE_WPM]);
        }
    }
    wrefresh(fenetre[ZONE_STATIST]);

}

/*
----------------------------------------------------------
    Fonction: analyse_statistiques
    En bref: analyse les statistiques après un exercice pratique
    Description:
        Analyse les statistique de précicion et de vitesse pour savoir s'il faut conseiller
        de passer à l'exercice suivant. Si la précision ne dépasse pas la limite
        (LIMITE_PRECISION_PC_MIN) ou que la vitesse est inférieure à la limite (LIMITE_VITESSE_WPM_MIN),
        l'exercice devrait être refait (fonction renvoie FAUX). Si les deux limites sont respectées,
        l'exercice est considéré réussi (fonction renvoie VRAI). La fonction s'occuppe également
        de surligner en rouge les performances insuffisantes (vitesse et/ou précision).
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -stat_tab: le tableau des statistiques (données pour comparer aux limites)
    Retour: VRAI si les limites de performances (vitesse et précision) sont dépassées, FAUX sinon
----------------------------------------------------------
*/
short analyse_statistiques(WINDOW* fenetre[],int stat_tab[]){

    int good=VRAI;  // supposer que tout est bon.

    if (stat_tab[STAT_VITESSE_WPM]<LIMITE_VITESSE_WPM_MIN){
        good=FAUX;  // vitesse insufisante
        wattrset(fenetre[ZONE_STATIST],COLOR_PAIR(COULEUR_BAD));
        mvwprintw(fenetre[ZONE_STATIST],STAT_L0+2,STAT_C2, STAT_TITRE_WPM " %4d (WPM)",stat_tab[STAT_VITESSE_WPM]);
        wattroff(fenetre[ZONE_STATIST],COLOR_PAIR(COULEUR_BAD));
        wrefresh(fenetre[ZONE_STATIST]);
    }

    if (stat_tab[STAT_PRECISION_PC]<LIMITE_PRECISION_PC_MIN){
        good=FAUX;  // précision insuffisante
        wattrset(fenetre[ZONE_STATIST],COLOR_PAIR(COULEUR_BAD));
        mvwprintw(fenetre[ZONE_STATIST],STAT_L0+4,STAT_C1, STAT_TITRE_PRECISION " %3d (%%)",stat_tab[STAT_PRECISION_PC]);

        wattroff(fenetre[ZONE_STATIST],COLOR_PAIR(COULEUR_BAD));
        wrefresh(fenetre[ZONE_STATIST]);
    }

    return good;
}

/*
----------------------------------------------------------
    Fonction: afficher_lettre
    En bref: afficher une lettre dans la couleur donnée a la colonne donnée
    Description:
        Affiche une seule lette dans la zone demandée (zone) et dans la couleur
        demandée (couleur) à la position spécifiée par la ligne (l) et la colonne (c)
    Paramètres:
        -zone: pointeur à la fenêtre ou l'affichage doit avoir lieu (zone)
        -lettre: le caractère à afficher (ex:'a' ou son code ascii)
        -l: ligne d'affichage
        -c: colonnne d'affichage
        -couleur: couleur d'affichage (COULEUR_GOOD/COULEUR_BAD)
    Retour: aucun
----------------------------------------------------------
*/
void afficher_lettre(WINDOW* zone,char lettre, int l,int c, int couleur){
    wmove(zone, l, c);                  // déplacer le curseur à la position voulue
    wattrset(zone,COLOR_PAIR(couleur)); // fixer la couleur pour cette affichage
    waddch(zone,lettre);                // ajouter le caractère
    wattroff(zone,COLOR_PAIR(couleur)); // remettre la couleur d'origine
    wrefresh(zone);                     // mettre à jour l'affichage avec le nouveau car.
}

/*
----------------------------------------------------------
    Fonction: afficher_texte_cible
    En bref: afficher le texte cible qui doit être recopié dans un exercice pratique
    Description:
        Affiche le texte à recopier lors de l'exercice pratique dans la zone d'interaction.
        Le texte est affiché à la position TEXTE_CIBLE_L0,TEXTE_CIBLE_C0. Une ligne est
        également affichée sous ce texte pour visualiser les endroits qui doivent être
        rempli lors de l'exercice pratique. Le car. utilisé pour cette deuxième ligne est
        CAR_SOUS_LIGNE_PRATIQUE.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -texte_cible: la chaîne de caractères qui doit être recopiée pendant l'exercice
    Retour: aucun
----------------------------------------------------------
*/
void afficher_texte_cible(WINDOW* fenetre[],char texte_cible[]){
    int i;  // itérateur de boucle

    // afficher le texte a écrire dans la zone d'interaction
    clear_fenetre(fenetre[ZONE_INTERAC],ZONE_INTERAC_TITRE);
    wattrset(fenetre[ZONE_INTERAC],A_BOLD);
    mvwaddstr(fenetre[ZONE_INTERAC],TEXTE_CIBLE_L0,TEXTE_CIBLE_C0,texte_cible);
    wattrset(fenetre[ZONE_INTERAC],A_NORMAL);
    wmove(fenetre[ZONE_INTERAC], TEXTE_CIBLE_L0+1, TEXTE_CIBLE_C0);

    for(i=0;i<LONGUEUR_LIGNE_PRATIQUE;i++){
       waddch(fenetre[ZONE_INTERAC],CAR_SOUS_LIGNE_PRATIQUE);
    }
    wrefresh(fenetre[ZONE_INTERAC]);

}

/*
----------------------------------------------------------
    Fonction: afficher_curseur
    En bref: montrer le curseur
    Description:
        Affiche le curseur dans un format très visible (rectangle clignotant) dans la
        zone spécifiée (zone) et à la position spécifiée par la ligne (l) et la colonne (c)
    Paramètres:
        -zone: pointeur à la fenêtre ou le curseur doit être affiché
        -l: ligne ou le curseur doit être affiché
        -c: colonnne ou le curseur doit être affiché
    Retour: aucun
----------------------------------------------------------
*/
void afficher_curseur(WINDOW* zone,int l, int c){
    // placer le curseur et le rendre visible
    wmove(zone, l, c);  // déplacer le curseur à la position voulue
    curs_set(2);        // un rectangle plein
    wrefresh(zone);     // mettre à jour l'affichage
}

/*
----------------------------------------------------------
    Fonction: masquer_curseur
    En bref: masquer le curseur
    Description:
        Masque le curseur qui était probablement rendu visible par la fonction affiche_curseur.
    Paramètres:
        -zone: pointeur à la fenêtre ou le curseur était affiché et doit maintenant être masqué
    Retour: aucun
----------------------------------------------------------
*/
void masquer_curseur(WINDOW* zone){
   // masquer le curseur
    curs_set(0);
    wrefresh(zone);
}

/*
----------------------------------------------------------
    Fonction: obtenir_char
    En bref: obtenir un caractère du clavier
    Description:
        Lire un caractère du clavier dans la zone Interaction.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
    Retour: aucun
----------------------------------------------------------
*/
int obtenir_char(WINDOW* fenetre[]){
    int key;

    // configurer l'entrée clavier
    noecho();               // ne pas afficher les caractères reçus du clavier
    cbreak();               // rendre les entrées directement sans attendre <enter>
    keypad(fenetre[ZONE_INTERAC], TRUE);   // activer les touches spéciales (flèches)
    raw();

    // attendre une entrée du clavier et obtenir la touche enfoncée
    key = wgetch(fenetre[ZONE_INTERAC]);
    //key = getch();

    return key;
}

/*
----------------------------------------------------------
    Fonction: capture_clavier
    En bref: obtenir un caractère du clavier avec son code et son type
    Description:
        Lire un caractère du clavier dans la zone Interaction. La touche du clavier est
        analysé pour obtenir le type de touche (type) et le code ascii de la touche (key).
        Le type est un de ceux-ci:
            TOUCHE_FLECHE_HAUT
            TOUCHE_FLECHE_BAS
            TOUCHE_ENTER
            TOUCHE_ESCAPE
            TOUCHE_ESPACE
            TOUCHE_AUTRE
        Le code est utile surtout dans le cas ou le type déterminé est TOUCHE_AUTRE.
    Paramètres:
        -fenetre: le tableau des fenêtres (zones)
        -type: type de caractère (pointeur)
    Retour: le code de la touche obtenu (le type est aussi fixé grâce au pointeur)
----------------------------------------------------------
*/
int capture_clavier(WINDOW* fenetre[],int *type){

    int key;    // touche enfoncée par l'utilisateur
    key = obtenir_char(fenetre);

    // selon la touche ajuster la valeur du choix/etat
    switch(key){
        case KEY_UP:
            *type=TOUCHE_FLECHE_HAUT;
            break;
        case KEY_DOWN:
            *type=TOUCHE_FLECHE_BAS;
            break;
        case 10:
        case 13:
        case KEY_ENTER:
            *type=TOUCHE_ENTER;
            break;
        case KEY_ESCAPE:
            *type=TOUCHE_ESCAPE;
            break;
        case KEY_ESPACE:
            *type=TOUCHE_ESPACE;
            break;
        default:
            *type=TOUCHE_AUTRE;
    }
    return key;
}

