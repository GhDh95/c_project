#include "functions_users.h"

void add_user(){

	user u_;
	user *u;
	u = &u_; 
	FILE *f;   
	u = get_user_input(u); 

	f = fopen("users.txt", "a+"); 
	if(f == NULL){
		printf("problem with file.\n"); 
		exit(1); 
	}else{
		fprintf(f, "%s %s %s %d %s %s %s %s\n",
		u->surname,
		u->name,
		u->cin,
		u->sex,
		u->est,
		u->role,
		u->password,
		u->tel
		); 
		fclose(f); 
	}
	
}

user * get_user_input(user *u){
	int input; 
	char p_word[LENGTH];  
	char p_word_confirm[LENGTH];
		
	do{
		printf("give surname.\n"); 
		scanf("%s", u->surname); 
		while(getchar() != '\n'); 
	}while(field_empty(u->surname) == 1);	

	do{
		printf("give name.\n"); 
		scanf("%s", u->name); 
		while(getchar() != '\n'); 
	}while(field_empty(u->name) == 1);

	do{
		printf("give national id.\n"); 
		scanf("%s", u->cin); 
		while(getchar() != '\n'); 
	}while(field_empty(u->cin) == 1 || id_unique(u->cin) == 0);

	do{
		printf("sex: 1 for m, 0 for f.\n"); 
		scanf("%d", &u->sex); 
		while(getchar() != '\n');		
	}while(u->sex != 0 && u->sex != 1); 
	
	
	printf("establishment name.\n");
	scanf("%s", u->est); 
	while(getchar() != '\n');

	do{
		printf("choose role.\n"); 
		printf("1: nurse, 2: establishment manager, 3: doctor.\n"); 
		scanf("%d", &input); 
		while(getchar() != '\n');
	}while(input != 1 && input != 2 && input != 3); 

	switch(input){
		case 1:
			strcpy(u->role, "Nurse"); 
			break;
		case 2: 
			strcpy(u->role, "EST_Manager");
			break; 
		case 3: 
			strcpy(u->role, "Doctor"); 
			break; 
				
	}
		
	do{
		printf("give password.\n"); 
		scanf("%s", p_word);
		while(getchar() != '\n');
		printf("confirm password\n"); 
		scanf("%s", p_word_confirm);  
		while(getchar() != '\n');
	}while(field_empty(p_word) == 1 || field_empty(p_word_confirm) == 1 || strcmp(p_word, p_word_confirm) != 0); 
	strcpy(u->password, p_word); 
	
	do{
		printf("give tel number.\n"); 
		scanf("%s", u->tel); 
		while(getchar() != '\n');		
	}while(field_empty(u->tel) == 1 || is_str_numeric(u->tel) ==1); 
	

	return u; 
}

void display_all_users(){
	user u_; 
	user *u;
	u = &u_; 
	int users_found = 0; 
	
	FILE *f; 
	f = fopen("users.txt", "a+"); 
	if(f == NULL){
		printf("problem accessing file.\n"); 
		exit(1); 
	}else{
		while(fscanf(f, "%s %s %s %d %s %s %*s %s",
			u->surname,
			u->name,
			u->cin,
			&u->sex,
			u->est,
			u->role,
			u->tel

		) == 7){
			char sex_ [LENGTH]; 
			u->sex == 1 ? strcpy(sex_, "male") : strcpy(sex_, "female"); 
			printf("surname: %s, name: %s, cin: %s, sex: %s, establishment: %s, role: %s, tel: %s\n", 
				u->surname,
				u->name,
				u->cin,
				sex_,
				u->est,
				u->role,
				u->tel
			); 
			users_found = 1; 

		}
			if(users_found == 0){
				printf("no available users.\n"); 
			}
		fclose(f); 
	}
}

int field_empty(char *str){
	return strlen(str) == 0 ? 1 : 0; 
}
int is_str_numeric(char *str){
	while(*str){
		if(!isdigit(*str)){
			return 1; 
		}
		str++; 
	}
	return 0; 
}
int id_unique(char* id){
	FILE *f; 
	char current_id[LENGTH]; 
	
	f = fopen("users.txt", "r"); 
	if(f == NULL){
		printf("problem with the file.\n"); 
		exit(1); 
	}else{
		while(fscanf(f, "%*s %*s %s %*d %*s %*s %*s %*s", current_id) == 1){
			if(strcmp(current_id, id) == 0){
				fclose(f); 
				return 0; 
			}
		}
		fclose(f); 
	}
	return 1; 
}

