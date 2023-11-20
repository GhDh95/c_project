#ifndef FUNCTIONS_REQ_H_INCLUDED
#define FUNCTIONS_REQ_H_INCLUDED
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <gtk/gtk.h>

#define LENGTH_REQ 50

typedef struct
{
	char bloodGroup[5];
	int rhesus;
} blood_type;


typedef struct
{
	int y;
	int m;
	int d;
} date;


typedef struct
{
	char id[LENGTH_REQ];
	char ets[LENGTH_REQ];
	blood_type bloodType;
	float quantity;
	date date;
} request;


enum
{
	ID_REQ,
	ETS_REQ,
	BLOODTYPE_REQ,
	QUANTITY_REQ,
	DATE_REQ,
	COLUMNS_REQ
};


//blood_type to string
void blood_type_to_string (char string[5], blood_type bloodType);


//date to string
void date_to_string (char string[15], date date);


// generate and set a unique id for request and then check in request_file to make sure it's unique.
request generate_id_req (request req);


// add request to request_file and return task status 
void add_req (request req, char *task_status);


// lookup request in request_file by id and return task status
void lookup_req_by_id (char id[LENGTH_REQ], request *req, char *task_status);


// edit request_data in request_file by id and return task status 
void edit_req (request req, char *task_status);


// delete request from request_file by id and return task status 
void delete_req (const char *path, char id[LENGTH_REQ], char *task_status);


//filter request by ets_name 
void filter_req_by_ets(const char *path, char ets[LENGTH_REQ], char *task_status);


//filter request by blood_type 
void filter_req_by_blood_type (const char *path, char bloodType[5], char *task_status);


//filter request by date_max 
void filter_req_by_date_max(const char *path, char date[15], char *task_status);


//display request_data in tree_view
void display_req (GtkWidget *list, const char* path, float *quantity, int *nbr);


//bloodGroup to int ( O - A - b - AB)
int blood_group_to_int (char bloodGroup[5]);




#endif //FUNCTIONS_REQ_H_INCLUDED 
