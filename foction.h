#ifndef FOCTION_H_INCLUDED
#define FOCTION_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"structure.h"
#include"prototype.h"
int chercheV(int id){
    voiture tab;
    FILE *fichier = NULL;
    fichier = fopen("Voitures","r");
    if (fichier != NULL){
        do{
            fscanf(fichier,"%d ;%s ;%s ;%s ;%d ;%d ;%s \n",&tab.idVoiture,tab.marque,tab.nomVoiture,tab.couleur,&tab.nbplaces,&tab.prixJour,tab.EnLocation);
            if(tab.idVoiture == id && tab.EnLocation == 'non'){
                fclose(fichier);
                return 1;
            }
            if(tab.idVoiture == id && tab.EnLocation == 'oui'){
                fclose(fichier);
                return 2;
            }
        }while(!feof(fichier));
        fclose(fichier);
    }
return 0;
}

int chercheC(int id){
    client tab;
    FILE *fichier = NULL;
    fichier = fopen("Clients","r");
    if(fichier != NULL){
        do{
            fscanf(fichier,"%d ;%s ;%s ;%d ;%s ;%d \n",&tab.idClient,tab.nom,tab.prenom,&tab.CIN,tab.adresse,&tab.telephone);
            if(tab.idClient == id){
                fclose(fichier);
                return 1;
            }
            fclose(fichier);
            return 0;
        }while(!feof(fichier));
    }
    return 0;
}
// RECHERCHE CONTRAT A L'AIDE DU ID VOITURE RETOURNE
int recherche_contrat(int id)
{
 contrat tab;
 FILE *fichier=NULL;
 fichier=fopen("contrat.txt","r");
 if(fichier){
 	do{
	 	fscanf(fichier,"%f\n%d\n%d\n%d %d %d \n %d %d %d \n %d \n",&tab.numContrat,&tab.idVoiture,&tab.idClient,tab.date_debut.jj,tab.date_debut.mm,tab.date_debut.aaaa,tab.date_fin.jj,tab.date_fin.mm,tab.date_fin.aaaa,tab,&tab.lecout);
	 if(tab.idVoiture=id){
	 	fclose(fichier);
	 	return 1;
	 }
	 fclose(fichier);
	 return 0;
	 }while(feof(fichier));
 }
 return 0;
}


#endif // FOCTION_H_INCLUDED
