#include "functions_request.h"

const char *req_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/request_data.txt";
const char *req_by_ets_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/intermediate/request_by_ets.txt";
const char *req_by_blood_type_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/intermediate/request_by_blood_type.txt";
const char *req_by_date_max_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/intermediate/request_by_date_max.txt";

//blood_type to string
void blood_type_to_string (char string[5], blood_type bloodType)
{
	const char plus = '+';
	const char minus = '-';
	strcpy (string, bloodType.bloodGroup);
	if (bloodType.rhesus == 1)
		strncat (string, &plus, 1);
	else if (bloodType.rhesus == 0)
		strncat (string, &minus, 1);	
}


//date to string
void date_to_string (char string[15], date date)
{
	sprintf (string, "%d / %d / %d", date.y, date.m, date.d);		
}


// generate and set a unique id for request and then check in request_file to make sure it's unique.
request generate_id_req (request req)
{
	char id[LENGTH_REQ];
	int check;
	uint32_t randomNumber;
	uint32_t result;  
	FILE *f = fopen (req_path, "r");
	if (f != NULL)
	{
		do
		{
			check = 0;
			randomNumber = rand();
			result = 10000000 + randomNumber % 90000000;
			sprintf(req.id, "%u", result);
			while (fscanf (f, "%s %*s %*s %*d %*f %*d %*d %*d\n", id) != EOF)
				if (strcmp (req.id, id) == 0)
					check = 1;
			rewind (f);	
		}
		while (check == 1);
		fclose (f);
	}
	else
	{
		randomNumber = rand();
		result = 10000000 + randomNumber % 90000000;
		sprintf(req.id, "%u", result);		
	}
	return req;	
}


// add request to request_file and return task status 
void add_req (request req, char *task_status)
{
	FILE *f = fopen (req_path, "a");
	if (f != NULL)
	{
		fprintf (f, "%s %s %s %d %.2f %d %d %d\n", req.id, req.ets, req.bloodType.bloodGroup, req.bloodType.rhesus, req.quantity, req.date.y, req.date.m, req.date.d);
		strcpy (task_status, "request successfully added");
		fclose (f);
	}
	else
		strcpy (task_status, "couldn't open request_file");	
}


