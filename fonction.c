/*
fonction.c
--------


Rôle : définir les fonctions
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "biblio.h"
#include "Struct.h"
int verifdate(char *date)
{
    char ch[11]="xx/xx/xxxx";
    if (strlen(ch)!=strlen(date)) {printf("la taille de date est différent de xx/xx/xxxx \n");return 0;}
    else
    {
        if ((date[0]=='0')&&(date[1]=='0')) {printf("\n\n\t\terreur dans la jour\n");return 0;}
        if ((date[0]>'3')||(date[0]<'0')) {printf("\n\n\t\terreur dans la jour\n");return 0;}
        if ((date[1]>'9')||(date[1]<'0')) {printf("\n\n\t\terreur dans la jour\n");return 0;}
        if (date[2]!='/') {printf("\n\n\t\ts'il vous plait écrivez '/' \n");return 0;}
        if ((date[3]=='0')&&(date[4]=='0')) {printf("\n\n\t\terreur dans le mois\n");return 0;}
        if ((date[3]>'1')||(date[3]<'0')) {printf("\n\n\t\terreur dans la mois\n");return 0;}
        if ((date[4]>'9')||(date[4]<'0')) {printf("\n\n\t\terreur dans la mois\n");return 0;}
        if (date[5]!='/') {printf("\n\n\t\ts'il vous plait écrivez '/' \n");return 0;}
        if ((date[6]>'9')||(date[6]<'0')) {printf("\n\n\t\terreur dans l'année\n");return 0;}
        if ((date[7]>'9')||(date[7]<'0')) {printf("\n\n\t\terreur dans l'année\n");return 0;}
        if ((date[8]>'9')||(date[8]<'0')) {printf("\n\n\t\terreur dans l'année\n");return 0;}
        if ((date[9]>'9')||(date[9]<'0')) {printf("\n\n\t\terreur dans l'année\n");return 0;}
        return 1;
    }
}

///**********************************************************************************

void incdate(char *date)
{
                    /**VARIABLES**/

    char year[6];
    int annee,i=0,j=0,t[8],mois,jour;
                    /**CORPS**/
    while (i<11)
    {
      if ((i!=2)&&(i!=5) )  {t[j]=date[i]-48;j++;} i++;
    }
        mois=t[2]*10+t[3];
        jour=t[0]*10+t[1];
        annee=t[4]*1000+t[5]*100+t[6]*10+t[7];

    if ((t[2]==0)&&(t[3]==2))   /** pour le cas fevrier **/
    {
        date[1]++;
        if (annee%4==0)
        {
            if (date[1]>'9') {date[1]='0';date[0]++;}
            if ((date[1]=='0')&& (date[0]=='3')){date[1]='1';date[0]='0';date[3]='0';date[4]='3';}
        }else
        {
            if ((date[1]=='9')&& (date[0]=='2')) {date[1]='0';date[0]++;}
            else {if (date[1]>'9') {date[0]++;date[1]='0';}}
            if ((date[1]=='0')&& (date[0]=='3')){date[1]='1';date[0]='0';date[3]='0';date[4]='3';}
        }
    }
    else        /**le cas de 31 jour de mois**/
    {
        if (((mois<8)&&(mois%2==1))||((mois>=8)&&(mois%2==0)))
        {
            date[1]++;
            if (date[1]>'9'){date[0]++;date[1]='0';}
            if (jour==31) {date[1]='1';date[0]='0';date[4]++;}
            if (date[4]>'9') {date[3]='1';date[4]='0';}
            if ((date[3]=='1')&&(date[4]=='3')&& (jour==31))
            {
               date[3]='0';date[4]='1';
               annee++;
               sprintf(year,"%d",annee);
               strncpy(date,date,6);
               date[6]='\0';
               strcat(date,year);
            }
        }
        else        /**le cas de 30 jour de mois**/
        {
            date[1]++;
            if (date[1]>'9'){date[0]++;date[1]='0';}
            if (jour==30)
            {
                date[1]='1';date[0]='0';
                if (date[4]=='9') {date[4]='0';date[3]='1';}
                else date[4]++;
            }
        }
    }
}

///**********************************************************************************

void date_alea(char date[11])
{
    srand(time(0)+rand()%10);
    int jour,mois,annee;
    char j[3],m[3],a[5];
    annee=2020;
    mois=rand()%12+1;
    annee=annee-20+rand()%40;
    if (mois<10) {m[0]='0',m[1]=mois+48;m[2]='\0';}
    else sprintf(m,"%d",mois);

    if (((mois<=7)&&(mois%2==1))||((mois>=8)&&(mois%2==0)))
    {
        jour=rand()%31+1;
    }
    else  jour=rand()%30+1;

    if (jour<10) {j[0]='0',j[1]=jour+48;}
    else sprintf(j,"%d",jour);
    a[0]=48+(annee/1000);
    a[1]=48+(annee/100)%10;
    a[2]=48+(annee/10)%10;
    a[3]=48+annee%10;
    a[4]='\0';
    strcpy(date,j); strcat(date,"/");
    strcat(date,m); strcat(date,"/");
    strcat(date,a);
}

