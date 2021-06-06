#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"structure.h"
#include"prototype.h"
#include"foction.h"
// visualiser le contrat du client
void visualiser_contrat()
{
    float num;
    contrat g;
    FILE *fichier = NULL;
    printf("Donnez le numero du contrat :");
    scanf("%f",&num);
    fichier = fopen("Contrats","r");
    if(fichier != NULL){
        do{
            fscanf(fichier,"%f ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d \n",&g.numContrat,&g.idVoiture,&g.idClient,&g.date_debut.jj,&g.date_debut.mm,&g.date_debut.aaaa,&g.date_fin.jj,&g.date_fin.mm,&g.date_fin.aaaa);
        }while(g.numContrat!=num && !feof(fichier));
        if(g.numContrat != num) //verification si le num_contrat exist
            printf("no contrat de cet numero");
        else{
            printf("id de la voiture :%d\n",g.idVoiture);
            printf("id du client :%d\n",g.idClient);
            printf("date de location :%d/%d/%d\n",g.date_debut.jj,g.date_debut.mm,g.date_debut.aaaa);
            printf("date de retourne de la voiture:%d/%d/%d\n",g.date_fin.jj,g.date_fin.mm,g.date_fin.aaaa);
            printf("cout :%d",g.lecout);
        }
        fclose(fichier);
    }
}

