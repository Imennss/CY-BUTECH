#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "function.h"


#define P printf
#define S scanf
#define login nomUt



            /* DANS CE FICHIER ON S'EST OCCUPÉ DES CONNEXIONS CÀD DES
             COMPTES DEJA EXISTANTS QUE L'ON A SEPARE EN DEUX CAS SELON SI
                        C'EST UN PROFESSEUR OU UN ÉTUDIANT*/

typedef struct{
    int localH;
    int localMin;
    int localS;
}localHour;


void seCo(){
    
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
    
    FILE *femprunt = fopen("emprunts.txt","a+");
    //OVERTURE DU FICHIER LIVRE.TXT EN MODE LECTURE POUR L'AFFICHAGE DANS LE TERMINAL
    FILE *f1 = fopen("livres.txt","r");
    //OVERTURE DU FICHIER LIVRE.TXT EN MODE LECTURE POUR L'AJOUT DANS LA LISTE PAR UN PROFESSEUR
    FILE *f2 = fopen("livres.txt","a+");
    
    if (femprunt == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    if (f1 == NULL){
        printf("Ouverture du fichier impossible");
        exit(1);
    }
    if (f2 == NULL){
        printf("Ouverture du fichier impossible");
        exit(1);
    }

    
    
    

    do{
        //L'UTILISATEUR CHOISI SON PROFIL
        P("\nchoisir \n1-etudiant  ou \n2-professeur");
        S("%d",&r);
    }
    while(r != 1 && r != 2);
    
    do{
        printf("Tapez votre nom d'utilsateur :  ");
        scanf("%s", nomUt);
        printf("Tapez votre mot de passe :  ");
        scanf("%s", password);
        
        //VERIFICATION DE SON MOT DE PASSE ET NOM D'UTILISATEUR
    
        users = LireUsers();
    
        indiceUtilisateur = rechercheUtilisateur(nomUt,users);
    
        if (indiceUtilisateur == -1){
            printf("\nVeillez réessayer avec un nom correct, pensez à respecter les majuscules\n");
        }
        else{
            verif = verifMdp(users, nomUt, password);
        }
    }while (indiceUtilisateur == -1 || verif == 0);
    
    P("\n\n*****************************************");
    P("\n\n     HELLOWWWWW TO CY-BU %s  ",login);
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
                
                P("\n\nsaisir le titre du livre à emprunter \
                    \n[avec des _ à la place des espaces]\n");
                S("%s",livreAemprunter);
                
                indiceLivre = rechercheLivre(livreAemprunter, livres);
                
                if(users[indiceUtilisateur].nbEmprunt>=3){
                    printf("\n\nVous ne pouvez pas emprunter de nouveau livre, rendez en un d'abord!");
                }
                else if(rechercheEmpruntID(livres[indiceLivre].numeroId, emprunts)!=-1){
                    printf("\n\nCe livre est déjà emprunté, DESOLE.\n");
                    printf("\n\nChoisir un autre livre\n ");
                    
                }
                else{
                    fprintf(femprunt, "%d %s %s %s\n", livres[indiceLivre].numeroId, users[indiceUtilisateur].user, livres[indiceLivre].titre, livres[indiceLivre].auteur);
                    printf("\n\nLivre emprunté avec succès! Vous devez le rendre avant...\n");
                    users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt + 1;
                    
                    time(&now);
                    localHour *local = localtime(&now);
                    h = local->localH;
                    min = local->localMin;
                    s = local->localS;
                    P("\n\n%s vous avez emprunté %s à heure : %02d:%02d:%02d \
                    \n Vous avez 2 min avec ce livre\n",login, livreAemprunter, s, min, h);
//                    sleep(120);
                    P("\n\n%s vous devez rendre %s",login,livreAemprunter);
                }
                actualiserUsers(users);
                
            }
            else if(c == 2){

                
                P("\n\nsaisir le titre du livre à rendre \
                    \n[avec des _ à la place des espaces]");
                S("%s",livreArendre);
                
                numeroIDemprunt = rechercheLivreID(livreArendre, livres);
                
             
                
                indiceRendre = rechercheEmpruntID(numeroIDemprunt, emprunts);
                
                if(strcmp(emprunts[indiceRendre].emprunteur,nomUt)==0){
                    printf("\n\nVous n'avez pas emprunté ce livre!!\n");
                }
                else{
                    nouveauEmprunts = supprimerUnEmprunt(emprunts, indiceRendre);
                    printf("\n\nLivre rendu avec succès !!\n");
                    actualiserEmprunts(nouveauEmprunts);
                    users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt - 1;
                    actualiserUsers(users);
                    
                }
                
            }
            else{
                P("\n\n\n    SEE YOUUU SOON IN CY-BU %s\n",login);
            }
        }
        
        
