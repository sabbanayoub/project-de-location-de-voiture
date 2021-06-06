#ifndef GESTION_VOITURE_H_INCLUDED
#define GESTION_VOITURE_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"structure.h"
#include"prototype.h"
#include"foction.h"
enum quit{
  LOGGED_OUT,
  LOGGED_IN,
  EXIT
};
//liste du voiture
void list_voiture(void){
    FILE *fichier = NULL;
    int i;
    voiture tab[100];
    printf("id  |||marque       |||nom         |||couleur  |||nbplaces|||prix |||louer\n");
    fichier =fopen("Voitures","r");
    if (fichier != NULL){
        for(i=0;!feof(fichier);i++){
            fscanf(fichier,"%d ;%s ;%s ;%s ;%d ;%d ;%s \n",&tab[i].idVoiture,tab[i].marque,tab[i].nomVoiture,tab[i].couleur,&tab[i].nbplaces,&tab[i].prixJour,tab[i].EnLocation);
            printf("%d|||%s  |||%s  |||%s     |||%d       |||%d |||%s",tab[i].idVoiture,tab[i].marque,tab[i].nomVoiture,tab[i].couleur,tab[i].nbplaces,tab[i].prixJour,tab[i].EnLocation);
        }
        fclose(fichier);
    }
}

//  ajouter une voiture
void Ajoutter_voiture(void){
    voiture v;
    int nb,i;
    printf("Entrer le nombres de voitures que vous pouvez ajouter : \n");
    scanf("%d",&nb);
    FILE *fichier=NULL;
fichier=fopen("voitures.txt","a");
  if (fichier != NULL)
{


    for(i=0;i<nb;i++){
        printf("\n \n la voiture numero %d \n",i+1);
        printf(" \n ----------- \n");
        printf("Entrer le id du voiture \n");
        scanf("%d",&v.idVoiture);
        printf("Entrer la marque du voiture \n");
        scanf("%s",v.marque);
        printf("Entrer le nom du voiture \n");
        scanf("%s",v.nomVoiture);
        printf("Entrer le couleur du voiture \n");
        scanf("%s",v.couleur);
        printf("Entrer le nombres des places \n");
        scanf("%d",&v.nbplaces);
        printf("Entrer le prixjour \n");
        scanf("%d",&v.prixJour);
        printf("Entrer l'enlocation \n");
        scanf("%s",v.EnLocation);
    }
{
           fprintf(fichier,"%d   %s   %s    %s    %d  %d  \n", v.idVoiture, v.nomVoiture, v.marque, v.couleur , v.nbplaces, v.prixJour);
                fclose(fichier);}



}}

// modifier les parametre d'une voiture
int modifier_voiture (void){
    FILE *fichier=NULL;
    voiture tab[5];
    int i,id,choix,fin =0;
    fichier =fopen("voitures.txt","r+");
    if(!fichier)
    system("cls");
    printf("Donnez l ID de la voiture que vous voulez modifier. id =");
    scanf("%d",&id);
      for(i=0;!feof(fichier);i++){
      if ( fichier == NULL ) {
        printf( "Cannot open file \n");
        return 0;}else{

        fscanf(fichier,"%d %s %s %s %d %d %s \n",&tab[i].idVoiture,tab[i].marque,tab[i].nomVoiture,tab[i].couleur,&tab[i].nbplaces,&tab[i].prixJour,tab[i].EnLocation);

         if(tab[i].idVoiture == id){
                    while(!fin){
                do{ system("cls");
                    printf("pour changer la marque--> taper [1]:%s",tab[i].marque);
                    printf("\n pour changer le nom--> taper [2]:%s",tab[i].nomVoiture);
                    printf("\n pour changer la couleur--> taper [3]:%s",tab[i].couleur);
                    printf("\n pour changer le nombre de places--> taper [4]:%d",tab[i].nbplaces);
                    printf("\n pour changer le prix --> taper [5] :%d",tab[i].prixJour);
                    printf("\n la voiture est En location--> taper [6] :%s",tab[i].EnLocation);
                    printf("\nenregistrer--> taper [0]");
                    printf("\nvotre choix :");
                    scanf("%d",&choix);
                }while(choix<0 || choix>6);
                system("cls");
                  switch (choix)
                {
                    case 0:fin ++;
                    printf("MERCI D'AVOIR NOUS VISITEZ ,AUREVOIR !! \n");
                    return EXIT;
                    case 1:
                        printf("Donnez le nouveau marque :");
                        scanf("%s",tab[i].marque);
                        break;

                    case 2:
                        printf("Donnez le nouveau nom:");
                        scanf("%s",tab[i].nomVoiture);
                        break;

                    case 3:
                        printf("Donnez le nouveau couleur :");
                        scanf("%s",tab[i].couleur);
                        break;

                    case 4:
                        printf("Donnez le nouveau nombre de places:");
                        scanf("%d",&tab[i].nbplaces);
                        break;

                    case 5:
                        printf("Donnez le nouveau prix par jour:");
                        scanf("%d",&tab[i].prixJour);
                        break;

                    case 6:
                        printf("Est ce qu'elle est en location (oui/non):");
                        scanf("%s",tab[i].EnLocation);
                        break;
                   default:
                        printf("Invalid choice, please insert a valid number\n");
                        break;

                }

            }}fclose(fichier);
            fichier = fopen("voitures.txt","w");
            for(i=0;!feof(fichier);i++){
                fprintf(fichier,"%d %s %s %s %d %d %s \n",tab[i].idVoiture,tab[i].marque,tab[i].nomVoiture,tab[i].couleur,tab[i].nbplaces,tab[i].prixJour,tab[i].EnLocation);
            }
      }
         fclose(fichier);

}
return 0;
}
// supprimer une voiture
void supprimer_voiture(void)
{
    FILE *f,*fichier;
    voiture aide;
    int id;
    fichier = fopen("Voitures.txt","r");
    f = fopen("temporaire","a");
    if(fichier != NULL && f != NULL){
        system("cls");
        printf("Donnez l'id du voiture que vous allez supprimer :");
        scanf("%d",&id);
        while(!feof(fichier)){
            fscanf(fichier,"%d ;%s ;%s ;%s ;%d ;%d ;%s \n",&aide.idVoiture,aide.marque,aide.nomVoiture,aide.couleur,&aide.nbplaces,&aide.prixJour,aide.EnLocation);
            if(aide.idVoiture != id)
                fprintf(f,"%d ;%s ;%s ;%s ;%d ;%d ;%s \n",aide.idVoiture,aide.marque,aide.nomVoiture,aide.couleur,aide.nbplaces,aide.prixJour,aide.EnLocation);
        }
        fclose(fichier);
        fclose(f);
        remove("Voitures");
        rename("temporaire","Voitures");
        printf("Suppression effectue avec succees");
    }
}


#endif // GESTION_VOITURE_H_INCLUDED
