/*
modele.c
--------


Rôle : définir le model de manipulation des file (ouvrir, fermer, lireDire ...)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/**--------------Les Modeles Des Fichiers TOF--------------**/

/*--------------Fonction d'ouverture d'un fichier--------------*/

int ouvrir_TOF(TOF **f,char *chemin,char mode)
{
    *f = malloc(sizeof(TOF));
    char s[3];

    if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
    else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
    else return 0;

    (*f)->file = fopen(chemin, s);
    if((*f)->file == NULL)   return 0;

    if((mode == 'A') || (mode == 'a'))
    {
        fread(&((*f)->entete), sizeof(Entete_TOF), 1, (*f)->file);
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        (*f)->entete.nbBloc = 0;
        (*f)->entete.nbEnreg = 0;
        (*f)->entete.nbSupp = 0;
    }
    return 1;
}
/*--------------------------------------------------------------*/

/*--------------Fonction de fermeture d'un fichier--------------*/

void fermer_TOF(TOF *f)
{
    //Sauvegarde de l'entête
    rewind(f->file);
    fwrite(&(f->entete), sizeof(Entete_TOF), 1, f->file);
    fclose(f->file);
    free(f);
}
/*--------------------------------------------------------------*/

/*-----------------Fonction de lecture d'un bloc----------------*/

void lireDir_TOF(TOF *f,int N_Bloc,Tbloc_TOF *buffer)
{
    int v;
    if(N_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->file, sizeof(Entete_TOF) + (N_Bloc-1) * sizeof(Tbloc_TOF),SEEK_SET);
        v=fread(buffer, 1, sizeof(Tbloc_TOF), f->file);
        if (v==0) printf("erreur_lire_TOF");
    }
}
/*--------------------------------------------------------------*/

/*-----------------Fonction d'écriture d'un bloc----------------*/

void ecrireDir_TOF(TOF *f,int N_Bloc,Tbloc_TOF *buffer)
{
    int v;
    if(N_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->file, sizeof(Entete_TOF) + (N_Bloc-1) * sizeof(Tbloc_TOF),SEEK_SET);
        v=fwrite(buffer, 1, sizeof(Tbloc_TOF), f->file);
        if (v==0) printf("erreur_ecr_TOF");
    }
}
/*--------------------------------------------------------------*/

/*----------------Fonction de lecture de l'entête---------------*/

/* lorsque i=1 ====> lecture de nombre des bloc
   lorsque i=2 ====> lecture du nombre d'enregistrement
   lorsque i=3 ====> lecture de nombre des enregistrement supprimés */

int entete_TOF(TOF *f,int i)
{
    if(i == 1) return (f->entete).nbBloc;
    else if(i == 2) return (f->entete).nbEnreg;
    else if(i == 3) return (f->entete).nbSupp;
    else return -1;
}
/*--------------------------------------------------------------*/

/*-------------Fonction de modification de l'entête-------------*/

/* lorsque i=1 ====> modification de nombre des bloc
   lorsque i=2 ====> modification du nombre d'enregistrement
   lorsque i=3 ====> modification de nombre des enregistrement supprimés */

void aff_entete_TOF(TOF *f, int i, int val)
{
    if(i == 1) (f->entete).nbBloc = val;
    else if(i == 2) (f->entete).nbEnreg = val;
    else if(i == 3) (f->entete).nbSupp = val;
}
/*--------------------------------------------------------------*/

/*--------------------L'allocation d'un bloc--------------------*/

int alloc_bloc_TOF(TOF *f)
{
    aff_entete_TOF(f,1,entete_TOF(f,1)+1);
    return entete_TOF(f,1);
}


/**--------------Les Modeles Des Fichiers TOVC--------------**/


/*--------------Fonction d'ouverture d'un fichier--------------*/

