#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "functions_user.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// etablissement struct
typedef struct
{
	char id[50];
	char name[20];
	char region[20];
	char address[50];
	int from_hour;
	int to_hour;
	int capacity;
	char contact[20];
	int type;	//int
} etablissement;

//type to string
char* type_toString(int type);

// generate and set a unique id for ets and then check in ets_file to make sure it's unique.
etablissement generate_id(etablissement ets);

// add ets to ets_file and return task status 
void add_ets(etablissement ets, char *task_status);

// lookup ets in ets_file by id and return task status
void lookup_ets_by_id(char id[50], etablissement *ets, char *task_status);

// edit ets_data in ets_file by id and return task status 
void edit_ets(etablissement ets, char *task_status);

// delete ets from ets_file by id and return task status 
void delete_ets(const char *path, char id[50], char *task_status);

// add region to region_file if it doesn't exist and return task_status
void add_region(char region[20], char *task_status);

//delete region from regions_file if it does exist and return task_status
void delete_region(char region[20], char *task_status);

//sort ets_by_region , and if equal, sort by capacity
void filter_by_region(const char *path, char region[20], char *task_status);

//ascending sort ets by capacity
void sort_by_capacity_asc(const char *path, char *task_status);

//descending sort ets by capacity
void sort_by_capacity_desc(const char *path, char *task_status);

//checks if cin exists in user_data
int check_cin_user(char *cin, char* task_status);

//returns information of adminUser
user get_userInfo(char cin[LENGTH]);

//get difficulty of password
int get_password_difficulty (char password[LENGTH]);
 
#endif // FUNCTIONS_H_INCLUDED

