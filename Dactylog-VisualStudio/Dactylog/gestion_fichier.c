// Module gestion_fichier
// Contient l'ensemble des implémentations des fonctions
// de gestion de fichiers (lecture)

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

 #include <stdio.h>
#include <string.h>

#include "gestion_fichier.h"
#include "util.h"
#include "gestion_statistiques.h"

/*
----------------------------------------------------------
    Fonction: fichier_sauter_commentaires
    En bref: obtenir un ligne d'un fichier en sautant les lignes de commentaires
    Description:
        Permet de lire une ligne d'un fichier mais d'ignorer les lignes de commentaires.
        Une ligne de commentaire commence par le caractère BALISE_COMMMENTAIRE ou un espace.
        La ligne lue se retrouve dans une chaine de caractères (tmp).
    Paramètres:
        -tmp: espace pour stocker la ligne lue
    Retour: 1 en cas de succès de lecture. 0 sinon
----------------------------------------------------------
*/
int fichier_sauter_commentaires(FILE *file_ptr,char tmp[]){
    char *test;
    while((test=fgets(tmp,MAX_CAR, file_ptr))
          &&((*tmp==BALISE_COMMMENTAIRE)
          ||(*tmp==' ')));
    return (test!=NULL);
}

/*
----------------------------------------------------------
    Fonction: charger_exercice_pratique
    En bref: charger toutes les informations d'un exercice pratique d'un fichier
    Description:
        Permet de lire un fichier d'exercice pour se positionner à un exercice donné et
        obtenir toutes les caractéristiques de cet exercice.
        Le fichier à lire est déterminé par l'index dans le tableau de statistiques (STAT_CLAVIER_NO)
        et la liste de noms des claviers (clavier_tab).
        Les lettres de l'exercice sont écrites dans un tableau (lettre_tab),
        les séparateurs sont écrits dans un autre tableau (separateur_tab).
        Le nombre de séparateurs (STAT_SEPARATEUR_NB), le nombre de lettres (STAT_LETTRE_NB),
        la longueur de mot minimum (STAT_LONG_MOT_MIN) et maximum (STAT_LONG_MOT_MAX) sont
        écrits dans le tableau de statistiques (STAT_TAB).
    Paramètres:
        -clavier_tab: le tableau des différents claviers possibles
        -stat_tab: le tableau des statistiques
        -lettre_tab: le tableau des lettres de l'exercice
        -separateur_tab: le tableau des séparateurs de l'exercice
    Retour: VRAI si la lecture du fichier fonctionne. FAUX sinon.
    Paramètres modifiés: stat_tab, clavier_tab, lettre_tab, sepatateur_tab
----------------------------------------------------------
*/
int charger_exercice_pratique(  char clavier_tab[][MAX_CAR], int stat_tab[],
                                char lettre_tab[],char separateur_tab[]){
    FILE *file_ptr;
    char nomFichier[MAX_CAR];
    char* ptr;
    char tmp[MAX_CAR];
    char nom[MAX_CAR];
    short found=FAUX;   // indique si l'exercice est trouvé dans le fichier
    short fin=FAUX;     // indique si la fin du fichier est atteinte
    int resultat=FAUX;
    int i;              // itérateur de boucle


    stat_tab[STAT_EXERCICE_TYPE]=EXERCICE_INCONNU;

    // déterminer le nom du fichier de clavier à ouvrir
    sprintf(nomFichier,"%s",strtok(clavier_tab[stat_tab[STAT_CLAVIER_NO]]," "));

    // générer le nom à chercher pour trouver le exercice dans le fichier
    sprintf(nom,"%s%d",BALISE_EXERCICE,stat_tab[STAT_EXERCICE_NO]);

    // ouvrir le fichier d'un clavier contenant les différents exercices
    file_ptr =fopen(nomFichier, "r");

    // si le fichier à pu être ouvert
    if (file_ptr!=NULL){
        // lire des lignes dans le fichier en ne considérant que celles qui commencent par *
        // jusqu'à atteindre l'exercice voulu
        do{
            if(fgets(tmp,MAX_CAR, file_ptr)){
                if(strstr(tmp, nom)==tmp){
                    found=VRAI;
                }
            }
            else
                fin=VRAI;
        }while(!fin&&!found);

        // si l'exercice est trouvé, charger cet exercice
        if (found){
            if(strstr(tmp,BALISE_PRATIQUE)){
                //sauter les commentaires
                if( (fichier_sauter_commentaires(file_ptr,tmp))
                    &&(2==sscanf(tmp,"%d-%d",&stat_tab[STAT_LONG_MOT_MIN],&stat_tab[STAT_LONG_MOT_MAX]))
                    &&(fichier_sauter_commentaires(file_ptr,tmp))
                    &&(1==sscanf(tmp,"%d:",&stat_tab[STAT_SEPARATEUR_NB]))
                    &&(ptr=strchr(tmp,':'))
                    &&(strlen(++ptr)>=(unsigned int)(stat_tab[STAT_SEPARATEUR_NB]+1))){

                    for(i=0;i<stat_tab[STAT_SEPARATEUR_NB];i++){
                        separateur_tab[i]=ptr[i];
                    }
                    if( (fichier_sauter_commentaires(file_ptr,tmp))
                        &&(1==sscanf(tmp,"%d:",&stat_tab[STAT_LETTRE_NB]))
                        &&(ptr=strchr(tmp,':'))
                        &&(strlen(++ptr)>=(unsigned int)(stat_tab[STAT_LETTRE_NB]+1))){
                        for(i=0;i<stat_tab[STAT_LETTRE_NB];i++){
                                lettre_tab[i]=ptr[i];
                        }
                        stat_tab[STAT_EXERCICE_TYPE]=EXERCICE_PRATIQUE;
                        resultat=VRAI;
                    }
                }
            }
        }
		fclose(file_ptr);
	}

    return  resultat;
}

