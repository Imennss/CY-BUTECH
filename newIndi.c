#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "function.h"


#define P printf
#define S scanf

typedef struct{
    int localH;
    int localMin;
    int localS;
}localHour;


void newAcc(){
    
    int c = 0;
    int r;
    int l = 0;
    int n = 0;
    int verif = 0;
    int indiceUtilisateur = 0;
    int indiceLivre = 0;
    int indiceEmprunt = 0;
    int indiceRendre = 0;
    int indiceDuLivreARendre = 0;
    int numeroIDemprunt = 0;
    
    char nomUt[20];
    char password[20];
    char livre[30];
    char livreArendre[50];
    char newLivre[50];
    char livreAemprunter[70];

    
    User* users = NULL;
    Livre* livres = NULL;
    Emprunt* emprunts = NULL;
    Emprunt* nouveauEmprunts = NULL;
    
    FILE *f1 = NULL;
    FILE *f2 = NULL;
    FILE *fnewIndi = NULL;
    FILE *femprunt = NULL;
    
    //OVERTURE DU FICHIER LIVRE.TXT EN MODE LECTURE POUR L'AFFICHAGE DANS LE TERMINAL
    f1 = fopen("livres.txt","r");
    //OVERTURE DU FICHIER LIVRE.TXT EN MODE LECTURE POUR L'AJOUT DANS LA LISTE PAR UN PROFESSEUR
    f2 = fopen("livres.txt","a+");
    fnewIndi = fopen("users.txt","a+");
    femprunt = fopen("emprunts.txt","a+");
    
    if (f1 == NULL){
        printf("Ouverture du fichier impossible");
        exit(1);
    }
    if (f2 == NULL){
        printf("Ouverture du fichier impossible");
        exit(1);
    }
    if (fnewIndi == NULL){
        printf("Ouverture du fichier impossible");
        exit(1);
    }
    if (femprunt == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    
    
    
    do{
        //L'UTILISATEUR CHOISI SON PROFIL
        P("\nchoisir \n1-etudiant  ou \n2-professeur");
        S("%d",&r);
    }
    while(r != 1 && r != 2);
    
    //CREATION DU COMPTE
    
    printf("Créez votre nom d'utilsateur :  ");
    scanf("%s", nomUt);
    printf("Créez votre mot de passe :  ");
    scanf("%s", password);
    fprintf(fnewIndi,"\n%s   %s   1 0 0",nomUt,password);
    
    users = LireUsers();

    
    P("\n\n*****************************************");
    P("\n\n     HELLOWWWWW TO CY-BU %s  ",nomUt);
    P("\n\n*****************************************");
    
    P ("\n\nQeulle action voulez-vous faire ?");
    
    
    do{
        // ---------------------------------DANS LE CAS OU C'EST UN ETUDIANT-------------------------------//
        
        if(r == 1){
            
            P("\n\n1. Emprunter un livre \
                 \n2. Rendre un livre \
                 \n3. Se déconnecter");
            S("%d",&c);
            
            livres = LireLivres();
            emprunts = LireEmprunts();
            
            if(c == 1){
                
                /*CAS OU L'ETUDIANT SOUHAITE EMPRUNTÉ UN LIVRE*/
                
                double t;
                int h,min, s;
                time_t now;
                
                P("\n\nvoici le choix des livres : \n\n");
                while((l = fgetc(f1)) != EOF){
                    P("%c",l);
                }
                
                P("\nsaisir le titre du livre à emprunter \
                    [avec des _ à la place des espaces]\n");
                S("%s",livreAemprunter);
                
                indiceLivre = rechercheLivre(livreAemprunter, livres);
                
                if(users[indiceUtilisateur].nbEmprunt>=3){
                    printf("Vous ne pouvez pas emprunter de nouveau livre, rendez en un d'abord!");
                }
                else if(rechercheEmpruntID(livres[indiceLivre].numeroId, emprunts)!=-1){
                    printf("\nCe livre est déjà emprunté, DESOLE.\n");
                    printf("\nChoisir un autre livre\n ");
                    
                }
                else{
                    fprintf(femprunt, "\n%d %s %s %s\n", livres[indiceLivre].numeroId, users[indiceUtilisateur].user, livres[indiceLivre].titre, livres[indiceLivre].auteur);
                    printf("\nLivre emprunté avec succès! Vous devez le rendre avant...\n");
                    users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt + 1;
                    
                    time(&now);
                    localHour *local = localtime(&now);
                    h = local->localH;
                    min = local->localMin;
                    s = local->localS;
                    P("%s vous avez emprunté %s à heure : %02d:%02d:%02d \
                    \n Vous avez 2 min avec ce livre\n",nomUt, livreAemprunter, s, min, h);
//                    sleep(120);
                    P("vous devez rendre %s",livreAemprunter);
                }
                actualiserUsers(users);
            }
            
            
            else if(c == 2){
                P("saisir le titre du livre à rendre \
                    [avec des _ à la place des espaces]");
                S("%s",livreArendre);
                
                numeroIDemprunt = rechercheLivreID(livreArendre, livres);
                
             
                indiceRendre = rechercheEmpruntID(numeroIDemprunt, emprunts);
                
                if(strcmp(emprunts[indiceRendre].emprunteur,nomUt)==0){
                    printf("\nVous n'avez pas emprunté ce livre!!\n");
                }
                else{
                    nouveauEmprunts = supprimerUnEmprunt(emprunts, indiceRendre);
                    printf("\nLivre rendu avec succès !!\n");
                    actualiserEmprunts(nouveauEmprunts);
                    users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt - 1;
                    actualiserUsers(users);
                    
                }
            }
            else{
                P("\n\n\n      SEE YOUUU SOON IN CY-BU %s",nomUt);
            }
        }
        
        // ---------------------------------DANS LE CAS OU C'EST UN PROFESSEUR-------------------------------//

        
        if(r == 2){
                    
            P("\n\n1. Emprunter un livre \
                 \n2. Rendre un livre \
                 \n3. Rajouter un livre \
                 \n4. Se déconnecter");
            S("%d",&c);
            
            switch(c){
                    double t;
                    int h,min,s;
                    time_t now;
                    
                case 1:
                    //LE CAS OU LE LIVRE VA ETRE EMPRUNTE
                    livres = LireLivres();
                    emprunts = LireEmprunts();
                    
                    P("\n\nvoici le choix des livres : \n\n");
                    while((l = fgetc(f1)) != EOF){
                        P("%c",l);
                    }

                    
                    P("\nsaisir le titre du livre à emprunter \
                        [avec des _ à la place des espaces]\n");
                    S("%s",livreAemprunter);
                    
                    indiceLivre = rechercheLivre(livreAemprunter, livres);
                    
                    if(users[indiceUtilisateur].nbEmprunt>=5){
                        printf("Vous ne pouvez pas emprunter de nouveau livre, rendez en un d'abord!");
                    }
                    else if(rechercheEmpruntID(livres[indiceLivre].numeroId, emprunts)!=-1){
                        printf("\nCe livre est déjà emprunté, DESOLE.\n");
                        printf("\nChoisir un autre livre\n ");
                        
                    }
                    else{
                        fprintf(femprunt, "\n%d %s %s %s\n", livres[indiceLivre].numeroId, users[indiceUtilisateur].user, livres[indiceLivre].titre, livres[indiceLivre].auteur);
                        printf("\nLivre emprunté avec succès! Vous devez le rendre avant...\n");
                        users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt + 1;
                        
                        time(&now);
                        localHour *local = localtime(&now);
                        h = local->localH;
                        min = local->localMin;
                        s = local->localS;
                        P("%s vous avez emprunté %s à heure : %02d:%02d:%02d \
                        \n Vous avez 2 min avec ce livre\n",nomUt, livre, s, min, h);
        //                    sleep(120);
                        P("vous devez rendre %s",livre);
                        
                    }
                    actualiserUsers(users);
                
                    break;
                    
                    
                case 2:
                    //LE CAS OU LE LIVRE VA ETRE RENDU
                    P("saisir le titre du livre à rendre \
                        [avec des _ à la place des espaces]");
                    S("%s",livreArendre);
                    P("\n\n%s vous avez rendu : %s",nomUt,livreArendre);
                    
                    numeroIDemprunt = rechercheLivreID(livreArendre, livres);
                    
                 
                    
                    indiceRendre = rechercheEmpruntID(numeroIDemprunt, emprunts);
                    
                    if(strcmp(emprunts[indiceRendre].emprunteur,nomUt)==0){
                        printf("\nVous n'avez pas emprunté ce livre!!\n");
                    }
                    else{
                        nouveauEmprunts = supprimerUnEmprunt(emprunts, indiceRendre);
                        printf("\nLivre rendu avec succès !!\n");
                        actualiserEmprunts(nouveauEmprunts);
                        users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt - 1;
                        actualiserUsers(users);
                        
                    }
                    break;
                    
                    
                case 3:
                    //LE CAS OU LE PROFESSEUR VA RAJOUTER UN LIVRE A LA LISTE
                    P("saisir [Titre]_[Auteur]_[Num d'id]_[Catégorie] du livre");
                    S("%s",newLivre);
                    fprintf(f2,"\n%s   ",newLivre);
                    P("\n\n%s vous avez ajouté : %s",nomUt,newLivre);
                    
                    break;
                    
                    
                case 4:
                    //LE CAS LE PROF SE DECONNECTE
                    P("\n\n\n    SEE YOUUU SOON IN CY-BU %s\n",nomUt);
                    break;
                    
                default:
                    P("vous avez été déconnecté il faut choisir entre 1.  2.  3. ou 4.");
                    break;
            }
        }
        
        
    }while(c != 3 && c != 4);
    
    

    fclose(f1);
    fclose(f2);
    fclose(fnewIndi);
    fclose(femprunt);


    
}