///**********************************************************************************

int seasonTempe(char *date)
{
    int mois;
    mois=(date[3]-48)*10+date[4]-48;
    if ((mois>=3)&&(mois<=5)) return rand()%21+10;
    if ((mois>=6)&&(mois<=8)) return rand()%26+25;
    if ((mois>=9)&&(mois<=11)) return rand()%11+5;
    return rand()%20-9;
}

///**********************************************************************************

void wilaya(int nbwilaya,char ch[])
{
    FILE *w=fopen("leswilaya.txt","r");
    fseek(w,0,SEEK_SET);
    int j=0;
    char c[20];
    while (j<nbwilaya)
    {
        j++;
        fscanf(w,"%s",c);
    }
    strcpy(ch,c);
    fclose(w);
}

///**********************************************************************************

int nbwilaya(char ch[])
{
    FILE *w=fopen("leswilaya.txt","r");
    int j=0,trouv=0;
    char c[20];
    rewind(w);
    while ((!trouv)&&(!(feof(w))))
    {
        j++;
        fscanf(w,"%s",c);
        if (strcmp(c,ch)==0) trouv=1;

    }
    fclose(w);
    if ((j==48)&&(!trouv)) j++;
    return j;
}

///**********************************************************************************

void CharInit(TOF **f,char nomfichier[30],int n)
{
                    /**LES VARIABLES**/

    srand(time(0));
    int i=1,j=0,t,k,w,q=0,cpt=0;
    char ch[11],c,s1[7],s2[7],wilayas[20];
    Tbloc_TOF buf;

                        /**CORPS**/

    ouvrir_TOF(&(*f),nomfichier,'N');
    do
        {
            printf("\n\n\t\tEntrez la date de debut sous la forme XX/XX/XXXX :\t");
            scanf("%s",ch);
        }
    while (verifdate(ch)==0);  ///VERFICATION DE LA DATE

    c=ch[9];
    strncpy(s1,ch,6);
    s1[6]='\0';
    k=1;w=1;

    while(k<=n)
    {
        t=seasonTempe(ch);
        if(j<TAILLE_BLOC)
        {
            strcpy(buf.tab[j].date,ch);
            if (cpt%3==0) wilaya(w,wilayas);  ///on verifie si on a introduit 3 temperatures pour chaque wilaya
            strcpy(buf.tab[j].ville,wilayas);
            buf.tab[j].temp=t;
            buf.tab[j].eff=0;
            cpt++;
            if (cpt==3) {w++;cpt=0;}          ///si on a introduit 3 temperatures on reinitialise à 0
            if (w==49)                        ///on verifie si on a depassé le nombre de wilayas pour incrementer la date
            {
                incdate(ch);
                cpt=0;
                w=1;
            }
            j++;
                            ///on verifie si un an est passé
            strncpy(s2,ch,6);
            s2[6]='\0';
            if ((ch[9]!=c)&&(strcmp(s1,s2)==0))
            {
                k++;
                c=ch[9];
            }
        }
        else            ///j=TAILLE_BLOC
        {
            buf.nb=j;                           ///on sauvegarde le nombre d'enreg dans le bloc
            aff_entete_TOF(*f,1,i);             ///mise à jours de l'entete (nombre de blocs)
            ecrireDir_TOF(*f,i,&buf);
            i++;
            if (cpt%3==0)wilaya(w,wilayas);     ///on verifie si on a introduit 3 temperatures pour chaque wilaya
            strcpy(buf.tab[0].ville,wilayas);
            buf.tab[0].temp=t;
            strcpy(buf.tab[0].date,ch);
            buf.tab[0].eff=0;
            cpt++;
            if (cpt==3) {w++;cpt=0;}            ///on verifie si on a introduit 3 temperatures on reinitialise à 0
            if (w==49)                          ///on verifie si on a depassé le nombre de wilayas pour incrementer la date
            {
                incdate(ch);
                cpt=0;
                w=1;
            }
            j=1;
                        ///on verifie si un an est passé
            strncpy(s2,ch,6);
            s2[6]='\0';
            if ((ch[9]!=c)&&(strcmp(s1,s2)==0))
            {
                k++;
                c=ch[9];
            }
        }
        q++;
    }
    buf.nb=j;
    aff_entete_TOF(*f,1,i);         ///mise à jours de l'entete (nombre de blocs)
    ecrireDir_TOF(*f,i,&buf);
    aff_entete_TOF(*f,2,q);         ///mise à jours de l'entete (nombre de enregistrements)
    fermer_TOF(*f);
}