// louer une voiture a un client
void louer_voiture()
{
    FILE *fichier,*f;
    contrat g;
    voiture v;
    char choix;
    fichier = fopen("Contrat","a+");
    if(fichier != NULL){
        system("cls");
        printf("numero de contrat :");
        scanf("%f",&g.numContrat);
        printf("l'id de la voiture:");
        scanf("%d",&g.idVoiture);
        //cherche une voiture a louer
        while(chercheV(g.idVoiture) != 1){
            if(chercheV(g.idVoiture) == 0){
                printf("Excusez moi ,il na pas une voiture de cet id\n");
                printf("Voulez-Vous continuer l'ajout d'un contrat o/n:");
                scanf("%c",&choix);
                if(choix == 'o' || choix == 'O'){
                    system("cls");
                    printf("Contrat numero:%d\nl'id de la voiture:",g.numContrat);
                    scanf("%d",&g.idVoiture);
                }
                else {fclose(fichier); return 0;}
            }
            if(chercheV(g.idVoiture) == 2){
                printf("Cette voiture est deja en location\n");
                fclose(fichier);
                return 0;
            }
        }
        printf("L'id du client :");//verification si client existe
        scanf("%d",&g.idClient);
        while(chercheC(g.idClient) == 0){
            printf("Excusez moi ,le client n'existe pas \n");
            printf("Voulez-Vous continuer l'ajout d'un contrat o/n:");
            scanf("%c",&choix);
            if(choix == 'o' || choix == 'O'){
                system("cls");
                printf("Contrat numero:%d\nl'id de la voiture:%d\n",g.numContrat,g.idVoiture);
                printf("L'id du client:");
                scanf("%d",&g.idClient);
            }
            else {fclose(fichier); return 0;}
        }
        printf("Quelle est la dat de debut :(separer les champs de la adte par espace)");
        scanf("%d %d %d",&g.date_debut.jj,&g.date_debut.mm,&g.date_debut.aaaa);
        printf("Quelle est la date de retournage du voiture:");
        scanf("%d %d %d",&g.date_fin.jj,&g.date_fin.mm,&g.date_fin.aaaa);
        printf("cout :");
        scanf("%d",&g.lecout);
        fprintf(fichier,"%f ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d \n",g.numContrat,g.idVoiture,g.idClient,g.date_debut.jj,g.date_debut.mm,g.date_debut.aaaa,g.date_fin.jj,g.date_fin.mm,g.date_fin.aaaa,g.lecout);
        fclose(fichier);
        fichier = fopen("Voitures","r");
        f = fopen("temporaire","a");
        if(fichier != NULL && f != NULL){
            while(!feof(fichier)){
                fscanf(fichier,"%d ;%s ;%s ;%s ;%d ;%d ;%s \n",&v.idVoiture,v.marque,v.nomVoiture,v.couleur,&v.nbplaces,&v.prixJour,v.EnLocation);
                if(v.idVoiture == g.idVoiture)
                    fprintf(f,"%d ;%s ;%s ;%s ;%d ;%d ;oui \n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour);
                else
                    fprintf(f,"%d ;%s ;%s ;%s ;%d ;%d ;%s \n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
            }
            fclose(fichier);
            fclose(f);
            remove("Voitures"),
            rename("temporaire","Voitures");
        }
    }
}

//////// FONCTION POUR RETOURNER UNE VOITURE DEJA LOUEE
void Retourner_voiture()
{
int IdRetourn;
FILE* voitures;
voiture V;
printf(" Saisir le Id de voiture a retourne \n");
scanf("%d",&IdRetourn);
voitures=fopen("voitures.txt","w");
do{
fscanf(voitures,"%s\n%d\n%s\n%s\n%d\n%d\n%s\n",&V.marque,&V.idVoiture,&V.nomVoiture,&V.couleur,&V.nbplaces,&V.prixJour,&V.EnLocation);
	if(V.idVoiture==IdRetourn){
	strcpy(V.EnLocation,"Non"); // on change l'etat de cette voiture
	// LA VOITURE N'EST PLUS DISPONIBLE DONC ON SUPPRIME LE CONTRAT
	Supprimer_Contrat(IdRetourn);
	}
}while(!feof(voitures));
}
//modifier contrat de voiture
void modifier_contrat()
{
    FILE *fichier = NULL;
    contrat tab[100];
    int i,j,choix,fin=0;
    float id;
    fichier =fopen("Voitures","r+");
    if (fichier != NULL){
        printf("donnez le numero de contrat que vous avez changer:");
        scanf("%f",&id);
        for(i=0;!feof(fichier);i++){
            fscanf(fichier,"%f ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d \n",&tab[i].numContrat,&tab[i].idVoiture,&tab[i].idClient,&tab[i].date_debut.jj,&tab[i].date_debut.mm,&tab[i].date_debut.aaaa,&tab[i].date_fin.jj,&tab[i].date_fin.mm,&tab[i].date_fin.aaaa,&tab[i].lecout);
            if(tab[i].idVoiture == id){
                    while(fin){
                do{ system("cls");
                    printf("numero de contrat :%f\n.1",tab[i].numContrat);
                    printf("id du voiture :%d\n.....2",tab[i].idVoiture);
                    printf("id du client :%d\n......3",tab[i].idClient);
                    printf("date debut :%d/%d/%d\n..4",tab[i].date_debut.jj,tab[i].date_debut.mm,tab[i].date_debut.aaaa);
                    printf("date fin :%d/%d/%d\n...5",tab[i].date_fin.jj,tab[i].date_fin.mm,tab[i].date_fin.aaaa);
                    printf("cout :%d...............6\n",tab[i].lecout);
                    printf("retour.................0\n");
                    printf("votre vhoix :");
                    scanf("%d",&choix);
                }while(choix<0 || choix>6);
                switch (choix)
                {
                    case 0:fin++;
                    case 1:
                        printf("donnez le nouveau numero :");
                        scanf("%d",&tab[i].numContrat);
                    case 2:
                        printf("donnez le nouveau id du voiture :");
                        scanf("%d",&tab[i].idVoiture);
                        if(chercheC(tab[i].idVoiture) == 0)
                            printf("Excusez moi ,il na pas une voiture de cet id\n");
                    case 3:
                        printf("donnez le nouveau id du client :");
                        scanf("%d",&tab[i].idClient);
                        if(chercheC(tab[i].idClient) == 0)
                            printf("Excusez moi ,il na pas un client de cet id\n");
                    case 4:
                        printf("donnez le nouveau date debut :");
                        scanf("%d %d %d",&tab[i].date_debut.jj,&tab[i].date_debut.mm,&tab[i].date_debut.aaaa);
                    case 5:
                        printf("donnez le nouveau date fin :");
                        scanf("%d %d %d",&tab[i].date_debut.jj,&tab[i].date_debut.mm,&tab[i].date_debut.aaaa);
                    case 6:
                        printf("donnez le nouveau cout :");
                        scanf("%d",&tab[i].lecout);
                }
            }
        }}j = i;//nombre de contrats
        fclose(fichier);
        fichier = fopen("Contrats","w");
        if(fichier != NULL){
            for(i=0;i<j;i++)
                fprintf(fichier,"%f ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d ;%d \n",tab[i].numContrat,tab[i].idVoiture,tab[i].idClient,tab[i].date_debut.jj,tab[i].date_debut.mm,tab[i].date_debut.aaaa,tab[i].date_fin.jj,tab[i].date_fin.mm,tab[i].date_fin.aaaa,tab[i].lecout);
        }
        fclose(fichier);
    }
}



//FONCTION DE RECHERCHE D UN CONTRAT D'APRES LE id DE VOITURE LOUEE
int recherche_Contrat(int Num){
FILE *F;
contrat cont;
F=fopen("contrats.txt","r");
do{
fscanf(F,"%f\n%d\n%d\n%d %d %d \n %d %d %d \n %d \n",&cont.numContrat,&cont.idVoiture,&cont.idClient,cont.date_debut.jj,cont.date_debut.mm,cont.date_debut.aaaa,cont.date_fin.jj,cont.date_fin.mm,cont.date_fin.aaaa,cont.lecout);
fflush(stdin);
	if(cont.idVoiture==Num){
    fclose(F);
    return 1;
 	}
   }while(!feof(F));
fclose(F);
return -1;  // s il ne trouve pas le  id de contrat
}
void Supprimer_Contrat()
{
 contrat cont ;
 int Id;
 printf("veuillez saisir id de la voiture dont laquel vous voulez supprimer le contrat \n");
 scanf("%d",&Id);

	 if(recherche_Contrat(Id)==1)
	 { FILE *temp,*R;
	 R=fopen("contrats.txt","r");
	 temp=fopen("tempContrat.txt","a");
		 do{
	     fscanf(R,"%f\n%d\n%d\n%d %d %d \n %d %d %d \n %d \n",&cont.numContrat,&cont.idVoiture,&cont.idClient,cont.date_debut.jj,cont.date_debut.mm,cont.date_debut.aaaa,cont.date_fin.jj,cont.date_fin.mm,cont.date_fin.aaaa,cont,&cont.lecout);
			 if(Id!=cont.idVoiture){
			 fprintf(temp,"%f\n%d\n%d\n%d %d %d \n %d %d %d \n %d \n",cont.numContrat,cont.idVoiture,cont.idClient,cont.date_debut.jj,cont.date_debut.mm,cont.date_debut.aaaa,cont.date_fin.jj,cont.date_fin.mm,cont.date_fin.aaaa,cont,cont.lecout);
			 }
		 }while(!feof(R));
	 fclose(temp);
	 fclose(R);
	 remove("contrats.txt");
	 rename("tempContrat.txt","contrats.txt");
	 }
	 else{
	 	printf("ce id n existe pas \n");
     }
}

#endif // LOCATION_H_INCLUDED
