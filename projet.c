#include <stdio.h>
#include <stdlib.h>
#include "seCo.h"
#include "newIndi.h"
#include "function.h"
#include "seCo.h"



#define P printf
#define S scanf


int main(){

    int c,r;
    int n = 0;
    
            /*CHOIX ENTRE SE CONNECTER OU CREATION D'UN COMPTE*/
    
	do{
		P("\nchoisir \n\n1-Se connecter  ou \n2-New individu");
		S("%d",&c);
	}
	while(c != 1 && c != 2);
	
	if(c == 1){
        seCo();
	}
    else{
        newAcc();
    }
    


	return 0;
}
