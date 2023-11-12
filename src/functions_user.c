#include "functions_user.h"

const char *user_path = "/home/arous/Desktop/studium/copie_interface/project_final/src/user_data.txt";

void add_user(user data)
{
	FILE *f = fopen (user_path, "a");
	if (f != NULL)
	{
		fprintf(f, "%s %s %s %d %s %s %s %s %s %s\n", data.surname, data.name, data.cin, data.sex, data.est, data.role, data.password, data.tel, data.answer, data.question);
	}
	fclose(f);
} 

void edit_user(user data)
{
	user file;
	FILE *f = fopen (user_path, "r");
	FILE *f2 = fopen ("temp.txt", "w");
	if (f != NULL && f2 != NULL)
	{
		while (fscanf (f, "%s %s %s %d %s %s %s %s %s %[^\n]\n", file.surname, file.name, file.cin, &file.sex, file.est, file.role, file.password, file.tel, file.answer, file.question) != EOF)
			if (strcmp (file.cin, data.cin) == 0)
				fprintf (f2, "%s %s %s %d %s %s %s %s %s %s\n", data.surname, data.name, data.cin, data.sex, data.est, data.role, data.password, data.tel, data.answer, data.question);
			else
				fprintf (f2, "%s %s %s %d %s %s %s %s %s %s\n", file.surname, file.name, file.cin, file.sex, file.est, file.role, file.password, file.tel, file.answer, file.question);		
	}
	fclose(f);
	fclose(f2);
	remove(user_path);
	rename("temp.txt", user_path);
}

user * get_user_input(user *u); 
int field_empty(char *str); 
int is_str_numeric(char *str);
int id_unique(char* id); 
void display_all_users();  
void display_filtered_users(); 
void delete_user(); 
void show_stats(); 


//check authentification credentials 
int authenticate(char cin[LENGTH], char password[LENGTH], char role[LENGTH], char task_status[100])
{
	int check = 0;
	char cin_file[LENGTH];
	char password_file[LENGTH];
	FILE *f = fopen(user_path, "r");
	if(f != NULL)
	{
		while(fscanf(f, "%*s %*s %s %*d %s %*s %s %*s %*S %*[^\n]\n", cin_file, role, password_file) != EOF && check == 0)
			if(strcmp(cin, cin_file) == 0 && strcmp(password, password_file) == 0)
			{
				strcpy(task_status, "authentification successful.");
				check = 1;
			}
		if(check == 0)
			strcpy(task_status, "identification invalide.");
		fclose(f);
	}
	else
		strcpy(task_status, "couldn't open user file.");
	return check;
}
