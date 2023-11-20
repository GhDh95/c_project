#include "functions_ets.h"
#include "functions_user.h"

const char *ets_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/ets_data.txt";
const char *ets_by_name_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/intermediate/ets_by_name.txt";
const char *ets_by_capacity_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/intermediate/ets_by_capacity.txt";
const char *ets_by_region_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/intermediate/ets_by_region.txt";

const char *region_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/region_data.txt";
const char *activity_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/activity_data.txt";

extern const char *user_path;


// get time and date
void get_timeDate (char timeDate[LENGTH_ETS])
{
	time_t t;
	struct tm *time_info;
	time(&t);
	time_info = localtime(&t);
	strftime(timeDate, 50, "%Y-%m-%d-%H-%M-%S", time_info);	
}

//type to string
void type_toString(int type, char result[LENGTH_ETS])
{
	sprintf(result, "%d", type);
}

// generate and set // generate and set a unique id for ets and then check in ets_file to make sure it's unique.
etablissement generate_id_ets(etablissement ets)
{
	// set id to current_time
	char timeDate[LENGTH_ETS];
	get_timeDate(timeDate);
	strcpy (ets.id, timeDate);

	// id gets an additional 4 digits random number until id unique in ets_file
	int found = 0;
	char id[LENGTH_ETS];
	srand(time(NULL));
	int randomNumber;
	char randomStr[10];
	FILE *f;
	f = fopen(ets_path,"r");
	if(f != NULL)
	{
		do 
		{
			randomNumber = rand() % 9000 + 1000;
			sprintf(randomStr, "%d", randomNumber);
			strcat(ets.id, randomStr);	
			while(fscanf(f,"%s %*s %*s %*s %*d %*d %*d %*s %*s\n", id) != EOF && found == 0)
				if(strcmp(ets.id, id) == 0)
					found = 1;
			rewind(f);
		}
		while(found == 1);	
		fclose(f);
	}
	else
	{
		randomNumber = rand() % 9000 + 1000;
		sprintf(randomStr, "%d", randomNumber);
		strcat(ets.id, randomStr);	
	}
	
	return ets;
}

// add ets to ets_file and return task status 
void add_ets(etablissement ets, char *task_status)
{
	
		FILE *f;
		f = fopen(ets_path,"a");
		if(f != NULL)	
		{
			fprintf(f,"%s %s %s %s %d %d %d %s %d\n", ets.id, ets.name, ets.region, ets.address, ets.from_hour, ets.to_hour, ets.capacity, ets.contact, ets.type);
			strcpy(task_status, "ets successfully added");
			fclose(f);
		}
		else 
			strcpy(task_status, "couldn't open ets_file");
		
}

