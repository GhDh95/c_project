#include "functions_users.h"


int main(){

	char input; 

	while(1){
		printf("1: add user.\n"); 
		printf("2: display all users.\n"); 
		printf("3: display filtered users.\n");
		printf("4: edit user by id.\n");
		printf("5: delete user by id.\n"); 
		printf("6: statistics.\n");   
		printf("x: exit.\n"); 
		scanf(" %c", &input); 

		switch(input){
			case '1': 
				add_user(); 
				break; 
			case '2': 
				display_all_users(); 
				break;
			case '3':
				display_filtered_users();
				break;   
			case '4': 
				edit_user(); 
				break; 
			case '5': 
				delete_user();
				break; 
			case '6':
				show_stats();
				break; 
			case 'x':
				exit(0);
			default:
				printf("give valid input.\n");
				break;  
		}
	}
	



	return 0; 
}