/*
----------------------------------------------------------
    Fonction: charger_exercice_theorique
    En bref: charger toutes les informations d'un exercice théorique d'un fichier
    Description:
        Permet de lire un fichier d'exercice pour se positionner à un exercice donné et
        obtenir toutes les lignes de théorie de cet exercice.
        Le fichier à lire est déterminé par l'index dans le tableau de statistiques (STAT_CLAVIER_NO)
        et la liste de noms des claviers (clavier_tab).
        Les lignes sont écrites dans un tableau (theorie_tab).
    Paramètres:
        -clavier_tab: le tableau des différents claviers possibles
        -stat_tab: le tableau des statistiques
        -theorie_tab: le tableau des lignes de théorie
    Retour: VRAI si la lecture du fichier fonctionne. FAUX sinon.
    Paramètres modifiés: stat_tab, clavier_tab, theorie_tab
----------------------------------------------------------
*/
int charger_exercice_theorique(char clavier_tab[][MAX_CAR], int stat_tab[],char theorie_tab[][MAX_CAR]){
    FILE *file_ptr;
    char nomFichier[MAX_CAR];
    char tmp[MAX_CAR];
    char nom[MAX_CAR];
    short found=FAUX;  // indique si l'exercice est trouvé dans la fichier
    short fin=FAUX;    // indique si la fin du fichier est atteinte

    // déterminer le nom du fichier de clavier à ouvrir
    sprintf(nomFichier,"%s",strtok(clavier_tab[stat_tab[STAT_CLAVIER_NO]]," "));

    // générer le nom à chercher pour trouver l'exercice dans le fichier
    sprintf(nom,"%s%d",BALISE_EXERCICE,stat_tab[STAT_EXERCICE_NO]);

    // ouvrir le fichier d'un clavier contenant les différents exercices
    file_ptr =fopen(nomFichier, "r");

    // initialiser le nombre de lignes lues
    stat_tab[STAT_LIGNE_THEO_NB]=0;

    // si le fichier à pu être ouvert
    if (file_ptr!=NULL){
        // lire des lignes dans le fichier en ne considérant que celles qui commencent par *
        // jusqu'à atteindre l'exercice voulu
        do{
            if(fgets(tmp,MAX_CAR, file_ptr)){
                if(strstr(tmp, nom)==tmp){
                    found=VRAI;
                }
            }
            else
                fin=VRAI;
        }while(!fin&&!found);

        // si le exercice est trouvé, charger ce exercice
        if (found){
            if (strstr(tmp,BALISE_THEORIQUE)){

                // charger le texte de la théorie dans le tableau
                while((fgets(tmp,MAX_CAR, file_ptr))&&(*tmp!='*')){
                    if ((*tmp!=BALISE_COMMMENTAIRE)&&(*tmp!='\n')&&(*tmp!=' ')){
                            strcpy(theorie_tab[stat_tab[STAT_LIGNE_THEO_NB]++],tmp);
                    }
                }
            }
        }
		fclose(file_ptr);
    }
    return  stat_tab[STAT_LIGNE_THEO_NB];
}

