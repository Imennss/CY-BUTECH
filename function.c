#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct{
    char user[50];
    char mdp[50];
    int role;
    int nbEmprunt;
    int nbPenalite;
}User;

typedef struct{
    char titre[100];
    char auteur[100];
    int numeroId;
    char categorie[100];
}Livre;

typedef struct{
    int presence;
    int ID;
    char emprunteur[100];
    char empTitre[100];
    char empAuteur[100];
}Emprunt;


int verifMdp(User*tab, char nomUt[50], char password[50] );

/** Cette fonction permet de récupérer les données des utilisateurs
et de les stocker dans un tableau de structure User */

User *LireUsers(){
    
    User*tab = NULL;
    
    FILE *fichier = fopen("users.txt","r");
    
    if (fichier == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    
    //on crée un tableau de structure :
    
    tab = malloc(10* sizeof(User));
    
    //on y entre les données des utilisateurs contenues dans le fichier :
    
    for(int i=0; i<10; i++){
        fscanf(fichier, "%s", tab[i].user);
        fscanf(fichier, "%s", tab[i].mdp);
        fscanf(fichier, "%d", &tab[i].role);
        fscanf(fichier, "%d", &tab[i].nbEmprunt);
        fscanf(fichier, "%d", &tab[i].nbPenalite);
    }

    
    fclose(fichier);
    
    return tab;
    
}



/** Cette fonction permet de récupérer les données des livres
et de les stocker dans un tableau de structure Livre */
Livre *LireLivres(){
    
    Livre*tabLivres = NULL;
    
    FILE *fichier = fopen("livres.txt","r");
    
    if (fichier == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    
    //on crée un tableau de structure :
    
    tabLivres = malloc(10* sizeof(Livre));
    
    //on y entre les données des utilisateurs contenues dans le fichier :
    
    for(int i=0; i<10; i++){
        fscanf(fichier, "%s", tabLivres[i].titre);
        fscanf(fichier, "%s", tabLivres[i].auteur);
        fscanf(fichier, "%d", &tabLivres[i].numeroId);
        fscanf(fichier, "%s", tabLivres[i].categorie);
    }

    
    fclose(fichier);
    
    return tabLivres;
    
}


/** Cette fonction permet de récupérer les données des emprunts
et de les stocker dans un tableau de structure Emprunt */
Emprunt *LireEmprunts(){
    
    Emprunt*tabEmprunts = NULL;
    
    FILE *fichier = fopen("emprunts.txt","r");
    
    if (fichier == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    
    //on crée un tableau de structure Emprunt :
    
    tabEmprunts = malloc(10* sizeof(Emprunt));
    
    //on remplit le tableau avec les données des emprunts contenues dans le fichier :
    
    for(int i=0; i<10; i++){
        fscanf(fichier, "%d", &tabEmprunts[i].presence);
        fscanf(fichier, "%d", &tabEmprunts[i].ID);
        fscanf(fichier, "%s", tabEmprunts[i].emprunteur);
        fscanf(fichier, "%s", tabEmprunts[i].empTitre);
        fscanf(fichier, "%s", tabEmprunts[i].empAuteur);
    }
    
    fclose(fichier);
    
    return tabEmprunts;
    
}


/** Cette fonction permet de vérifier le mot de passe
Elle renvoie 1 si le mot de passe est correct, et 0 si il est incorrect*/

int verifMdp(User*tab, char nomUt[50], char password[50] ){
    
    int n = 0;
    int res = 0;
    
        
    while (strcmp(nomUt,tab[n].user)!=0){
        n=n+1;
    }
    
    if (strcmp(password,tab[n].mdp)==0){
        res = 1;
        printf(" \nMot de passe correct\n");
    }
    else{
        printf(" \nMot de passe incorrect. Réeassayer\n");
        res = 0;
    }
    return res;
}


/*** Fonction qui permet de rechercher l'indice du nom d'utilisateur dans un tableau de structure User
Retourne la valeur de l'indice*/
int rechercheUtilisateur(char nomAchercher[50], User* tabUtilisateur){
    
    int indice = -1;
    
    for(int i=0; i<10; i++){
        if (strcmp(nomAchercher,tabUtilisateur[i].user)==0){
            indice = i;
            break;
        }
    }
    if(indice == -1){
            printf("Utilisateur introuvable\n");
        }
        
    return indice;
}


/*** Fonction qui permet de rechercher l'indice d'un livre dans un tableau de structure Livre
Retourne la valeur de l'indice*/
int rechercheLivre(char livreAchercher[50], Livre* tabLivre){
    
    int indice = -1;
    
    for(int i=0; i<10; i++){
        if (strcmp(livreAchercher,tabLivre[i].titre)==0){
            indice = i;
            break;
        }
    }
    if (indice==-1){
        printf("Livre introuvable");
    }
    
    return indice;
}


/*** Fonction qui permet de rechercher l'ID d'un livre dans un tableau de structure Livre
Retourne la valeur de l'ID*/
int rechercheLivreID(char livreAchercher[70], Livre* tabLivre){
    
    
    for(int i=0; i<10; i++){
        if (strcmp(livreAchercher,tabLivre[i].titre)==0){
          
            return tabLivre[i].numeroId;
        }
    }
    printf("\nCe livre n'existe pas. Veuillez respecter l'orthographe et les underscores.\n");
    
    return 0;
}


/*** Fonction qui permet de rechercher l'indice d'un livre dans un tableau de structure Emprunt
Retourne la valeur de l'indice*/
int rechercheEmpruntID(int idLivre, Emprunt* tabEmprunt){
    
    int indice = -1;
    
    for(int i=0; i<10; i++){
        if (idLivre==tabEmprunt[i].ID){
            indice = i;
       
            break;
        }
    }
    

    return indice;
}


/*** Fonction qui permet de rechercher le nom d'un livre dans un tableau de structure Emprunt
Retourne la valeur de l'indice*/
int rechercheEmprunt(char empruntAchercher[100], Emprunt* tabEmprunt){
    
    int indice = -1;
    
    for(int i=0; i<10; i++){
        if (strcmp(empruntAchercher,tabEmprunt[i].empTitre)==0){
            indice = i;
    
            break;
        }
    }
    if (indice!=-1){
        printf("\nCe livre n'est pas empruté.\n");
    }
    
    return indice;
}





/*Fonction qui permet d'actualiser le contenu du fichier après avoir fait des modifications
Prend en paramètre un tableau de type User*/

void actualiserUsers(User *tableau){
    
    int n; //nombre d'utilisateur présent dans le tableau
    int i = 0;
    
    FILE *fichier = fopen("users.txt","w");
    
    if (fichier == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    
    for(int j=0; j<10; j++){
        while (tableau[i].role==1){
            fprintf(fichier, "%s %s %d %d %d\n", tableau[i].user, tableau[i].mdp, tableau[i].role, tableau[i].nbEmprunt, tableau[i].nbPenalite );
            i++;
        }
    }
    fprintf(fichier, "\n");
    
    fclose(fichier);
}


/* Fonction qui permet d'actualiser le contenu du fichier après avoir fait des modifications
Prend en paramètre un tableau de type User*/

void actualiserEmprunts(Emprunt *tableau){
    
    int n;
    int i = 0;
    
    FILE *fichier = fopen("emprunts.txt","w");
    
    if (fichier == NULL){
        printf("Ouverture du fichier impossible\n");
        printf("code d'erreur= %d \n", errno);
        exit(1);
    }
    
    for(int j=0; j<10; j++){
        while (tableau[i].presence==1){
            fprintf(fichier, "%d %d %s %s %s\n", tableau[i].presence, tableau[i].ID, tableau[i].emprunteur, tableau[i].empTitre, tableau[i].empAuteur );
            i++;
        }
    }
    fprintf(fichier, "\n");
    
    fclose(fichier);
}



/*Cette fonction permet de retirer un élément de la liste d'emprunt. Autrement dit, cette fonction
est utiliser dans le but de "rendre" un livre.
Elle prend en paramètres: -la liste/tableau d'emprunts
                          -l'indice de l'élément(du livre) à supprimer */
Emprunt *supprimerUnEmprunt(Emprunt *tabEmprunt, int indiceEmpruntSupp){
    for(int i = indiceEmpruntSupp ; i<9; i++){
        tabEmprunt[i] = tabEmprunt[i+1];
    }
    

    
    return tabEmprunt;
}

