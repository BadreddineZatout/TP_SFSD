/*struct.h
--------


Rôle : définir les prototype des fonctions pour le model de manipulation des fichier (ouvrir, fermer, lireDire ...)
*/
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

    #define TAILLE_BLOC 1024 ///à modifier dans la fin!!!!!!!!

    /*-------Déclaration des structures-------*/

    /*****************TOF*******************/

    typedef struct enreg_TOF
    {
        char date[11];
        char ville[20];
        int temp;
        int eff;
    } enreg_TOF;
    typedef struct Tbloc_TOF
    {
        enreg_TOF tab[TAILLE_BLOC];
        int nb;
    } Tbloc_TOF;
    typedef struct Entete_TOF
    {
        int nbBloc;
        int nbEnreg;
        int nbSupp;
    } Entete_TOF;
    typedef struct TOF
    {
        FILE *file;
        Entete_TOF entete;
    } TOF;

    /*******************TOVC*******************/

    typedef struct enreg_TOVC
    {
        int taille;
        int Caract_effacement;
        int ville;
        char *temp;
        char *date;
    } enreg_TOVC;
    typedef struct Tbloc_TOVC
    {
        char chaine[TAILLE_BLOC+1];
    } Tbloc_TOVC;
    typedef struct Entete_TOVC
    {
        int indice_libre;
        int nbIns;
        int nbSupp;
        int nbBloc;
    } Entete_TOVC;
    typedef struct TOVC
    {
        FILE *fichier;
        Entete_TOVC entete;
    } TOVC;
    typedef struct D
    {
        char taille[10];
        char eff;
        char cle[30];
        char num[3];
    }D;

    /*----------Prototypes des modeles----------*/

    /*****************TOF*******************/

    int ouvrir_TOF(TOF **f,char *chemin,char mode);
    void fermer_TOF(TOF *f);
    void lireDir_TOF(TOF *f,int N_Bloc,Tbloc_TOF *buffer);
    void ecrireDir_TOF(TOF *f,int N_Bloc,Tbloc_TOF *buffer);
    int entete_TOF(TOF *f,int i);
    void aff_entete_TOF(TOF *f, int i, int val);
    int alloc_bloc_TOF(TOF *f);

    /*******************TOVC*******************/

    int ouvrir_TOVC(TOVC **f,char *chemin,char mode);
    void fermer_TOVC(TOVC *f);
    void lireDir_TOVC(TOVC *f,int N_Bloc,Tbloc_TOVC *buffer);
    void ecrireDir_TOVC(TOVC *f,int N_Bloc,Tbloc_TOVC *buffer);
    int entete_TOVC(TOVC *f,int i);
    void aff_entete_TOVC(TOVC *f, int i, int val);
    int alloc_bloc_TOVC(TOVC *f);

    /*--------------------------------------------*/

#endif // STRUCT_H_INCLUDED
