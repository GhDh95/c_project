
// fonctions.h
#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

extern const char* dons_path;

typedef struct {
    char id[50];
    char cin[50];
    int types_don[3];
    char groupe_sanguin[5];
    int rhesus;
    float quantite;
    char ets[50];
    int jour;
    int mois;
    int an;
} don;

char* groupeSanguin_toString(char groupe_sanguin[5]);
char* typesDon_toString(char types_don[3]);
don generate_id_don(don d);
void add_don(don d, char *task_status);
void lookup_don_by_id(char id[50], don *d, char *task_status);
void edit_don(don d, char *task_status);
void delete_don(char id[50], char *task_status);
int quantite_groupe_sanguin(char groupe_sanguin[]);
void sang_rare(char sangRare[]);


#endif // FONCTIONS_H