///**********************************************************************************

void rech_TOF(TOF *f,TOF **f3,int v,char  nomfichier[30])
{
                /**LES VARIABLES**/

    Tbloc_TOF buf,buf2;
    int i=0,j=1,k=0,r=1,q=0;
    char wilayas[20];

                    /**CORPS**/

    wilaya(v,wilayas);
    ouvrir_TOF(&f,nomfichier,'a');
    ouvrir_TOF(&(*f3),"ville",'a');         ///un fichier TOF qui va contenir tous les temperatures de la ville 'wilayas'
    while (j<=entete_TOF(f,1))
    {
        lireDir_TOF(f,j,&buf);
        while (k<buf.nb)
        {
            if (strcmp(buf.tab[k].ville,wilayas)==0)        ///on verifie si la ville dans l'enrigstrement est 'wilayas'
            {
                buf2.tab[i].temp=buf.tab[k].temp;
                strcpy(buf2.tab[i].date,buf.tab[k].date);
                strcpy(buf2.tab[i].ville,buf.tab[k].ville);
                i++;
                if (i>=TAILLE_BLOC)
                {
                    buf2.nb=i;                               ///on sauvegarde le nombre d'enreg dans le bloc
                    aff_entete_TOF(*f3,1,r);                 ///mise à jours de l'entete de f3 (nombre de blocs)
                    ecrireDir_TOF(*f3,r,&buf2);
                    i=0;
                    r++;
                }
                q++;
            }
            k++;
        }
        j++;
        k=0;
    }
    fermer_TOF(f);
    buf2.nb=i;                      ///on sauvegarde le nombre d'enreg dans le bloc
    aff_entete_TOF(*f3,1,r);        ///mise à jours de l'entete de f3 (nombre de blocs)
    ecrireDir_TOF(*f3,r,&buf2);
    aff_entete_TOF(*f3,2,q);        ///mise à jours de l'entete de f3 (nombre de enregistrements)
    fermer_TOF(*f3);
}

///**********************************************************************************

