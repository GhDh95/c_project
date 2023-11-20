#ifndef FUNCTIONS_ETS_H_INCLUDED
#define FUNCTIONS_ETS_H_INCLUDED
#include "functions_user.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <gtk/gtk.h>


#define LENGTH_ETS 50


// etablissement struct
typedef struct
{
	char id[LENGTH_ETS];
	char name[LENGTH_ETS];
	char region[LENGTH_ETS];
	char address[LENGTH_ETS];
	int from_hour;
	int to_hour;
	int capacity;
	char contact[LENGTH_ETS];
	int type;	
} etablissement;

enum 
{
	ID_ETS,
	NAME_ETS,
	REGION_ETS,
	ADDRESS_ETS,
	HOUR_ETS,
	CAPACITY_ETS,
	CONTACT_ETS,
	TYPE_ETS,
	COLUMNS_ETS
};

enum
{
	DATE_HEURE_ACTIVITY,
	TYPE_ACTIVITY,
	COLUMNS_ACTIVITY
};

//get time and date
void get_timeDate (char timeDate[LENGTH_ETS]);

//type to string
void type_toString (int type, char result[LENGTH_ETS]);

// generate and set a unique id for ets and then check in ets_file to make sure it's unique.
etablissement generate_id_ets (etablissement ets);

// add ets to ets_file and return task status 
void add_ets (etablissement ets, char *task_status);

// lookup ets in ets_file by id and return task status
void lookup_ets_by_id (char id[LENGTH_ETS], etablissement *ets, char *task_status);

// edit ets_data in ets_file by id and return task status 
void edit_ets (etablissement ets, char *task_status);

// delete ets from ets_file by id and return task status 
void delete_ets (const char *path, char id[LENGTH_ETS], char *task_status);

// add region to region_file if it doesn't exist and return task_status
void add_region (char region[LENGTH_ETS], char *task_status);

//delete region from regions_file if it does exist and return task_status
void delete_region (char region[LENGTH_ETS], char *task_status);

//sort ets by region 
void filter_ets_by_region (const char *path, char region[LENGTH_ETS], char *task_status);

//filter ets by capacity_min
void filter_ets_by_capacity(const char *path, int capacity_min, char *task_status);

//filter ets by name 
void filter_ets_by_name(const char *path, char name[LENGTH_ETS], char *task_status);

//ascending sort ets by capacity
void sort_ets_by_capacity_asc (const char *path, char *task_status);

//descending sort ets by capacity
void sort_ets_by_capacity_desc (const char *path, char *task_status);

//checks if cin exists in user_data
int check_cin_user (char cin[LENGTH], char* task_status);

//returns information of adminUser
user get_userInfo (char cin[LENGTH]);

//get difficulty of password
int get_password_difficulty (char password[LENGTH]);

//adds activity
void add_activity(char cin[LENGTH], char activity[LENGTH_ETS]);

//returns index of region in the combobox
int region_toInt(char region[LENGTH_ETS]);

// returns index of ets 
int ets_toInt (char id[LENGTH_ETS]);

//fill combobox with ets
void fill_etsComboBox (GtkComboBox *comboBox);

//checks if entry has whitespace
int has_whiteSpace(char entry[LENGTH_ETS]);

//populate ets_data in tree_view
void display_ets (GtkWidget *list, const char *path, int *nbr);

//clear tree view
void clear_treeView (GtkWidget *list);

//display user_activity in tree_view
void display_user_activity (GtkWidget *list, char cin[LENGTH], char type[LENGTH_ETS]);

//retrieves the last DATE of mdp_modification by cin 
void get_last_reset_password (char cin[LENGTH], char last_reset[LENGTH_ETS]);

//replace whitespaces with underscore
void whitespace_to_underscore (char *string);

//replace underscore with whitespace
void underscore_to_whitespace (char *string);

//checks if string is all digits
int is_all_digit (char *string);

//checks if string is all alphabetical letters
int is_all_alpha (char *string);

//checks if string is all alpha or numeric
int is_all_alnum (char *string);

//checks if string has 2 adjacent whitespaces
int has_double_whitespace (char *string);
 
#endif // FUNCTIONS_ETS_H_INCLUDED

