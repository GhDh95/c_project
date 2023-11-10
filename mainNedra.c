#include "functions.h"


int main(){
	int input; 
	while(1){
		printf("1: ajouter don.\n"); 
		printf("2: afficher tout les dons.\n"); 
		printf("3: afficher don par id.\n"); 
		printf("4: modifier don par id.\n");
		printf("5: supprimer don par id.\n");  
		printf("0: exit. \n"); 

		scanf("%d", &input); 

		switch(input){
			case 0: 
				exit(0); 
				break; 
			case 1: 
				ajouter_don(); 
				break; 
			case 2: 
				afficher_don_tout(); 
				break; 
			case 3:
				afficher_don(); 
				break; 
			case 4: 
				modifier_don(); 
				break; 
			case 5:
				supprimer_don(); 
			default: 
				printf("choisir correct input.\n"); 
				break; 
		
		}



		
	}



	return 0; 
}