void conversion(TOF *f,TOVC **f2,char  nomfichier[30])
{
            /**LES VARIABLES**/

    TOF *f3;
    Tbloc_TOF buf;
    Tbloc_TOVC BUF;
    char c1[]="00",c2[]="00";
    char ch[20],taille[10];
    char temp1[50],temp2[50],wilayas[20];
    char chaine[50];
    int j=0,i=1,r,m=1;
    int nbbloc=1,pos=0;
    int tai=0,ville=1;
    int sub,som=0;
    D D;
    FILE *w=fopen("leswilaya.txt","r");

                /**CORPS**/

                        ///initialisation des fichiers
    BUF.chaine[0]='\0';
    ouvrir_TOF(&f,nomfichier,'a');
    ouvrir_TOVC(f2,"TOVC",'N');
    ouvrir_TOF(&f3,"ville",'N');
                            /**la conversion**/
    while (ville<49)
    {
        rech_TOF(f,&f3,ville,nomfichier);
        ouvrir_TOF(&f3,"ville",'A');
        wilaya(ville,wilayas);
        lireDir_TOF(f3,1,&buf);

                                /**ecrire la ville dans TOVC**/

        ///les details de chaque enreg
        r=1;
        strcpy(chaine,"000000");                    ///on reserve un espace pour la taille
        sprintf(ch,"%d",buf.tab[0].eff);
        strcat(chaine,ch);
        if (ville<10)                               ///les villes dont le nombre est inferieur à 10
            {
                c1[0]='0';
                c1[1]=ville+48;
                strcpy(ch,c1);
            }
        else sprintf(ch,"%d",ville);
        strcat(chaine,ch);
        strcat(chaine,wilayas);
        if (strlen(chaine)+tai>=TAILLE_BLOC)         ///si la taille de chaine et de buffer depasse TAILLE_BLOC
        {
            sub=TAILLE_BLOC-tai;
            strncpy(temp1,chaine,sub);
            temp1[sub]='\0';
            strcat(BUF.chaine,temp1);
            som+=strlen(BUF.chaine);
            aff_entete_TOVC(*f2,4,i);
            ecrireDir_TOVC(*f2,i,&BUF);
            i++;
            strcpy(BUF.chaine,chaine+sub);
        }
        else
        {
            strcat(BUF.chaine,chaine);
        }
        tai=strlen(BUF.chaine);                         ///la taille courante de buffer

                        ///*********************************************

                                /**concaténation des dates et temperatures**/

        strcpy(ch,buf.tab[j].date);
        while ((j<buf.nb)&&(r<=entete_TOF(f3,1)))
        {
            if ((buf.tab[j].temp<10)&&(buf.tab[j].temp>=0))         ///cas la temperature est inferieur à 10
                {
                    c2[0]='0';
                    c2[1]=buf.tab[j].temp+48;
                }
            else sprintf(c2,"%d",buf.tab[j].temp);
            strcat(ch,c2);
            j++;

            if (m%3==0)                                             ///verification si on a depassé 3 temperatures
            {
                if (tai+strlen(ch)>=TAILLE_BLOC)                     ///si la taille de buffer et la chaine 'ch' depasse TAILLE_BLOC
                {                                                    ///on effectue une ecriture
                    sub=TAILLE_BLOC-tai;
                    strncpy(temp2,ch,sub);
                    temp2[sub]='\0';
                    strcat(BUF.chaine,temp2);
                    aff_entete_TOVC(*f2,4,i);
                    som+=strlen(BUF.chaine);                         ///la taille de l'enregistrement
                    ecrireDir_TOVC(*f2,i,&BUF);
                    i++;
                    strcpy(temp1,ch+sub);
                    strcpy(BUF.chaine,temp1);
                    tai=strlen(BUF.chaine);
                }
                else
                {
                    strcat(BUF.chaine,ch);                          ///sinon on continue la concaténation
                }
                strcpy(ch,buf.tab[j].date);
                tai=strlen(BUF.chaine);
                m=0;
            }
            m++;
            if ((j==buf.nb)&&(r<entete_TOF(f3,1)))          ///si on a parcouru tout le bloc TOF de f3
            {
                r++;
                lireDir_TOF(f3,r,&buf);
                j=0;
            }
        }

                ///***************************************************

                                ///la taille d'enregistrement
        som+=strlen(BUF.chaine);
        sprintf(taille,"%d",som);
        strcpy(D.taille,taille);
        remplacertai(*f2,nbbloc,pos+6-strlen(taille),taille,&D,&j);      ///on remplace l'espace reservé avec la taille
        pos=strlen(BUF.chaine);                                          ///la position où on va remplaer la taille suivante
        nbbloc=i;                                                        ///le bloc où on va remplacer la taille suivante
        ville++;
        som=-strlen(BUF.chaine);
        j=0;
    }
    aff_entete_TOVC(*f2,1,strlen(BUF.chaine));                  ///mise à jours de l'entete TOVC (indice libre)
    aff_entete_TOVC(*f2,4,i);                                   ///mise à jours de l'entete TOVC (nombre des blocs)
    ecrireDir_TOVC(*f2,i,&BUF);

    fclose(w);
    fermer_TOF(f);
    fermer_TOF(f3);
    fermer_TOVC(*f2);
}

///**********************************************************************************

void recuperer(TOVC *f,int i,int j,D *D,int *cout)
{
            /**LES VARIABLES**/

    int k;
    char ch[21];
    Tbloc_TOVC buf;

                /**CORPS**/

    lireDir_TOVC(f,i,&buf);
    (*cout)++;
    k=0;
            ///*********************************
    while(buf.chaine[j]<'A')            ///tant qu'on n'arrive pas au champs de clé
    {
        ch[k]=buf.chaine[j];            ///on récupère la taille et eff et le numero de ville
        k++;j++;
        if (j>=TAILLE_BLOC)
        {
            j=0;
            i++;
            lireDir_TOVC(f,i,&buf);
            (*cout)++;
        }
    }
    ch[k]='\0';
            ///*********************************
    (*D).num[1]=ch[k-1];                                ///le numéro de ville
    (*D).num[0]=ch[k-2];
    (*D).num[2]='\0';
    (*D).eff=ch[k-3];                                   ///caractère d'effacement
    strncpy((*D).taille,ch,k-3);                        ///la taille
    (*D).taille[k-3]='\0';
    k=0;
            ///*********************************
    while ((buf.chaine[j]>'9')||(buf.chaine[j]<'0'))    ///recuperation de la clé
    {
        (*D).cle[k]=buf.chaine[j];
        k++;j++;
         if (j>=TAILLE_BLOC)
        {
            j=0;
            i++;
            lireDir_TOVC(f,i,&buf);
            (*cout)++;
        }
    }
    (*D).cle[k]='\0';
}

///**********************************************************************************