// ---------------------------------DANS LE CAS OU C'EST UN PROFESSEUR-------------------------------//
        
        if(r == 2){
            //LE PROF CHOISI ICI PARMIS LES DIFFERENTES POSSIBILITES
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

                    
                    P("\n\nsaisir le titre du livre à emprunter \
                        [avec des _ à la place des espaces]\n");
                    S("%s",livreAemprunter);
                    
                    indiceLivre = rechercheLivre(livreAemprunter, livres);
                    
                    if(users[indiceUtilisateur].nbEmprunt>=3){
                        printf("\n\nVous ne pouvez pas emprunter de nouveau livre, rendez en un d'abord!");
                    }
                    else if(rechercheEmpruntID(livres[indiceLivre].numeroId, emprunts)!=-1){
                        printf("\n\nCe livre est déjà emprunté, DESOLE.\n");
                        printf("\n\nChoisir un autre livre\n ");
                        
                    }
                    else{
                        fprintf(femprunt, "\n%d %s %s %s\n", livres[indiceLivre].numeroId, users[indiceUtilisateur].user, livres[indiceLivre].titre, livres[indiceLivre].auteur);
                        printf("\n\nLivre emprunté avec succès! Vous devez le rendre avant...\n");
                        users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt + 1;
                        
                        time(&now);
                        localHour *local = localtime(&now);
                        h = local->localH;
                        min = local->localMin;
                        s = local->localS;
                        P("\n\n%s vous avez emprunté %s à heure : %02d:%02d:%02d \
                        \n Vous avez 2 min avec ce livre\n",login, livre, s, min, h);
        //                    sleep(120);
                        P("\n\n%s vous devez rendre %s",login,livre);
                        
                    }
                    actualiserUsers(users);
                    
                
                    break;
            
                case 2:
                    //LE CAS OU LE LIVRE VA ETRE RENDU
                    P("\n\nsaisir le titre du livre à rendre \
                        \n[avec des _ à la place des espaces]");
                    S("%s",livreArendre);
                    
                    numeroIDemprunt = rechercheLivreID(livreArendre, livres);
                    
                 
                    
                    indiceRendre = rechercheEmpruntID(numeroIDemprunt, emprunts);
                    
                    if(strcmp(emprunts[indiceRendre].emprunteur,nomUt)==0){
                        printf("\n\nVous n'avez pas emprunté ce livre!!\n");
                    }
                    else{
                        nouveauEmprunts = supprimerUnEmprunt(emprunts, indiceRendre);
                        printf("\n\nLivre rendu avec succès !!\n");
                        actualiserEmprunts(nouveauEmprunts);
                        users[indiceUtilisateur].nbEmprunt= users[indiceUtilisateur].nbEmprunt - 1;
                        actualiserUsers(users);
                        
                    }
                    break;
                    
                    
                case 3:
                    //LE CAS OU LE PROFESSEUR VA RAJOUTER UN LIVRE A LA LISTE
                    P("\n\nsaisir [Titre]_[Auteur]_[Num d'id]_[Catégorie] du livre");
                    S("%s",newLivre);
                    fprintf(f2,"\n%s   ",newLivre);
                    P("\n\n%s vous avez ajouté : %s",login,newLivre);
                    
                    break;
                    
                    
                case 4:
                    //LE CAS LE PROF SE DECONNECTE
                    P("\n\n\n    SEE YOUUU SOON IN CY-BU %s\n",login);
                    break;
                    
                default:
                    P("\n\nvous avez été déconnecté il faut choisir entre 1.  2.  3. ou 4.");
                    break;
            }
        }
        
    }
    while(c != 3 && c != 4);
    
    

        
    fclose(f1);
    fclose(f2);

}


