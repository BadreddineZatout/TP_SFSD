/*biblio.h
--------


Rôle : définir les prototype des fonctions
*/
#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include "Struct.h"

    /**----------Prototypes des fonctions----------**/

int verifdate(char *date); ///VERFIER SI LA DATE EST DE FORME JJ/MM/YYYY ET JJ ET MM SONT DIFFERNTS DE 00
void incdate(char *date);  ///RENVOIE LA DATE SUIVANTE DE LA DATE DONNEE
void date_alea(char date[11]);  ///RENVOIE UNE DATE ALEATOIREMENT
int seasonTempe(char *date); ///RENVOIE LES TEMPERATURE SELON LE SAISON
void wilaya(int nbwilaya,char ch[]); ///RENVOIE LE NOM DE WILAYA SELON SA NUMERO
int nbwilaya(char ch[]); ///RENVOIE LE NUMERO DE WILAYA SELON LA WILAYA DONNEE
void CharInit(TOF **f,char nomfichier[30],int n); ///CHARGEMENT INITIALE DE FICHIER TOF
void rech_TOF(TOF *f,TOF **f3,int v,char  nomfichier[30]); ///RECHERCHER DANS LE FICHIER TOF ET CREATION D'UN FICHIER TOF CONTENANT TOUS LES TEMPERATURES D'UN SEUL VILLE
void conversion(TOF *f,TOVC **f2, char  nomfichier[30]); ///CONVERTION DE TOF A TOVC
void recuperer(TOVC *f,int i,int j,D *D,int *cout); ///RENVOIE LES CARACTERISTIQUE D'UN ENREGISTREMENT
void rech_TOVC(TOVC *f,char cle_r[20],int *i,int *j, int *trouv,int *cout); ///RECHERCHER DANS LE FICHIER TOVC
void affichage (TOVC *f, int i, int j,D D,int *cout); ///AFFICHAGE D'UN ENREGISTREMENT
void requete (TOVC *f,int cle1,int cle2); ///LA REQUETE A INTERVALLE
void rech_date(TOVC *f,char date_rech[10],int *i,int *j,int *trouv,D D,int *cout); ///RECHERCHE D'UN DATE DANS LE FICHIER TOVC
void decalbloc(TOVC *f,int nbbloc,int tairest,int taiInser,int *cout); ///FONCTION DE DECALAGE
void inserTOVC(TOVC *f,int nbbloc,int tairest,char ch[35],int *cout); ///INSERER CH DANS UN POSITION DANS UN BLOC
void remplacertai(TOVC *f,int nbbloc,int tairest,char ch[20],D *D,int *cout); ///REMLPACER LA TAILLE DE L'ENREGISTREMENT APRES L'INSERTION
void insertion(TOVC *f,int nbwil,char temp1[3],char date[11]); ///L'INSERTION DANS LE FICHIER TOVC
void welcome();
void choix(); ///Menu de choix

#endif // BIBLIO_H_INCLUDED