void rech_TOVC(TOVC *f,char cle_r[20],int *i,int *j, int *trouv,int *cout)
{
            /**LES VARIABLES**/

    int k=0,max=TAILLE_BLOC,eff,stop=0;
    D D;
    *i=1;*j=0;*trouv=0;

                /**CORPS**/

    if (nbwilaya(cle_r)<=48)
    {
        recuperer(f,*i,*j,&D,cout);                             ///on récupère les details
        while (*i<=entete_TOVC(f,4)&&(!*trouv)&&(!stop))
        {
            if (atoi(D.num)>=nbwilaya(cle_r)) k=1;              ///on verifie si on a depasse la ville recherché (elle n'existe pas)
            if (*i==entete_TOVC(f,4)) max=entete_TOVC(f,1);     ///la taille de dernier bloc
            eff=atoi(&(D.eff));
                        ///******************************
            if ((!strcmp(cle_r,D.cle)) && (!eff)) *trouv=1;
            else
            {
                if (k==0)                                       ///si on n'a pas depassé la ville recherché
                {
                    *j+=atoi(D.taille);
                    if (*j>=max)
                    {
                        *i+=(*j/max);
                        *j=(*j)%max;
                        recuperer(f,*i,*j,&D,cout);
                    }
                }
                else stop=1;                               ///sinon on arrete
            }
        }
    }
}

///**********************************************************************************

void affichage (TOVC *f, int i, int j,D D,int *cout)
{
            /**LES VARIABLES**/

    int b=TAILLE_BLOC;
    Tbloc_TOVC buf;
    int k=1;
    int p=strlen(D.taille)+strlen(D.cle)+3; ///la longueur des details

                /**CORPS**/

    lireDir_TOVC(f,i,&buf);
    (*cout)++;
    j+=p;                           ///on ajoute à la position la longueur de details
    if (j>=TAILLE_BLOC)             ///on verifie si 'j' a depassé la taille de bloc
    {
        i++;
        lireDir_TOVC(f,i,&buf);
        (*cout)++;
        j=j%TAILLE_BLOC;
    }
    while ((k<=atoi(D.taille)-p))   ///tant que 'k' est inferieur à la déffirence entre la taille et la longueur de details
    {
        if (j<b)
        {
            printf("%c",buf.chaine[j]);
            j++;k++;
        }
        else
        {
            i++;
            lireDir_TOVC(f,i,&buf);
            (*cout)++;
            j=0;
        }
    }
    printf("\n\n");
}

///**********************************************************************************

void requete (TOVC *f,int cle1,int cle2)
{
            /**LES VARIABLES**/

    clock_t t1,t2;
    float temps;
    int b=TAILLE_BLOC;
    Tbloc_TOVC buf;
    int i,j,trouv,stop=0,cout=0;
    D D;
    char ville1[50];
    FILE *COUT;

                /**CORPS**/

    t1=clock();
    COUT=fopen("couts_requete.txt","a+");
    ouvrir_TOVC(&f,"TOVC",'A');
    wilaya(cle1,ville1);                     ///on recupere la ville corespendante au 'cle1'
    rech_TOVC(f,ville1,&i,&j,&trouv,&cout);  ///rechercher 'ville1'
    if (trouv)
    {
        lireDir_TOVC(f,i,&buf);
        cout++;
        while ((!stop)&&(i<=entete_TOVC(f,4)))
        {
            if (i==entete_TOVC(f,4)) b=entete_TOVC(f,1);    ///la taille de dernier bloc
            recuperer(f,i,j,&D,&cout);                      ///on recupere les détails de ville1
            if (atoi(D.num)<=cle2)
            {
                printf("\n\n\t\t\t\t\t***************%s***************\n\n",D.cle);
                if (!atoi(&(D.eff))) affichage(f,i,j,D,&cout);   ///affichage de ville
                j+=atoi(D.taille);
                if (j>=b)
                {
                    i+=j/b;
                    j=j%b;
                    lireDir_TOVC(f,i,&buf);
                    cout++;
                }
            }
            if (atoi(D.num)==cle2) stop=1;
        }
    }
    fermer_TOVC(f);
    cout++;
    fprintf(COUT,"%d\n",cout);
    fclose(COUT);
    t2=clock();
    temps=(float)(t2-t1)/CLOCKS_PER_SEC;                            ///calcule du temps d'éxecution
    printf("\n\t\t\t--->le temps d'éxecution est %fs\n",temps);
    printf("\n\t\t\t--->le cout est %d\n",cout);
}

///**********************************************************************************