// lookup ets// lookup ets in ets_file by id and return task status
void lookup_ets_by_id(char id[LENGTH_ETS], etablissement *ets, char *task_status)
{

	int found = 0;
	etablissement file;
	FILE *f;
	f = fopen(ets_path, "r");
	if(f != NULL)
	{
		while(fscanf(f, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF && found == 0)
		{
			if(strcmp(file.id, id) == 0)
			{
				strcpy(task_status, "ets successfully found");
				found = 1;
				*ets = file;
				underscore_to_whitespace (ets->name);
				underscore_to_whitespace (ets->region);
				underscore_to_whitespace (ets->address);
			}
		}
		if(found == 0)
			strcpy(task_status, "ets not found");
		fclose(f);
	}
	else
		strcpy(task_status, "couldn't open ets_file");	
}

// edit ets_data in ets_file by id and return task status 
void edit_ets(etablissement ets, char *task_status)
{
	int check = 0;
	etablissement file;
	FILE *f;
	f = fopen(ets_path, "r");
	FILE *f2;
	f2 = fopen("temporary.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF)
			if(strcmp(file.id, ets.id) == 0)
			{
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", ets.id, ets.name, ets.region, ets.address, ets.from_hour, ets.to_hour, ets.capacity, ets.contact, ets.type);
				strcpy(task_status, "ets successfully modified");
				check = 1;
			}
			else 
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
		if (check == 0)
			strcpy (task_status, "ets not found");
	}
	else
		strcpy(task_status, "couldn't open ets_file");
	fclose(f); 
	fclose(f2);
	remove(ets_path);
	rename("temporary.txt", ets_path);	
}

// delete ets from ets_file by id and return task status 
void delete_ets(const char* path, char id[LENGTH_ETS], char *task_status)
{
	int found = 0;
	etablissement file;
	FILE *f;
	f = fopen(path, "r");
	FILE *f2;
	f2 = fopen("temporary.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF)
			if(strcmp(file.id, id) != 0)
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
			else 
			{
				strcpy(task_status, "ets successfully deleted");
				found = 1;
			}
		if(found == 0)
			strcpy(task_status, "ets not found");
	}
	else
		strcpy(task_status, "couldn't open ets_file");
	fclose (f);
	fclose (f2);
	remove (path);
	rename ("temporary.txt", path);	
}

// add region to region_file if it doesn't exist already and return task_status
void add_region(char region[LENGTH_ETS], char *task_status)
{
	int found = 0;
	char file[20];
	FILE *f;
	f = fopen(region_path, "a+");
	if(f != NULL)
	{
		while(fscanf(f, "%s\n", file) != EOF && found == 0)
			if(strcmp(file, region) == 0)
			{
				found = 1;
				strcpy(task_status, "region already exists");
			}
		if(found == 0)
		{
			fprintf(f, "%s\n", region);
			strcpy(task_status, "region successfully added");
		}
	}
	else
		strcpy(task_status, "couldn't open regions_file");
	fclose(f);	
}

//delete region from regions_file if it does exist and return task_status
void delete_region(char region[LENGTH_ETS], char *task_status)
{
	int found = 0;
	char file[LENGTH_ETS];
	FILE *f;
	f = fopen(region_path, "r");
	FILE *f2;
	f2 = fopen("temporary.txt", "w");
	if(f!= NULL && f2 != NULL)
	{
		while(fscanf(f, "%s\n", file) != EOF)
			if(strcmp(file, region) == 0)
			{
				found = 1;
				strcpy(task_status, "region successfully deleted");
			}
			else
				fprintf(f2, "%s\n", file);
		if(found == 0)
			strcpy(task_status, "region not found");
	}
	else
		strcpy(task_status, "couldn't open regions_file");
	fclose(f);
	fclose(f2);
	remove(region_path);
	rename("temporary.txt", region_path);
}

//filter ets by region 
void filter_ets_by_region(const char *path, char region[LENGTH_ETS], char *task_status)
{
	etablissement file;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen(ets_by_region_path, "w");
	if(f1 != NULL && f2 != NULL)
	{
		while(fscanf(f1, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF)
			if (strlen (region) == 0)
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
			else if (strcmp (file.region, region) == 0)
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by region successful");
	}
	else
		strcpy(task_status, "couldn't open file");
}

//filter ets by capacity_min
void filter_ets_by_capacity(const char *path, int capacity_min, char *task_status)
{
	etablissement file;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen(ets_by_capacity_path, "w");
	if(f1 != NULL && f2 != NULL)
	{
		while (fscanf (f1, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF)
			if (file.capacity >= capacity_min)
				fprintf (f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by capacity successful");
	}
	else
		strcpy(task_status, "couldn't open file");
}

//filter ets by name 
void filter_ets_by_name(const char *path, char name[LENGTH_ETS], char *task_status)
{
	etablissement file;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen(ets_by_name_path, "w");
	if(f1 != NULL && f2 != NULL)
	{
		while (fscanf (f1, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF)
			if (strlen (name) == 0)
				fprintf (f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
			else if (strstr (file.name, name) != NULL)
				fprintf (f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by name successful");
	}
	else
		strcpy(task_status, "couldn't open file");
}

//sort ets by capacity
void sort_ets_by_capacity_asc(const char *path, char *task_status)
{
	etablissement ets1, ets_min;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen("ets_by_capacity_asc.txt", "w");
	if(f1 != NULL && f2 != NULL)
	{
		FILE *copie = fopen("copie_path", "w");
		if(copie != NULL)
		{
			while(fscanf(f1, "%s %s %s %s %d %d %d %s %d\n", ets1.id, ets1.name, ets1.region, ets1.address, &ets1.from_hour, &ets1.to_hour, &ets1.capacity, ets1.contact, &ets1.type) != EOF)
				fprintf(copie, "%s %s %s %s %d %d %d %s %d\n", ets1.id, ets1.name, ets1.region, ets1.address, ets1.from_hour, ets1.to_hour, ets1.capacity, ets1.contact, ets1.type);	
			fclose(copie);
			fclose(f1);
			
			int line;
			char garbage[50];
			do
			{
				copie = fopen("copie_path", "r");
				line = 0;
				if(fscanf(copie, "%s %s %s %s %d %d %d %s %d\n", ets_min.id, ets_min.name, ets_min.region, ets_min.address, &ets_min.from_hour, &ets_min.to_hour, &ets_min.capacity, ets_min.contact, &ets_min.type) != EOF)
				{
					line++;
					while(fscanf(copie, "%s %s %s %s %d %d %d %s %d\n", ets1.id, ets1.name, ets1.region, ets1.address, &ets1.from_hour, &ets1.to_hour, &ets1.capacity, ets1.contact, &ets1.type) != EOF)
					{
						line++;
						if(ets1.capacity < ets_min.capacity)
							ets_min = ets1;
					}
					fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", ets_min.id, ets_min.name, ets_min.region, ets_min.address, ets_min.from_hour, ets_min.to_hour, ets_min.capacity, ets_min.contact, ets_min.type);
					fclose(copie);
					delete_ets("copie_path", ets_min.id, garbage);
				}
				else
					fclose(copie);			
			}
			while(line > 0);
			remove("copie_path");
			fclose (f2);
			strcpy(task_status, "sorting by capacity successful");	
		}
		else
			strcpy(task_status, "couldn't open file");
	}
	else
		strcpy(task_status, "couldn't open file");
	
}

//descending sort ets by capacity
void sort_ets_by_capacity_desc(const char *path, char *task_status)
{
	etablissement ets1, ets_max;
			FILE *f1 = fopen(path, "r");
			FILE *f2 = fopen("ets_by_capacity_desc.txt", "w");
			if(f1 != NULL && f2 != NULL)
			{
				FILE *copie = fopen("copie_path", "w");
				if(copie != NULL)
				{
					while(fscanf(f1, "%s %s %s %s %d %d %d %s %d\n", ets1.id, ets1.name, ets1.region, ets1.address, &ets1.from_hour, &ets1.to_hour, &ets1.capacity, ets1.contact, &ets1.type) != EOF)
						fprintf(copie, "%s %s %s %s %d %d %d %s %d\n", ets1.id, ets1.name, ets1.region, ets1.address, ets1.from_hour, ets1.to_hour, ets1.capacity, ets1.contact, ets1.type);	
					fclose(copie);
					fclose(f1);
					
					int line;
					char garbage[LENGTH_ETS];
					do
					{
						copie = fopen("copie_path", "r");
						line = 0;
						if(fscanf(copie, "%s %s %s %s %d %d %d %s %d\n", ets_max.id, ets_max.name, ets_max.region, ets_max.address, &ets_max.from_hour, &ets_max.to_hour, &ets_max.capacity, ets_max.contact, &ets_max.type) != EOF)
						{
							line++;
							while(fscanf(copie, "%s %s %s %s %d %d %d %s %d\n", ets1.id, ets1.name, ets1.region, ets1.address, &ets1.from_hour, &ets1.to_hour, &ets1.capacity, ets1.contact, &ets1.type) != EOF)
							{
								line++;
								if(ets1.capacity > ets_max.capacity)
									ets_max = ets1;
							}
							fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", ets_max.id, ets_max.name, ets_max.region, ets_max.address, ets_max.from_hour, ets_max.to_hour, ets_max.capacity, ets_max.contact, ets_max.type);
							fclose(copie);
							delete_ets("copie_path", ets_max.id, garbage);
						}
						else
							fclose(copie);			
					}
					while(line > 0);
					remove("copie_path");
					strcpy(task_status, "sorting by capacity successful");	
				}
				else
					strcpy(task_status, "couldn't open file");
				fclose (f2);
			}
			else
				strcpy(task_status, "couldn't open file");	
}


//checks if cin exists in user_data
int check_cin_user(char cin[LENGTH], char* task_status)
{
	
	int check = 0;
	char cin_file[LENGTH];
	FILE *f = fopen(user_path, "r");
	if(f != NULL)
	{
		while(fscanf (f, "%*s %*s %s %*d %*s %*s %*s %*s %*s %*[^\n]\n", cin_file) != EOF && check == 0)
			if (strcmp (cin, cin_file) == 0)
			{
				strcpy(task_status, "cin found");
				check = 1;
			}
		if(check == 0)
			strcpy(task_status, "cin n'existe pas");
		fclose(f);
	}
	else
		strcpy(task_status, "couldn't open user file");
	return check;
}

//returns information of adminUser
user get_userInfo (char cin[LENGTH])
{
	user user;
	int check = 0;
	FILE *f = fopen(user_path, "r");
	if(f != NULL)
	{
		while(fscanf(f, "%s %s %s %d %s %s %s %s %s %[^\n]?\n", user.surname, user.name, user.cin, &user.sex, user.est, user.role, user.password, user.tel, user.answer, user.question) != EOF && check == 0)
			if(strcmp(user.cin, cin) == 0)
			{
				fclose(f);
				return user;
			}
	}
}

//get difficulty of password
int get_password_difficulty (char password[LENGTH])
{
	int result = 0;
	int upper = 0;
	int lower = 0;
	int digit = 0;
	int whitespace = 0;
	int special_char = 0;
	for (int i = 0; password[i] != '\0'; i++)
	{
		if (isupper (password[i]))
			upper = 1;
		if (islower (password[i]))
			lower = 1;
		if (isdigit (password[i]))
			digit = 1;
		if (!isdigit (password[i]) && !isalpha (password[i]))
			special_char = 1;
		if (password[i] == ' ')
			whitespace = 1;
	}
	if (upper == 1 && lower == 1)
		result++;
	if (digit == 1 && (upper == 1 || lower == 1))
		result++;
	if (special_char == 1)
		result++;
	if (whitespace == 1 || strlen (password) < 8)
		result = 0;
	return result;	
}

//adds activity
void add_activity (char cin[LENGTH], char activity[LENGTH_ETS])
{
	FILE *f = fopen (activity_path, "a");
	if (f != NULL)
	{
		char timeDate[LENGTH_ETS];
		get_timeDate(timeDate);
		fprintf (f, "%s %s %s\n", cin, timeDate, activity);
		fclose(f);
	}
}

//returns index of region in the combobox
int region_toInt (char region[LENGTH_ETS])
{
	int i = 0;
	char file[LENGTH_ETS]; 
	FILE *f = fopen (region_path, "r");
	if (f!= NULL)
	{
		while (fscanf (f, "%[^\n]\n", file) != EOF)
		{
			if (strcmp (file, region) == 0)
					return i;
			i++;
		}
	}
	return -1;
}

// returns index of ets by name 
int ets_toInt (char name[LENGTH_ETS])
{
	char file[LENGTH_ETS];
	int i = 0;
	FILE *f = fopen (ets_path, "r");
	if (f!= NULL)
	{
		while (fscanf (f, "%*s %s %*s %*s %*d %*d %*d %*s %*d\n", file) != EOF)
		{
			underscore_to_whitespace (file);
			if (strcmp (name, file) == 0)
				return i;
			i++;
		}
	}
	return -1;	
}

//fill combobox with ets.name
void fill_etsComboBox (GtkComboBox *comboBox)
{
	//clear comboBox
	GtkListStore *liste = GTK_LIST_STORE (gtk_combo_box_get_model (comboBox));
	gtk_list_store_clear(liste);

	//fill comboBox
	char name[LENGTH_ETS];
	FILE *f = fopen (ets_path, "r");
	if (f != NULL)
	{
		while (fscanf (f, "%*s %s %*s %*s %*d %*d %*d %*s %*d\n", name) != EOF)
		{
			underscore_to_whitespace (name);
			gtk_combo_box_append_text (comboBox, name);
		}
		fclose (f);
	}	
}

//checks if entry has whitespace
int has_whiteSpace(char entry[LENGTH_ETS])
{
	int i;
	for (i = 0; i < strlen (entry); i++)
		if (entry[i] == ' ')
			return 1;
	return 0;
}

//display ets_data in tree_view
void display_ets (GtkWidget *list, const char* path, int *nbr)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	store = NULL;
	etablissement ets;
	store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (list)));
	if (store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Id", renderer, "text", ID_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Nom", renderer, "text", NAME_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, NAME_ETS);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Region", renderer, "text", REGION_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, REGION_ETS);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Addresse", renderer, "text", ADDRESS_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Heures d'ouverture", renderer, "text", HOUR_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, HOUR_ETS);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Capacite", renderer, "text", CAPACITY_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, CAPACITY_ETS);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Contact", renderer, "text", CONTACT_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Type", renderer, "text", TYPE_ETS, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
	}
	store = gtk_list_store_new (COLUMNS_ETS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);
	FILE *f = fopen (path, "r");
	*nbr = 0;
	if (f == NULL)
		return;
	else
	{
		while (fscanf (f, "%s %s %s %s %d %d %d %s %d\n", ets.id, ets.name, ets.region, ets.address, &ets.from_hour, &ets.to_hour, &ets.capacity, ets.contact, &ets.type) != EOF)
		{
			(*nbr)++;
			char hours[10];
			char typeStr[10];
			if (ets.type == 0)
				strcpy (typeStr, "cnts");
			else
				strcpy (typeStr, "crts");
			sprintf (hours, "%d - %d", ets.from_hour, ets.to_hour);
			underscore_to_whitespace (ets.name);
			underscore_to_whitespace (ets.region);
			underscore_to_whitespace (ets.address);
			gtk_list_store_append (store, &iter);
			gtk_list_store_set (store, &iter, ID_ETS, ets.id, NAME_ETS, ets.name, REGION_ETS, ets.region, ADDRESS_ETS, ets.address, HOUR_ETS, hours, CAPACITY_ETS, ets.capacity, CONTACT_ETS, ets.contact, TYPE_ETS, typeStr, -1);
		}
		fclose (f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (list), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}	
}

//clear tree view
void clear_treeView (GtkWidget *list)
{
	gtk_list_store_clear (GTK_LIST_STORE (list));	
}

//display user_activity in tree_view
void display_user_activity (GtkWidget *list, char cin[LENGTH], char type[LENGTH_ETS])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	char cin_file[LENGTH];
	char type_file[LENGTH_ETS];
	char date_file[LENGTH_ETS];

	store = NULL;
	store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (list)));
	if (store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Date et Heure", renderer, "text", DATE_HEURE_ACTIVITY, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, DATE_HEURE_ACTIVITY);
		gtk_tree_view_column_set_sort_order (column, GTK_SORT_DESCENDING);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Activité", renderer, "text", TYPE_ACTIVITY, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
	}
	store = gtk_list_store_new (COLUMNS_ACTIVITY, G_TYPE_STRING, G_TYPE_STRING);

	FILE *f = fopen (activity_path, "r");
	if (f == NULL)
		return;
	else
	{
		while (fscanf (f, "%s %s %s\n", cin_file, date_file, type_file) != EOF)
			if (strlen (type) == 0 && strcmp (cin, cin_file) == 0)
			{
				gtk_list_store_append (store, &iter);
				gtk_list_store_set (store, &iter, DATE_HEURE_ACTIVITY, date_file, TYPE_ACTIVITY, type_file, -1);
			}
			else if (strcmp (type, type_file) == 0 && strcmp (cin, cin_file) == 0)
			{
				gtk_list_store_append (store, &iter);
				gtk_list_store_set (store, &iter, DATE_HEURE_ACTIVITY, date_file, TYPE_ACTIVITY, type_file, -1);	
			}
		fclose (f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (list), GTK_TREE_MODEL (store));
		g_object_unref (store);			
	}
}

//retrieves the last DATE of mdp_modification by cin 
void get_last_reset_password (char cin[LENGTH], char last_reset[LENGTH_ETS])
{
	char date_file[LENGTH_ETS];
	char cin_file[LENGTH];
	char activity[LENGTH_ETS];
	char last_date[LENGTH_ETS];
	FILE *f = fopen (activity_path, "r");

	if (f != NULL)
	{
		while (fscanf (f, "%s %s %s\n", cin_file, date_file, activity) != EOF)
			if (strcmp (cin, cin_file) == 0 && strcmp (activity, "modification_mdp") == 0)
				strcpy (last_date, date_file);
		fclose(f);
	}
	if (strlen (last_date) != 19)
	{
		strcpy (last_reset, "erreur");
		return;
	}
	strcpy (last_reset, "Dernière modification:");
	const char slash = '/';	
	for (int i = 0; i < 10; i++)
		if (i != 4 && i != 7)
			strncat (last_reset, &last_date[i], 1);
		else
			strncat (last_reset, &slash, 1);		
}

//replace whitespaces with underscore
void whitespace_to_underscore (char *string)
{
	if (string == NULL)
		return;

	while (*string)
	{
		if (*string == ' ')
			*string = '_';
		string++;
	}
}

//replace underscore with whitespace
void underscore_to_whitespace (char *string)
{
	if (string == NULL)
		return;
		
	while (*string)
	{
		if (*string == '_')
			*string = ' ';
		string++;
	}	
}

//checks if string is all digits
int is_all_digit (char *string)
{
	while (*string)
	{
		if (!isdigit (*string))
			return 0;
		string++;
	}
	return 1;	
}

//checks if string is all alphabetical letters
int is_all_alpha (char *string)
{
	while (*string)
	{
		if (!isalpha (*string) && *string != ' ')
			return 0;
		string++;
	}
	return 1;	
}

//checks if string is all alpha or numeric
int is_all_alnum (char *string)
{
	while (*string)
	{
		if (!isalnum (*string) && *string != ' ')
			return 0;
		string++;
	}
	return 1;	
}

//checks if string has 2 adjacent whitespaces
int has_double_whitespace (char *string)
{
	if (strstr (string, "  ") == NULL)
		return 0;
	else return 1;
}