int ouvrir_TOVC(TOVC **f,char *chemin,char mode)
{
    *f = malloc(sizeof(TOVC));
    char s[3];

    if((mode == 'A') || (mode == 'a')) sprintf(s,"rb+");
    else if ((mode == 'N') || (mode == 'n')) sprintf(s,"wb+");
    else return 0;

    (*f)->fichier = fopen(chemin, s);
    if((*f)->fichier == NULL)   return 0;

    if((mode == 'A') || (mode == 'a'))
    {
        fread(&((*f)->entete), sizeof(Entete_TOVC), 1, (*f)->fichier);
    }
    else if ((mode == 'N') || (mode == 'n'))
    {
        (*f)->entete.indice_libre = 0;
        (*f)->entete.nbIns = 0;
        (*f)->entete.nbSupp = 0;
        (*f)->entete.nbBloc = 0;
    }
    return 1;
}
/*--------------------------------------------------------------*/

/*--------------Fonction de fermeture d'un fichier--------------*/

void fermer_TOVC(TOVC *f)
{
    //Sauvegarde de l'entête
    rewind(f->fichier);
    fwrite(&(f->entete), sizeof(Entete_TOVC), 1, f->fichier);
    fclose(f->fichier);
    free(f);
}
/*--------------------------------------------------------------*/

/*-----------------Fonction de lecture d'un bloc----------------*/

void lireDir_TOVC(TOVC *f,int N_Bloc,Tbloc_TOVC *buffer)
{
    int v;

    if(N_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOVC) + (N_Bloc-1) * sizeof(Tbloc_TOVC),SEEK_SET);
        v=fread(buffer, 1, sizeof(Tbloc_TOVC), f->fichier);
        if (v==0) printf("erreur_lire_TOVC");
    }
}
/*--------------------------------------------------------------*/

/*-----------------Fonction d'écriture d'un bloc----------------*/

void ecrireDir_TOVC(TOVC *f,int N_Bloc,Tbloc_TOVC *buffer)
{
    int v;
    if(N_Bloc <= (f->entete).nbBloc)
    {
        fseek(f->fichier, sizeof(Entete_TOVC) + (N_Bloc-1) * sizeof(Tbloc_TOVC),SEEK_SET);
        v=fwrite(buffer, 1, sizeof(Tbloc_TOVC), f->fichier);
        if (v==0) printf("erreur_ecr_TOVC");
    }
}
/*--------------------------------------------------------------*/

/*----------------Fonction de lecture de l'entête---------------*/

/* lorsque i=1 ====> lecture d'indice libre
   lorsque i=2 ====> lecture du nombre d'enregistrements insérés
   lorsque i=3 ====> lecture de nombre d'enregistrements supprimés
   lorsque i=4 ====> lecture de nombre des bloc */

int entete_TOVC(TOVC *f,int i)
{
    if(i == 1) return (f->entete).indice_libre;
    else if(i == 2) return (f->entete).nbIns;
    else if(i == 3) return (f->entete).nbSupp;
    else if(i == 4) return (f->entete).nbBloc;
    else return -1;
}
/*--------------------------------------------------------------*/

/*-------------Fonction de modification de l'entête-------------*/
/* lorsque i=1 ====> modification d'indice libre
   lorsque i=2 ====> modification du nombre d'enregistrement
   lorsque i=3 ====> modification de nombre des enregistrement supprimés
   lorsque i=4 ====> modification de nombre des bloc */

void aff_entete_TOVC(TOVC *f, int i, int val)
{
    if(i == 1) (f->entete).indice_libre = val;
    else if(i == 2) (f->entete).nbIns = val;
    else if(i == 3) (f->entete).nbSupp = val;
    else if(i == 4) (f->entete).nbBloc = val;
}
/*--------------------------------------------------------------*/

/*--------------------L'allocation d'un bloc--------------------*/
int alloc_bloc_TOVC(TOVC *f)
{
    aff_entete_TOVC(f,1,entete_TOVC(f,1)+1);
    return entete_TOVC(f,1);
}
