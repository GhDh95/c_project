#include "functions_don.h"

const char* don_path = "/home/arous/Desktop/studium/copie_interface/project_final/data/don_data.txt";

char* groupeSanguin_toString(char groupe_sanguin[5]) {
    return groupe_sanguin;
}

char* typesDon_toString(char types_don[3]) {
    return types_don;
}

don generate_id_don(don d) {
    char timeStr[50];
    time_t t;
    struct tm *time_info;
    time(&t);
    time_info = localtime(&t);
    strftime(timeStr, 50, "%H%M%S%Y%m%d", time_info);
    strcat(d.id, timeStr);

    int found = 0;
    char id[50];
    srand(time(NULL));
    int randomNumber;
    char randomStr[20];
    FILE *f;
    f = fopen(don_path, "r");
    if (f != NULL) {
        do {
            randomNumber = rand() % 9000 + 1000;
            sprintf(randomStr, "%d", randomNumber);
            strcat(d.id, randomStr);
            while (fscanf(f, "%s %*s %*d %*d %*d %*s %*d %*f %*s %*d %*d %*d\n", id) != EOF && found == 0)
                if (strcmp(d.id, id) == 0)
                    found = 1;
            rewind(f);
        } while (found == 1);
        fclose(f);
    } else {
        randomNumber = rand() % 9000 + 1000;
        sprintf(randomStr, "%d", randomNumber);
        strcat(d.id, randomStr);
    }

    return d;
}

void add_don(don d, char *task_status) {
    FILE *f;
    f = fopen(don_path, "a");

    if (f != NULL) {
        fprintf(f, "%s %s %d %d %d %s %d %f %s %d %d %d\n", d.id, d.cin, d.types_don[0], d.types_don[1], d.types_don[2], d.groupe_sanguin, d.rhesus, d.quantite, d.ets, d.jour, d.mois, d.an);
        strcpy(task_status, "don successfully added\n");
        fclose(f);
    } else {
        strcpy(task_status, "couldn't open don_file\n");
    }
}

void lookup_don_by_id(char id[50], don *d, char *task_status) {
    int found = 0;
    don file;
    FILE *f;
    f = fopen(don_path, "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d\n", file.id, file.cin, &file.types_don[0],  &file.types_don[1], &file.types_don[2], file.groupe_sanguin, &file.rhesus, &file.quantite, file.ets, &file.jour, &file.mois, &file.an) != EOF) {
            if (strcmp(file.id, id) == 0) {
                strcpy(task_status, "don successfully found");
                found = 1;
                *d = file;
            }
        }
        if (found == 0)
            strcpy(task_status, "don not found");
        fclose(f);
    } else
        strcpy(task_status, "couldn't open dons_file");
}

void edit_don(don d, char *task_status) {
    don file;
    FILE *f;
    f = fopen(don_path, "r");
    FILE *f2;
    f2 = fopen("temporary.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d\n", file.id, file.cin, &file.types_don[0],  &file.types_don[1], &file.types_don[2], file.groupe_sanguin, &file.rhesus, &file.quantite, file.ets, &file.jour, &file.mois, &file.an) != EOF) {
            if (strcmp(file.id, d.id) == 0) {
        		fprintf(f2, "%s %s %d %d %d %s %d %f %s %d %d %d\n", d.id, d.cin, d.types_don[0], d.types_don[1], d.types_don[2], d.groupe_sanguin, d.rhesus, d.quantite, d.ets, d.jour, d.mois, d.an);
                strcpy(task_status, "don successfully modified\n");
            } else
				fprintf (f2, "%s %s %d %d %d %s %d %f %s %d %d %d\n", file.id, file.cin, file.types_don[0],  file.types_don[1], file.types_don[2], file.groupe_sanguin, file.rhesus, file.quantite, file.ets, file.jour, file.mois, file.an);
		}
	}
	else
        strcpy(task_status, "couldn't open don_file\n");
    fclose(f);
    fclose(f2);
    remove(don_path);
    rename("temporary.txt", don_path);
}

void delete_don(char id[50], char *task_status) {
    int found = 0;
    don file;
    FILE *f;
    f = fopen(don_path, "r");
    FILE *f2;
    f2 = fopen("temporary.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d\n", file.id, file.cin, &file.types_don[0],  &file.types_don[1], &file.types_don[2], file.groupe_sanguin, &file.rhesus, &file.quantite, file.ets, &file.jour, &file.mois, &file.an) != EOF) 
            if (strcmp(file.id, id) != 0)
				fprintf (f2, "%s %s %d %d %d %s %d %f %s %d %d %d\n", file.id, file.cin, file.types_don[0],  file.types_don[1], file.types_don[2], file.groupe_sanguin, file.rhesus, file.quantite, file.ets, file.jour, file.mois, file.an);
            else {
                strcpy(task_status, "don successfully deleted\n");
                found = 1;
            }
        if (found == 0)
            strcpy(task_status, "don not found");
    } else
        strcpy(task_status, "couldn't open don_file\n");
    fclose(f);
    fclose(f2);
    remove(don_path);
    rename("temporary.txt", don_path);
}

int quantite_groupe_sanguin(char groupe_sanguin[]) {
    FILE *f;
    int quantite = 0;

    f = fopen(don_path, "r");
    if (f != NULL) {
        don file;
        while (fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d\n", file.id, file.cin, &file.types_don[0],  &file.types_don[1], &file.types_don[2], file.groupe_sanguin, &file.rhesus, &file.quantite, file.ets, &file.jour, &file.mois, &file.an) != EOF) 
		{
            if (strcmp(file.groupe_sanguin, groupe_sanguin) == 0) {
                quantite++;
            }
        }
        fclose(f);
    }

    return quantite;
}

void sang_rare(char sangRare[]) {
    char typesSang[][5] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    int minQuantite = -1;
    char sangMinQuantite[3] = "";

    for (int i = 0; i < 8; ++i) {
        int quantite = quantite_groupe_sanguin(typesSang[i]);
        if (minQuantite == -1 || quantite < minQuantite) {
            minQuantite = quantite;
            strcpy(sangMinQuantite, typesSang[i]);
        }
    }

    strcpy(sangRare, sangMinQuantite);
}


