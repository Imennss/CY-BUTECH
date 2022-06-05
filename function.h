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






/** Cette fonction permet de récupérer les données des utilisateurs
et de les stocker dans un tableau de structure User */

User *LireUsers();



/** Cette fonction permet de récupérer les données des livres
et de les stocker dans un tableau de structure Livre */
Livre *LireLivres();



/** Cette fonction permet de récupérer les données des emprunts
et de les stocker dans un tableau de structure Emprunt */
Emprunt *LireEmprunts();


/** Cette fonction permet de vérifier le mot de passe
Elle renvoie 1 si le mot de passe est correct, et 0 si il est incorrect*/

int verifMdp(User*tab, char nomUt[50], char password[50] );


/*** Fonction qui permet de rechercher l'indice du nom d'utilisateur dans un tableau de structure User
Retourne la valeur de l'indice*/
int rechercheUtilisateur(char nomAchercher[50], User* tabUtilisateur);


/*** Fonction qui permet de rechercher l'indice d'un livre dans un tableau de structure Livre
Retourne la valeur de l'indice*/
int rechercheLivre(char livreAchercher[50], Livre* tabLivre);


/*** Fonction qui permet de rechercher l'ID d'un livre dans un tableau de structure Livre
Retourne la valeur de l'ID*/
int rechercheLivreID(char livreAchercher[70], Livre* tabLivre);


/*** Fonction qui permet de rechercher l'indice d'un livre dans un tableau de structure Emprunt
Retourne la valeur de l'indice*/
int rechercheEmpruntID(int idLivre, Emprunt* tabEmprunt);


/*** Fonction qui permet de rechercher le nom d'un livre dans un tableau de structure Emprunt
Retourne la valeur de l'indice*/
int rechercheEmprunt(char empruntAchercher[100], Emprunt* tabEmprunt);





/*** Fonction qui permet d'actualiser le contenu du fichier après avoir fait des modifications
Prend en paramètre un tableau de type User*/

void actualiserUsers(User *tableau);


/*** Fonction qui permet d'actualiser le contenu du fichier après avoir fait des modifications
Prend en paramètre un tableau de type User*/

void actualiserEmprunts(Emprunt *tableau);



/*** Cette fonction permet de retirer un élément de la liste d'emprunt. Autrement dit, cette fonction
est utiliser dans le but de "rendre" un livre.
Elle prend en paramètres: -la liste/tableau d'emprunts
                          -l'indice de l'élément(du livre) à supprimer ***/
Emprunt *supprimerUnEmprunt(Emprunt *tabEmprunt, int indiceEmpruntSupp);
