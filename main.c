#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "Struct.h"
#include "biblio.h"
int main()
{
    setlocale(LC_ALL,""); ///POUR AFFICHER LES CARACTERE SPECIAUX

                /**DECLARATION DES VARAIBLES**/

    TOF *f;
    TOVC *f2;
    FILE *impact;
    int n,choice,fin=0;
    int j=1,k=0,q=0,i=1;;
    Tbloc_TOF buf;
    Tbloc_TOVC buf2;
    int cle1,cle2;
    char impa[50];
    char date[11],temp1[3];
    int temp=-10,nbwil,vrai,stop;

                    /**PROGRAMME PRINCIPALE**/
    welcome();
    while (!fin)
    {
        choix();
        printf("\n\n\t\tVeuillez entrer votre choix : ");
        scanf("%d",&choice);
        system("cls");

        switch(choice)
        {
            case 1:     /**LA CREATION DE FICHIER TOF**/
            {
                printf("\n\n\t\tVeuillez entrer le nombre des années : ");
                scanf("%d",&n);
                CharInit(&f,"TOF",n);
                printf("\n\n\t\t\t********la la création de TOF est terminée********\n ");
                printf("\n\n\t\t\t\t _______________________\n");
                printf("\t\t\t\t|                \t|\n");
                printf("\t\t\t\t|  nb bloc=%d    \t|\n",entete_TOF(f,1));
                printf("\t\t\t\t|                \t|\n");
                printf("\t\t\t\t|  nb Enreg=%d   \t|\n",entete_TOF(f,2));
                printf("\t\t\t\t|_______________________|\n\n");
                fermer_TOF(f);
                break;
            }
            case 2:     /**AFFICHAGE DE TOF**/
            {
                ouvrir_TOF(&f,"TOF",'a');
                if ((f->file)==NULL)
                {
                    printf("\n\n\t\t!!!!!le fichier n'existe pas!!!!!\n");
                    break;
                }
                j=1;
                lireDir_TOF(f,j,&buf);
                while (j<=entete_TOF(f,1))
                {
                    while (k<=buf.nb+1)
                    {
                        if (q%144==0) printf("\n\n\t\t\t---------- la date %s  ----------------\n\n",buf.tab[k].date);
                        if (q%3==0)
                        {
                            printf("\n\t\t\t\t%s\n",buf.tab[k].ville);
                            printf("\t\t\t\t _______________________\t\n");
                        }

                        printf("\t\t\t\t|                 \t|\n");
                        printf("\t\t\t\t| temp%d--->%d    \t|\n",k%3+1,buf.tab[k].temp);
                        if ((q+1)%3==0)printf("\t\t\t\t|_______________________|\t\n");
                        if ((q+1)%(144)==0)
                        {
                            printf("\n\n\t\t\t---------- la date %s  ----------------\n\n",buf.tab[k].date);
                            printf("\t\t\t----------le nombre des enregistrements restes est --->%d\n\n",entete_TOF(f,2)-q-1);
                            if ((q+1)%1440==0)
                            {
                                printf("\n\t\t\técrivez 1 pour arreter l'affichage\n\n");
                                scanf("%d",&stop);
                                if (stop==1)break;
                            }
                        }
                        k++;
                        q++;
                    }
                j++;
                 if (stop==1)break;
                lireDir_TOF(f,j,&buf);k=0;
                }
                break;
            }
            case 3:     /**LA CONVERSION DE TOF_TOVC**/
            {
                ouvrir_TOF(&f,"TOF",'a');
                if ((f->file)==NULL)
                {
                    printf("\n\n\t\t!!!!!!le fichier n'existe pas!!!!!\n");
                    break;
                }
                fermer_TOF(f);
                conversion(f,&f2,"TOF");
                printf("\n\n\t\t\t********la conversion au TOVC est terminée********\n ");
                printf("\n\n\t\t\t\t _______________________\n");
                printf("\t\t\t\t|                  \t|\n");
                printf("\t\t\t\t|   indice libre=%d\t|\n",entete_TOVC(f2,1));
                printf("\t\t\t\t|                  \t|\n");
                printf("\t\t\t\t|   nb bloc=%d     \t|\n",entete_TOVC(f2,4));
                printf("\t\t\t\t|_______________________|\n\n");
                fermer_TOVC(f2);
                break;
            }
            case 4:     /**AFFICHAGE DE TOVC**/
            {
                ouvrir_TOVC(&f2,"TOVC",'A');
                if ((f2->fichier)==NULL)
                {
                    printf("le fichier n'existe pas!!!!!\n");
                    break;
                }
                do
                {
                    printf("choisissez le bloc de départ de 01 à %d :",entete_TOVC(f2,4));
                    scanf("%d",&i);
                }while((i<1)||(i>entete_TOVC(f2,4)));

                do
                {
                    printf("choisissez le bloc d'arrive de %d à %d :",i,entete_TOVC(f2,4));
                    scanf("%d",&stop);
                }while((stop<i)&&(stop>entete_TOVC(f2,4)));

                while ((i<=entete_TOVC(f2,4))&&(i<=stop))
                {
                    lireDir_TOVC(f2,i,&buf2);
                    printf("\t\t\t\t\t \ttaille de chaine est %d\n\n",strlen(buf2.chaine));
                    printf("\n%s\n\n",buf2.chaine);
                    printf("\t\t\t\t\t \tnombre de bloc reste est %d\n\n\n\n",entete_TOVC(f2,4)-i);
                    i++;
                }
                break;
            }
            case 5:     /**LA REQUETE A INTERVALLE**/
            {
                ouvrir_TOVC(&f2,"TOVC",'a');
                if ((f2->fichier)==NULL)
                {
                    printf("le fichier n'existe pas!!!!!\n");
                    break;
                }
                fermer_TOVC(f2);
                printf("\n\n\t\t\tVeuillez entrer la première ville  : ");
                scanf("%d",&cle1);
                printf("\n\n\t\t\tVeuillez entrer la deuxième ville  : ");
                scanf("%d",&cle2);
                if ((cle1<=cle2)&&(cle2<=48)&&(cle1>0)&&(cle2>0))
                {
                    requete(f2,cle1,cle2);
                }
                else {printf("!!!!!!!!!!!un de les cle est faux!!!!!!!!\n");break;}
                break;
            }
            case 6:     /**L'INSERTION*/
            {
                vrai=0;
                ouvrir_TOVC(&f2,"TOVC",'a');
                if (f2==NULL)
                {
                    printf("le fichier n'existe pas!!!!!\n");
                    break;
                }
                fermer_TOVC(f2);
                do
                {
                    printf("\n\n\t\t\tdonnez le numéro de ville d'insertion : ");
                    scanf("%d",&nbwil);
                    if ((nbwil>48)||(nbwil<=0))
                    {
                        printf("\t\t\tcette ville n'existe pas!!!!\n");
                    }
                    else vrai=1;
                }while (!vrai);

                do
                {
                    printf("\n\n\t\t\tEntrez la date de debut sous la forme XX/XX/XXXX :\t");
                    scanf("%s",date);
                }while (verifdate(date)==0);
                do
                {
                    printf("\n\n\t\t\tdonnez la tempurature d'insertion entre -9 et 50 :");
                    scanf("%d",&temp);
                }while ((temp<-9)||(temp>50));
                if ((temp<10)&&(temp>-1))
                {
                    temp1[0]='0';
                    temp1[1]=temp+48;
                }
                else sprintf(temp1,"%d",temp);
                insertion(f2,nbwil,temp1,date);
                printf("\n\n\t\t\tl'insetion est terminée avec succès \n\n");
                break;
            }
            case 7:     /**EXEMPLE D'EVALUATION DE COUT**/
            {
                q=0;
                i=1;
                while (i<49)
                {
                    date_alea(date);
                    temp=seasonTempe(date);
                    if ((temp<10)&&(temp>-1))
                    {
                        temp1[0]='0';
                        temp1[1]=temp+48;
                    }
                    else sprintf(temp1,"%d",temp);
                    insertion(f2,i,temp1,date);
                    q++;
                    if (q%3==0) i++;
                }
                system("cls");
                requete(f2,1,48);
                break;
            }
            case 8:
            {           /**L'IMPACT DE REORDONNE TOVC SELON LA DATE **/
                impact=fopen("L'impact.txt","r");
                puts("");
                puts("");
                while (!feof(impact))
                {
                  fgets(impa,500,impact);
                  printf("\t\t\t%s",impa);
                }
                puts("");
                puts("");
                fclose(impact);
                break;
            }
            case 0:     /**QUITTER LE PROGRAMME**/
            {
                fin=1;
                break;
            }
        }
    }
    return 1;
}