void rech_date(TOVC *f,char date_rech[10],int *i,int *j,int *trouv,D D,int *cout)
{
                /**LES VARIABLES**/

    Tbloc_TOVC buf;
    char date[11];
    int l=strlen(D.cle)+strlen(D.taille)+3; ///la longueur des détails
    int k=*j,T=l,p=0,q=0,n;
    *trouv=0;
                    /**CORPS**/

    lireDir_TOVC(f,*i,&buf);
    (*cout)++;
    if (k+l>=TAILLE_BLOC)           ///on verifie si la somme de la position et la longueur des détails est superieur à la taille de bloc
    {
        l=l+k-TAILLE_BLOC;          ///la longueur restante des détails
        (*i)++;
        lireDir_TOVC(f,*i,&buf);
        (*cout)++;
        k=l;
    }
    else k+=l;                      ///sinon on ajoute l à la position

    while ((!*trouv)&&(T<atoi(D.taille))&&(*i<=entete_TOVC(f,4)))
    {
        while (p<10)                ///on recupere la date
        {
            date[p]=buf.chaine[k];
            k++;p++;n++;
            if (k>=TAILLE_BLOC)
                {
                    k=0;
                    (*i)++;
                    lireDir_TOVC(f,*i,&buf);
                    (*cout)++;
                }
        }
        date[p]='\0';
        p=0;
        T+=10;                                                   ///on ajoute 10 au nombre des caractères parcourus
        if (!strcmp(date,date_rech)) *trouv=1;
        else
        {   while ((buf.chaine[k]!='/')&&(T+q-2<atoi(D.taille)))        ///la position de la date suivante
            {
                k++;
                if (k>=TAILLE_BLOC)
                {
                    k=0;
                    (*i)++;
                    lireDir_TOVC(f,*i,&buf);
                    (*cout)++;
                }
                q++;
            }
            if (k<2)                                ///le cas où le '/' est dans la position '0' ou '1' de buffer
            {
                (*i)--;
                lireDir_TOVC(f,*i,&buf);
                (*cout)++;
                k=TAILLE_BLOC+k-2;
            }
            else k=k-2;
            T+=q-2;
            q=0;
        }
    }
    *j=k;
}

///**********************************************************************************

void decalbloc(TOVC *f,int nbbloc,int tairest,int taiInser,int *cout)
{
                            /**LES VARIABLES**/
    char ch[taiInser];
    Tbloc_TOVC c1,c2,c3;
    int n=entete_TOVC(f,4),x=0;

                                /**CORPS**/

    if (tairest<=TAILLE_BLOC)   ///on vérifie si la position est inferieur ou égale à TAILLE_BLOC
    {
        lireDir_TOVC(f,n,&c1);
        (*cout)++;
        if (taiInser+strlen(c1.chaine)>=TAILLE_BLOC)     ///Si la somme de taille à inserer et la taille de buffeur est superieur à TAILLE_BLOC
        {
            strcpy(ch,c1.chaine+TAILLE_BLOC-taiInser);   ///on copie les caractère positionés aprés (TAILLE_BLOC-taiInser) dans un nouveau bloc
            strcpy(c3.chaine,ch);
            aff_entete_TOVC(f,4,entete_TOVC(f,4)+1);     ///mise à jour de numéro de bloc
            aff_entete_TOVC(f,1,strlen(ch));             ///mise à jour de l'indice libre
            ecrireDir_TOVC(f,n+1,&c3);
            (*cout)++;
            strncpy(c1.chaine,c1.chaine,TAILLE_BLOC-taiInser);  /// on supprime les caractères copiés
            c1.chaine[+TAILLE_BLOC-taiInser]='\0';
        }
        if (tairest+taiInser>TAILLE_BLOC) x++;
        while (n>nbbloc)
        {                           ///on fait un décalage successive jusqu'à nbbloc ou nbbloc-1 d'aprés x
            lireDir_TOVC(f,n-1,&c2);
            (*cout)++;
            if ((n-1!=nbbloc)||(x==0))
            {
                strcpy(ch,c2.chaine+TAILLE_BLOC-taiInser);
                strncpy(c2.chaine,c2.chaine,+TAILLE_BLOC-taiInser);
                c2.chaine[TAILLE_BLOC-taiInser]='\0';
            }
            else
            {
                strcpy(ch,c2.chaine+tairest);
                strncpy(c2.chaine,c2.chaine,tairest);
                c2.chaine[tairest]='\0';
            }
            strcpy(c3.chaine,ch);
            strcat(c3.chaine,c1.chaine);
            ecrireDir_TOVC(f,n,&c3);
            (*cout)++;
            strcpy(c1.chaine,c2.chaine);
            n--;
        }
        ecrireDir_TOVC(f,n,&c1);
        (*cout)++;
    }
    else printf("erreur dans la taille rest");
}

///**********************************************************************************

