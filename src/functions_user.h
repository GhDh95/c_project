#ifndef FUNCTIONS_USERS_H
#define FUNCTIONS_USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 40


typedef struct User{
	char surname [LENGTH]; 
	char name [LENGTH]; 
	char cin[LENGTH]; 
	int sex; 
	char est[LENGTH]; 
	char role[LENGTH]; 
	char password [LENGTH]; 
	char tel[LENGTH]; 		
	char answer[LENGTH];
	char question[LENGTH];
}user; 

void add_user(user data);
void edit_user(user data); 
user * get_user_input(user *u); 
int field_empty(char *str); 
int is_str_numeric(char *str);
int id_unique(char* id); 
void display_all_users();  
void display_filtered_users();
void delete_user(); 
void show_stats(); 

//check authentification credentials 
int authenticate(char *cin_entry, char *password_entry, char *role, char* task_status);





#endif 