// lookup request in request_file by id and return task status
void lookup_req_by_id (char id[LENGTH_REQ], request *req, char *task_status)
{
	int found = 0;
	request file;
	FILE *f;
	f = fopen(req_path, "r");
	if(f != NULL)
	{
		while(fscanf(f, "%s %s %s %d %f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, &file.bloodType.rhesus, &file.quantity, &file.date.y, &file.date.m, &file.date.d) != EOF)
		{
			if(strcmp(file.id, id) == 0)
			{
				strcpy(task_status, "request successfully found");
				found = 1;
				*req = file;
			}
		}
		if(found == 0)
			strcpy(task_status, "request not found");
		fclose(f);
	}
	else
		strcpy(task_status, "couldn't open request_file");	
}


// edit request_data in request_file by id and return task status 
void edit_req (request req, char *task_status)
{
	int check = 0;
	request file;
	FILE *f;
	f = fopen(req_path, "r");
	FILE *f2;
	f2 = fopen("temporary.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%s %s %s %d %f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, &file.bloodType.rhesus, &file.quantity, &file.date.y, &file.date.m, &file.date.d) != EOF)
			if(strcmp(file.id, req.id) == 0)
			{
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", req.id, req.ets, req.bloodType.bloodGroup, req.bloodType.rhesus, req.quantity, req.date.y, req.date.m, req.date.d);
				strcpy(task_status, "request successfully modified");
				check = 1;
			}
			else 
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
		if (check == 0)
			strcpy (task_status, "request not found");
	}
	else
		strcpy(task_status, "couldn't open request_file");
	fclose(f); 
	fclose(f2);
	remove(req_path);
	rename("temporary.txt", req_path);		
}


// delete request from request_file by id and return task status 
void delete_req (const char *path, char id[LENGTH_REQ], char *task_status)
{
	int found = 0;
	request file;
	FILE *f;
	f = fopen(path, "r");
	FILE *f2;
	f2 = fopen("temporary.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%s %s %s %d %f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, &file.bloodType.rhesus, &file.quantity, &file.date.y, &file.date.m, &file.date.d) != EOF)
			if(strcmp(file.id, id) != 0)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
			else 
			{
				strcpy(task_status, "request successfully deleted");
				found = 1;
			}
		if(found == 0)
			strcpy(task_status, "request not found");
	}
	else
		strcpy(task_status, "couldn't open request_file");
	fclose (f);
	fclose (f2);
	remove (path);
	rename ("temporary.txt", path);		
}


//filter request by ets_name 
void filter_req_by_ets(const char *path, char ets[LENGTH_REQ], char *task_status)
{
	request file;
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen(req_by_ets_path, "w");
	if(f1 != NULL && f2 != NULL)
	{
		while (fscanf (f1, "%s %s %s %d %f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, &file.bloodType.rhesus, &file.quantity, &file.date.y, &file.date.m, &file.date.d) != EOF)
			if (strlen (ets) == 0)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
			else if (strstr (file.ets, ets) != NULL)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by ets successful");
	}
	else
		strcpy(task_status, "couldn't open file");
}


//filter request by blood_type 
void filter_req_by_blood_type (const char *path, char bloodType[5], char *task_status)
{
	request file;
	char bloodType_file_str[5];
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen(req_by_blood_type_path, "w");
	if(f1 != NULL && f2 != NULL)
	{
		while (fscanf (f1, "%s %s %s %d %f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, &file.bloodType.rhesus, &file.quantity, &file.date.y, &file.date.m, &file.date.d) != EOF)
			if (strlen (bloodType) == 0)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
			else
			{
				blood_type_to_string (bloodType_file_str, file.bloodType);
				if (strcmp (bloodType_file_str, bloodType) == 0)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
			}
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by blood_type successful");
	}
	else
		strcpy(task_status, "couldn't open file");	
}


//filter request by date_max 
void filter_req_by_date_max(const char *path, char date[15], char *task_status)
{
	request file;
	char date_file_str[15];
	FILE *f1 = fopen(path, "r");
	FILE *f2 = fopen(req_by_date_max_path, "w");
	if(f1 != NULL && f2 != NULL)
	{
		while (fscanf (f1, "%s %s %s %d %f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, &file.bloodType.rhesus, &file.quantity, &file.date.y, &file.date.m, &file.date.d) != EOF)
		{
			date_to_string (date_file_str, file.date);
			if (strlen (date) == 0)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);				
			else if (strcmp (date_file_str, date) <= 0)
				fprintf (f2, "%s %s %s %d %.2f %d %d %d\n", file.id, file.ets, file.bloodType.bloodGroup, file.bloodType.rhesus, file.quantity, file.date.y, file.date.m, file.date.d);
		}
		fclose(f1);
		fclose(f2);
		strcpy(task_status, "filtering by name successful");
	}
	else
		strcpy(task_status, "couldn't open file");
}


//display request_data in tree_view
void display_req (GtkWidget *list, const char* path, float *quantity, int *nbr)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	store = NULL;
	request req;
	store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (list)));
	if (store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Id", renderer, "text", ID_REQ, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("ETS demandeur", renderer, "text", ETS_REQ, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, ETS_REQ);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Type Sang", renderer, "text", BLOODTYPE_REQ, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, BLOODTYPE_REQ);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Quantité", renderer, "text", QUANTITY_REQ, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, QUANTITY_REQ);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes ("Date", renderer, "text", DATE_REQ, NULL);
		gtk_tree_view_column_set_sizing (column, GTK_TREE_VIEW_COLUMN_AUTOSIZE);
		gtk_tree_view_column_set_sort_column_id (column, DATE_REQ);
		gtk_tree_view_append_column (GTK_TREE_VIEW (list), column);
	}
	store = gtk_list_store_new (COLUMNS_REQ, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	FILE *f = fopen (path, "r");
	*quantity = 0;
	*nbr = 0;
	if (f == NULL)
		return;
	else
	{
		char bloodType[5];
		char date[15];
		gchar formatted_quantity[20];
		while (fscanf (f, "%s %s %s %d %f %d %d %d\n", req.id, req.ets, req.bloodType.bloodGroup, &req.bloodType.rhesus, &req.quantity, &req.date.y, &req.date.m, &req.date.d) != EOF)
		{
			(*quantity) += req.quantity;
			(*nbr)++;
			blood_type_to_string (bloodType, req.bloodType);
			req.date.m++;
			date_to_string (date, req.date);
			g_snprintf (formatted_quantity, sizeof (formatted_quantity), "%.2f", req.quantity);
			gtk_list_store_append (store, &iter);
			gtk_list_store_set (store, &iter, ID_REQ, req.id, ETS_REQ, req.ets, BLOODTYPE_REQ, bloodType, QUANTITY_REQ, formatted_quantity, DATE_REQ, date, -1);
		}
		fclose (f);
		gtk_tree_view_set_model (GTK_TREE_VIEW (list), GTK_TREE_MODEL (store));
		g_object_unref (store);
	}	
}


//bloodGroup to int ( O - A - b - AB)
int blood_group_to_int (char bloodGroup[5])
{
	if (strcmp (bloodGroup, "O") == 0)
		return 0;
	else if (strcmp (bloodGroup, "A") == 0)
		return 1;
	else if (strcmp (bloodGroup, "B") == 0)
		return 2;
	else if (strcmp (bloodGroup, "AB") == 0)
		return 3;
}