void inserTOVC(TOVC *f,int nbbloc,int tairest,char ch[35],int *cout)
{
                        /**LES VARIABLES**/

    Tbloc_TOVC c,c2;
    char cha[TAILLE_BLOC];
    int x=1,y=strlen(ch);

                            /**CORPS**/

    decalbloc(f,nbbloc,tairest,strlen(ch),cout);
    lireDir_TOVC(f,nbbloc,&c);
    (*cout)++;
    if (tairest<=TAILLE_BLOC)
    {
        if (tairest+y>TAILLE_BLOC)
        {                                           ///si la position de l'inserion est à la fin de bloc
            x=-tairest+TAILLE_BLOC;
            strncpy(cha,ch,x);
            cha[x]='\0';
            strcpy(ch,ch+x);
            strcat(c.chaine,cha);
            ecrireDir_TOVC(f,nbbloc,&c);
            lireDir_TOVC(f,nbbloc+1,&c);
            strcpy(c2.chaine,ch);
            strcat(c2.chaine,c.chaine);
            ecrireDir_TOVC(f,nbbloc+1,&c2);
            (*cout)+=3;
        }
        else
        {                                           ///si la position de l'insertion est au milieu de bloc
            strcpy(cha,c.chaine+tairest);
            strncpy(c.chaine,c.chaine,tairest);
            c.chaine[tairest]='\0';
            strcat(c.chaine,ch);
            if (tairest+y==TAILLE_BLOC)  c.chaine[TAILLE_BLOC]='\0';
            else  strcat(c.chaine,cha);
            ecrireDir_TOVC(f,nbbloc,&c);
            (*cout)++;
        }
    }
    else printf("erreur dans la taille rest");
}

///**********************************************************************************

void remplacertai(TOVC *f,int nbbloc,int tairest,char ch[20],D *D,int *cout)
{
                            /**LES VARIABLES**/

    Tbloc_TOVC c;
    int i=0;
                                /**CORPS**/

    if (tairest+i>=TAILLE_BLOC) {nbbloc++;tairest=-i;}
    lireDir_TOVC(f,nbbloc,&c);
    (*cout)++;
    while (i<strlen(ch))
    {                                       ///on remplace caractère par caractère la taille précédent par la taille ch
        c.chaine[tairest+i]=ch[i];
        i++;
        if (tairest+i>=TAILLE_BLOC)
        {
            tairest=-i;
            ecrireDir_TOVC(f,nbbloc,&c);
            nbbloc++;
            lireDir_TOVC(f,nbbloc,&c);
            (*cout)+=2;
        }
    }
    ecrireDir_TOVC(f,nbbloc,&c);
    (*cout)++;
    strcpy((*D).taille,ch);
}

///**********************************************************************************

void insertion(TOVC *f,int nbwil,char temp1[3],char date[11])
{
                /**LES VARIABELES**/

    clock_t t1,t2;
    float temps;
    Tbloc_TOVC c;
    D D;
    char ch1[10],ville[20],chaine[35];
    int trouv,trouv2;
    int nbbloc2,nbbloc1,tairest2,tairest1;
    int tai,cout=0,inser=1;
    FILE *COUT,*TAILLE;

                    /**CORPS**/

    t1=clock();
    wilaya(nbwil,ville);
    COUT=fopen("couts_insertion.txt","a+");
    TAILLE=fopen("file size.txt","a+");
    ouvrir_TOVC(&f,"TOVC",'A');
    rech_TOVC(f,ville,&nbbloc1,&tairest1,&trouv,&cout);                 /// On recherche la ville dans TOVC
    if (trouv)
    {
        lireDir_TOVC(f,nbbloc1,&c);
        cout++;
        recuperer(f,nbbloc1,tairest1,&D,&cout);                         ///on recupere les caractéristique de la ville (Taille,numéro,nom et le champs effacé
        nbbloc2=nbbloc1;
        tairest2=tairest1;
        rech_date(f,date,&nbbloc2,&tairest2,&trouv2,D,&cout);           ///on recherche la date d'insertion si elle existe déja ou pas
        if (trouv2) strcpy(chaine,temp1);                               ///si la date existe on insère juste la tempurature
        else
        {                                                               ///sinon on insère la date et la température
            strcpy(chaine,date);
            strcat(chaine,temp1);
        }
        tai=atoi(D.taille)+strlen(chaine);                              ///mise à jour de la taille d'enregistrement
        sprintf(ch1,"%d",tai);
        inserTOVC(f,nbbloc2,tairest2,chaine,&cout);                     ///Insertion de chaine dans la bloc nbbloc2 à la position tairest2
        remplacertai(f,nbbloc1,tairest1+6-strlen(ch1),ch1,&D,&cout);    ///On remplace la nouvelle taille dans TOVC
    }
    else
    {           ///si la ville n'existe pas on l'insere à la fin du fichier TOVC

        nbwil=nbwilaya(ville);
        printf("%d",nbwil);
        if (nbwil<=48)
        {
            tai=3+strlen(ville)+strlen(date)+strlen(temp1);
            sprintf(ch1,"%d",tai);
            tai+=strlen(ch1);
            sprintf(ch1,"%d",tai);
            if (strlen(ch1)<6) {strcpy(chaine,"000000"+strlen(ch1));strcat(chaine,ch1);}
            else strcpy(chaine,ch1);
            strcat(chaine,"0");
            if (nbwil<10)
            {
                ch1[0]='0';
                ch1[1]=nbwil+48;
                ch1[2]='\0';
            }
            else sprintf(ch1,"%d",nbwil);
            strcat(chaine,ch1);
            strcat(chaine,ville);
            strcat(chaine,date);
            strcat(chaine,temp1);
            inserTOVC(f,nbbloc1,tairest1,chaine,&cout);
        }
        else
        {
            printf("\n\t\t\tle ville n'existe pas\n");
            inser=0;
        }
    }
    if (inser)      ///si l'insertion est réussie
    {
        aff_entete_TOVC(f,1,entete_TOVC(f,1)+strlen(chaine));   ///mise à jour de l'indice libre
        printf("\n\t\t--->le nouvel indice libre est %d\t\n",entete_TOVC(f,1));
        cout++;
        fprintf(COUT,"%d\n",cout);///on sauvgarde le cout dans un fichier
        fprintf(TAILLE,"%d\n",(entete_TOVC(f,4)-1)*1024+entete_TOVC(f,1)); ///on sauvgarde la taille de fichier TOVC
        fermer_TOVC(f);
        fclose(COUT);
        fclose(TAILLE);
        t2=clock();
        temps=(float)(t2-t1)/CLOCKS_PER_SEC;                        ///calcule de temps d'execution
        printf("\n\t\t--->le temps d'éxecution est %fs\n",temps);
        printf("\n\t\t--->le cout est %d\n",cout);
    }
}