/*
----------------------------------------------------------
    Fonction: charger_item_etoile_fichier
    En bref: lire un fichier texte et charger en mémoire toutes les lignes (items) précédées d'une étoile
    Description:
        Permet de lire un fichier (nomFichier), parcourir chaque ligne pour mémoriser
        uniquement celles qui commencent par une étoile (*, BALISE_ETOILE).
        Chaque ligne ainsi trouvée est ajoutée à un tableau (item_tab).
        (Ce tableau pourra ensuite être utilisé pour créer un menu par exemple).
    Paramètres:
        -item_tab: le tableau ou écrire les lignes trouvées commençant par une étoile
        -nomFichier: le nom du fichier à lire
    Retour: le nombre d'item chargé.
            -1 en cas de problème d'ouverture de fichier.
            0 si aucun item trouvé
    Paramètres modifiés: item_tab
----------------------------------------------------------
*/
int charger_item_etoile_fichier(char item_tab[][MAX_CAR], char* nomFichier) {
	FILE* file_ptr;     // pointeur au fichier
	char tmp[MAX_CAR];  // chaine temporaire pour les lectures du fichier
	int nb = -1;          // nombre de lignes chargées dans le tableau
	short fin = FAUX;    // indicateur d'atteinte de fin du fichier


	// ouvrir le fichier d'un clavier contenant les différents exercices
	file_ptr = fopen(nomFichier, "r");

	// si le fichier n'a pu être ouvert
	if (file_ptr == NULL) {
		return -1;
	}

	// lire des lignes dans le fichier en ne considérant que celle qui commence par *
	// jusqu'à atteindre l'exercice voulu
	do {

		if (fgets(tmp, MAX_CAR, file_ptr)) {
			printf("%c\n", tmp[0]);
		}
		else {
			fin = VRAI;
		}

	} while (!fin);


	fclose(file_ptr);

	// renvoyer le nombre de lignes ajoutées au tableau
	return  nb;
}
int test_charger_item_etoile_fichier() {

	char item_tab[10][MAX_CAR];
	char* nomFichier = "clavier.lst";

	charger_item_etoile_fichier(item_tab, nomFichier);

	system("pause");
}
/*
----------------------------------------------------------
    Fonction: determiner_type_exercice
    En bref: déterminer s'il s'agit d'un exercice pratique ou théorique
    Description:
        Analyse la ligne d'en-tête d'un exercice pour déterminer s'il
        s'agit d'un exercice pratique ou théorique.
        Exemple d'en-tête:
            *EXERCICE 3: lettres fj - pratique
        Si la balise "- pratique" (BALISE_PRATIQUE) est trouvée dans cette ligne,
        il s'agit d'un exercice pratique (EXERCICE_PRATIQUE).
        Si la balise "- theorie" (BALISE_THEORIQUE) est trouvée dans cette ligne,
        il s'agit d'un exercice théorique (EXERCICE_THEORIQUE).
        Si aucune des balises n'est trouvée dans cette ligne,
        il s'agit d'un exercice de type inconnu (EXERCICE_INCONNU)
    Paramètres:
        -exercice: la chaine de caractère décrivant l'exercice (ex:"*EXERCICE 3: lettres fj - pratique")
    Retour: EXERCICE_PRATIQUE/EXERCICE_THEORIQUE/EXERCICE_INCONNU selon la balise trouvée
----------------------------------------------------------
*/
int determiner_type_exercice(char exercice[]){
    int type;
    if (strstr(exercice,BALISE_THEORIQUE)) type=EXERCICE_THEORIQUE;
    else if (strstr(exercice,BALISE_PRATIQUE)) type=EXERCICE_PRATIQUE;
    else type=EXERCICE_INCONNU;
    return type;
}