void display_filtered_users(){
	int sex_input; 
	int role_input; 
	char role [LENGTH]; 
	FILE *f;
	user u_; 
	user *u; 
	u = &u_;  
	int users_found = 0; 
	do{
		printf("filter by sex: 1 for male, 0 for female \n"); 
		scanf("%d", &sex_input);
		while(getchar() != '\n');
	}while(sex_input != 1 && sex_input != 0); 

	do{
		printf("filter by role: 1: nurse, 2: establishment manager, 3: doctor."); 
		scanf("%d", &role_input);
		while(getchar() != '\n');  
	}while(role_input != 1 && role_input != 2 && role_input != 3); 

	switch(role_input){
		case 1: 
			strcpy(role, "Nurse"); 
			break; 
		case 2: 
			strcpy(role, "EST_Manager");
			break; 
		case 3: 
			strcpy(role, "Doctor"); 
			break;  
	}	

	f = fopen("users.txt", "a+"); 
	if(f == NULL){
		printf("problem accessing file.\n"); 
		exit(1); 
	}else{
		while(fscanf(f, "%s %s %s %d %s %s %*s %s",
					u->surname,
					u->name,
					u->cin,
					&u->sex,
					u->est,
					u->role,
					u->tel) == 7){
						if(u->sex == sex_input && strcmp(u->role, role) == 0){
							printf("surname: %s, name: %s, cin: %s, sex: %d, establishment: %s, role: %s, tel: %s\n", 
											u->surname,
											u->name,
											u->cin,
											u->sex,
											u->est,
											u->role,
											u->tel
										);
							users_found = 1; 
							 
						}
					} 
			if(users_found == 0){
				printf("no available users.\n"); 
			}
		fclose(f);
	}
	
}


void edit_user(){
	char id[LENGTH]; 
	FILE *f, *temp; 
	user u_; 
	user *u; 
	u = &u_; 
	int found = 0; 
	
	printf("what user to edit.\n"); 
	scanf("%s", id);
	while(getchar() != '\n'); 
	 
	f = fopen("users.txt", "a+"); 
	temp = fopen("temp.txt", "a+"); 

	if(f == NULL || temp == NULL){
		printf("problem accessing files.\n"); 
		exit(1); 
	}else{
		while(fscanf(f, "%s %s %s %d %s %s %s %s", 
			u->surname, 
			u->name, 
			u->cin, 
			&u->sex,
			u->est,
			u->role,
			u->password,
			u->tel		
		) == 8){
			if(strcmp(u->cin, id) == 0){
				found = 1; 
				u = get_user_input(u); 
				fprintf(temp, "%s %s %s %d %s %s %s %s\n",
					u->surname,
					u->name,
					u->cin,
					u->sex,
					u->est,
					u->role,
					u->password,
					u->tel

				);
			}else{
				fprintf(temp, "%s %s %s %d %s %s %s %s\n",
										u->surname,
										u->name,
										u->cin,
										u->sex,
										u->est,
										u->role,
										u->password,
										u->tel
					
									);
										
			}
		}

		fclose(f); 
		fclose(temp); 

		remove("users.txt"); 
		rename("temp.txt", "users.txt"); 

		if(found) {
		   printf("User with ID %s edited successfully.\n", id);
		 } else {
		   printf("No user found with ID %s.\n", id);
		 }
	}
	
}



void delete_user() {
    char id[LENGTH];
    FILE *f, *temp;
    user u_;
    user *u = &u_;
    int found = 0;

    printf("Enter the ID of the user to delete: ");
    scanf("%s", id);
    while (getchar() != '\n');

    f = fopen("users.txt", "r");
    temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) {
        printf("Problem accessing files.\n");
        exit(1);
    } else {
        while (fscanf(f, "%s %s %s %d %s %s %s %s",
                      u->surname,
                      u->name,
                      u->cin,
                      &u->sex,
                      u->est,
                      u->role,
                      u->password,
                      u->tel) == 8) {
            if (strcmp(u->cin, id) == 0) {
                found = 1;
            } else {
                fprintf(temp, "%s %s %s %d %s %s %s %s\n",
                        u->surname,
                        u->name,
                        u->cin,
                        u->sex,
                        u->est,
                        u->role,
                        u->password,
                        u->tel);
            }
        }

        fclose(f);
        fclose(temp);

        remove("users.txt");
        rename("temp.txt", "users.txt");

        if (found) {
            printf("User with ID %s deleted successfully.\n", id);
        } else {
            printf("No user found with ID %s.\n", id);
        }
    }
}


void show_stats(){
	user u_;
	    user *u = &u_;
	    int total_users = 0;
	    int male_count = 0;
	    int female_count = 0;
	
	    FILE *f;
	    f = fopen("users.txt", "a+");
	    if (f == NULL) {
	        printf("Problem accessing file.\n");
	        exit(1);
	    } else {
	        while (fscanf(f, "%s %s %s %d %s %s %s %s",
	                      u->surname,
	                      u->name,
	                      u->cin,
	                      &u->sex,
	                      u->est,
	                      u->role,
	                      u->password,
	                      u->tel) == 8) {
	            total_users++;
	
	            // Count male and female users
	            if (u->sex == 1) {
	                male_count++;
	            } else {
	                female_count++;
	            }
	        }
	
	        fclose(f);
	
	        // Calculate percentages
	        float male_percentage = (float)male_count / total_users * 100;
	        float female_percentage = (float)female_count / total_users * 100;
	
	        printf("Statistics:\n");
	        printf("Total Users: %d\n", total_users);
	        printf("Male Users: %.2f%%\n", male_percentage);
	        printf("Female Users: %.2f%%\n", female_percentage);
	    }
	}
	
	