///**********************************************************************************

void welcome()
{
    system("color 73");
    printf("\n\n\n\n\t\t\t         _______________________________________________________ \n");
    printf("\t\t\t        |        _______     _______     _                      |\n");
    printf("\t\t\t        |       |  _____|   |  _____|   | |  école nationale    |\n");
    printf("\t\t\t        |       | |_____    | |_____    | |                     |\n");
    printf("\t\t\t        |       |  _____|   |_____  |   | |  superieure         |\n");
    printf("\t\t\t        |       | |_____     _____| |   | |                     |\n");
    printf("\t\t\t        |       |_______|   |_______|   |_|  d'informatique     |\n");
    printf("\t\t\t        |_______________________________________________________|\n\n");
    printf("\t\t\t\t    CPI - 2ème Année - Année Universitaire 2018/2019 \n\n\n");
    printf("\t\t\t _______________________________________________________________________\n");
    printf("\t\t\t|                                                            \t\t|\n");
    printf("\t\t\t| REALISE PAR : ZATOUT BADREDDINE et DJEHAICHE SALAH         \t\t|\n");
    printf("\t\t\t|                                                             \t\t|\n");
    printf("\t\t\t|        \t ANNEE SCOLAIRE : 2018/2019                        \t|\n");
    printf("\t\t\t|                                                             \t\t|\n");
    printf("\t\t\t|         \tSECTION : B           GROUPE: 05                  \t|\n");
    printf("\t\t\t|                                                             \t\t|\n");
    printf("\t\t\t|         \tTP :   Evaluation des opérations sur les fichiers \t|\n");
    printf("\t\t\t|                                                             \t\t|\n");
    printf("\t\t\t|                        <FICHIERS TOF ET TOVC>               \t\t|\n");
    printf("\t\t\t|                                                               \t|\n");
    printf("\t\t\t|                                                             \t\t|\n");
    printf("\t\t\t| ENCADRE PAR :Madame ARTABAZ                            \t\t|\n ");
    printf("\t\t\t|_______________________________________________________________________|\n\n\n");
}

///**********************************************************************************

void choix()
{
    system("pause");
    system("cls");
    printf("\n\n\n\n\t---->Vous choisissez l'une des operations suivantes: \n\n\n");
    printf("\t\t\t ---------------------------------------------------------\n");
    printf("\t\t\t| 01---->Creation d'un nouveau fichier TOF.               |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 02---->Afficher le fichier TOF.                         |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 03---->Conversion TOF_TOVC                              |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 04---->Afficher le fichier TOVC.                        |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 05---->La requete à intervalle.                         |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 06---->L'insertion.                                     |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 07---->Exemple d'evaluation de cout.                    |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 08---->L'impact de reordonne TOVC selon la date         |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t| 00---->Quitter.                                         |\n");
    printf("\t\t\t|                                                         |\n");
    printf("\t\t\t ---------------------------------------------------------\n");
}
