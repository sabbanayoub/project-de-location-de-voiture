#ifndef GESTION_CLIENT_H_INCLUDED
#define GESTION_CLIENT_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"structure.h"
#include"prototype.h"
#include"foction.h"
void list_client(void)
{
    FILE *fichier = NULL;
    client Tab;
    fichier = fopen("Clients","r");
    if(fichier != NULL){
        system("cls");
        printf("Id       |Nom       |Prenom    |cin     |adresse        |telephone\n");
        while (!feof(fichier)){
            fscanf(fichier,"%d ;%s ;%s ;%d ;%s ;%d \n",&Tab.idClient,Tab.nom,Tab.prenom,&Tab.CIN,Tab.adresse,&Tab.telephone);
            printf("%d   |%s  |%s   |%d|%s  |%d",Tab.idClient,Tab.nom,Tab.prenom,Tab.CIN,Tab.adresse,Tab.telephone);
        }
        fclose(fichier);
    }
}

int ajouter_client(void)
{
    FILE *fichier = NULL;
    client A;
    char choix;
    fichier = fopen("Clients","a");
    if(fichier != NULL){
        system("cls");
        printf("Id du client :");
        scanf("%d",&A.idClient);
        while(chercheC(A.idClient)){
            printf("Ce id est deja existe\n");
            printf("Voulez vous continuer l'ajout O/N:");
            scanf("%c",&choix);
            if(choix == 'O' || choix == 'o'){
                system("cls");
                printf("Id du client :");
                scanf("%d",&A.idClient);
            }
            else { fclose(fichier);return 0;}
        }
        printf("Nom :");
        scanf("%s",A.nom);
        printf("Prenom :");
        scanf("%s",A.prenom);
        printf("CIN :");
        scanf("%d",&A.CIN);
        printf("Adresse :");
        scanf("%s",A.adresse);
        printf("Telephone :");
        scanf("%d",&A.telephone);
        fprintf(fichier,"%d ;%s ;%s ;%d ;%s ;%d \n",A.idClient,A.nom,A.prenom,A.CIN,A.adresse,A.telephone);
        fclose(fichier);
    }
 return 0;
 }

void modifier_client(void)
{
    FILE *fichier = NULL;
    client tab[100];
    int i,id,choix,fin,j = 0;
    fichier =fopen("Clients","w+");
    if (fichier != NULL){
        printf("donnez l'id du client que vous avez modifier");
        scanf("%d",&id);
        for(i=0;!feof(fichier);i++){
            fscanf(fichier,"%d ;%s ;%s ;%d ;%s ;%d \n",&tab[i].idClient,tab[i].nom,tab[i].prenom,&tab[i].CIN,tab[i].adresse,&tab[i].telephone);
            if(tab[i].idClient == id){
                    while(!fin){
                do{ system("cls");
                    printf("id du client :%d..1\n",tab[i].idClient);
                    printf("nom :%s...........2\n",tab[i].nom);
                    printf("prenom :%s........3\n",tab[i].prenom);
                    printf("cin :%d...........4\n",tab[i].CIN);
                    printf("adresse :%s.......5\n",tab[i].adresse);
                    printf("telephone :%d.....6\n",tab[i].telephone);
                    printf("retour............0\n");
                    scanf("%d",&choix);
                    system("cls");
                }while(choix<0 || choix>6);
                 switch (choix)
                {
                    case 0:fin++;
                    case 1:
                        printf("donnez le nouveau id du client :");
                        if(chercheC(tab[i].idClient) == 0)
                            printf("Excusez moi ,il na pas un client de cet id\n");
                    case 2:
                        printf("donnez le nouveau nom :");
                        scanf("%s",tab[i].nom);
                    case 3:
                        printf("donnez le nouveau prenom :");
                        scanf("%s",tab[i].prenom);
                    case 4:
                        printf("donnez le nouveau CIN:");
                        scanf("%d",&tab[i].CIN);
                    case 5:
                        printf("donnez le nouveau adresse :");
                        scanf("%s",tab[i].adresse);
                    case 6:
                        printf("donnez le nouveau telephone:");
                        scanf("%d",&tab[i].telephone);
                }
            }}
        } j = i;
        if(!fin)printf("no client de cet id \n");
        fclose(fichier);
        fichier = fopen("Clients","w");
        if(fichier != NULL){
            for(i=0;i<j;i++){
                 fprintf(fichier,"%d ;%s ;%s ;%d ;%s ;%d \n",tab[i].idClient,tab[i].nom,tab[i].prenom,tab[i].CIN,tab[i].adresse,tab[i].telephone);
            }
            fclose(fichier);
        }
}
}
void supprimer_client(void)
{
    FILE *fichier,*f;
    client Tab;
    int id;
    fichier = fopen("Clients","r");
    f = fopen("temporaire","a");
    if(fichier != NULL && f != NULL){
        while(!feof(fichier)){
            system("cls");
            printf("Donnez l'id dsu voiture que vous allez supprimer\n");
            scanf("%d",&id);
            fscanf(fichier,"%d ;%s ;%s ;%d ;%s ;%d \n",&Tab.idClient,Tab.nom,Tab.prenom,&Tab.CIN,Tab.adresse,&Tab.telephone);
            if(Tab.idClient != id)
                fprintf(f,"%d ;%s ;%s ;%d ;%s ;%d \n",Tab.idClient,Tab.nom,Tab.prenom,Tab.CIN,Tab.adresse,Tab.telephone);
        }
        fclose(fichier);
        fclose(f);
        remove("Clients"),
        rename("temporaire","Clients");
        printf("Suppression effectue avec succes");
    }
}
#endif // GESTION_CLIENT_H_INCLUDED
