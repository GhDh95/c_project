#include "functions_ets.h"
#include "functions_user.h"

const char *ets_path = "/home/arous/Desktop/studium/copie_interface/project_final/src/ets_data.txt";
const char *region_path = "/home/arous/Desktop/studium/copie_interface/project_final/src/region_data.txt";
extern const char *user_path;

//type to string
char* type_toString(int type)
{
	char *result = malloc(50 * sizeof(char));
	sprintf(result, "%d", type);
	return result;
}

// generate and set // generate and set a unique id for ets and then check in ets_file to make sure it's unique.
etablissement generate_id(etablissement ets)
{
	// set id to type + current_time
	char timeStr[50];
	time_t t;
	struct tm *time_info;
	time(&t);
	time_info = localtime(&t);
	strftime(timeStr, 50, "%H-%M-%S-%Y-%m-%d", time_info);
	strcat(ets.id, timeStr);

	// id gets an additional 4 digits random number until id unique in ets_file
	int found = 0;
	char id[50];
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
			strcpy(task_status, "ets successfully added\n");
			fclose(f);
		}
		else 
			strcpy(task_status, "couldn't open ets_file\n");
		
}

// lookup ets// lookup ets in ets_file by id and return task status
void lookup_ets_by_id(char id[50], etablissement *ets, char *task_status)
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
				strcpy(task_status, "ets successfully modified\n");
			}
			else 
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
	}
	else
		strcpy(task_status, "couldn't open ets_file\n");
	fclose(f); 
	fclose(f2);
	remove(ets_path);
	rename("temporary.txt", ets_path);	
}

// delete ets from ets_file by id and return task status 
void delete_ets(const char *path, char id[50], char *task_status)
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
				strcpy(task_status, "ets successfully deleted\n");
				found = 1;
			}
		if(found == 0)
			strcpy(task_status, "ets not found");
	}
	else
		strcpy(task_status, "couldn't open ets_file\n");
	fclose(f);
	fclose(f2);
	remove(ets_path);
	rename("temporary.txt", ets_path);	
}

// add region to region_file if it doesn't exist already and return task_status
void add_region(char region[20], char *task_status)
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
void delete_region(char region[20], char *task_status)
{
	int found = 0;
	char file[20];
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

//sort ets_by_region , and if equal, sort by capacity
void filter_by_region(const char *path, char region[20], char *task_status)
{
	etablissement file;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen("ets_per_region.txt", "w");
	if(f1 != NULL && f2 != NULL)
	{
		while(fscanf(f1, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, &file.from_hour, &file.to_hour, &file.capacity, file.contact, &file.type) != EOF)
			if(strcmp(file.region, region) == 0)
				fprintf(f2, "%s %s %s %s %d %d %d %s %d\n", file.id, file.name, file.region, file.address, file.from_hour, file.to_hour, file.capacity, file.contact, file.type);
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by region successful");
	}
	else
		strcpy(task_status, "couldn't open ets_file");
}

//sort ets by capacity
void sort_by_capacity_asc(const char *path, char *task_status)
{
	etablissement ets1, ets_min;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen("ets_by_capacity_asc.txt", "w");
	if(f1 != NULL && f2 != NULL)
	{
		FILE *copie = fopen("copie_ets.txt", "w");
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
				copie = fopen("copie_ets.txt", "r");
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
					delete_ets("copie_ets.txt",ets_min.id, garbage);
				}
				else
					fclose(copie);			
			}
			while(line > 0);
			remove("copie_ets.txt");
			strcpy(task_status, "sorting by capacity successful");	
		}
		else
			strcpy(task_status, "couldn't open file");
	}
	else
		strcpy(task_status, "couldn't open file");
	
}

//descending sort ets by capacity
void sort_by_capacity_desc(const char *path, char *task_status)
{
	etablissement ets1, ets_max;
			FILE *f1 = fopen(path, "r");
			FILE *f2 = fopen("ets_by_capacity_desc.txt", "w");
			if(f1 != NULL && f2 != NULL)
			{
				FILE *copie = fopen("copie_ets.txt", "w");
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
						copie = fopen("copie_ets.txt", "r");
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
							delete_ets("copie_ets.txt", ets_max.id, garbage);
						}
						else
							fclose(copie);			
					}
					while(line > 0);
					remove("copie_ets.txt");
					strcpy(task_status, "sorting by capacity successful");	
				}
				else
					strcpy(task_status, "couldn't open file");
			}
			else
				strcpy(task_status, "couldn't open file");	
}


//checks if cin exists in user_data
int check_cin_user(char *cin, char* task_status)
{
	int check = 0;
	char cin_file[LENGTH];
	FILE *f = fopen(user_path, "r");
	if(f != NULL)
	{
		while(fscanf(f, "%*s %*s %s %*d %*s %*s %*s %*s /%*S/ %*S\n", cin_file) != EOF && check == 0)
			if(cin == cin_file)
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
		while(fscanf(f, "%s %s %s %d %s %s %s %s %s %[^\n]\n", user.surname, user.name, user.cin, &user.sex, user.est, user.role, user.password, user.tel, user.answer, user.question) != EOF && check == 0)
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
