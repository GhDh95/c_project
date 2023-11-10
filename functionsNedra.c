#include "functions.h"

void ajouter_don(){
	don don1; 
	don *d; 
	d = &don1; 
	FILE *f;

	d = saisir_don(d); 

	f = fopen("don.txt", "a+"); 
	if(f == NULL){
		printf("problem de fichier.\n"); 
		exit(1); 
	}else{
		fprintf(f, "%s %s %d %d %d %s %d %.2f %s %d %d %d \n", 
		d->id,
		d->cin,
		d->type_don_sang,
		d->type_don_plasma,
		d->type_don_plaquette,
		d->groupe_sanguin,
		d->rhesus,
		d->quantite,
		d->etablissement,
		d->jour,
		d->mois,
		d->annee
		); 

		fclose(f); 
	}	

	 
	
}

//afficher tout les dons
void afficher_don_tout(){
	don d_;
	don *d; 
	d = &d_;  
	
	FILE *f; 
	f = fopen("don.txt", "r"); 
	if(f == NULL){
		printf("problem avec le fichier.\n"); 
		exit(1); 
	}else{
		while(fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d",
		              d->id,
		              d->cin,
		              &d->type_don_sang,
		              &d->type_don_plasma,
		              &d->type_don_plaquette,
		              d->groupe_sanguin,
		              &d->rhesus,
		              &d->quantite,
		              d->etablissement,
		              &d->jour,
		              &d->mois,
		              &d->annee) == 12){
			 printf("%s %s %d %d %d %s %d %.2f %s %d %d %d\n",
                   d->id,
                   d->cin,
                   d->type_don_sang,
                   d->type_don_plasma,
                   d->type_don_plaquette,
                   d->groupe_sanguin,
                   d->rhesus,
                   d->quantite,
                   d->etablissement,
                   d->jour,
                   d->mois,
                   d->annee);			
		}

		fclose(f); 
	}


}

void afficher_don(){
    FILE *f;
    don d;
    char id [LENGTH]; 

	printf("donner l id.\n");
	scanf("%s", id); 
	while(getchar() != '\n'); 
	 
    f = fopen("don.txt", "r");
    if(f == NULL){
        printf("problem avec le fichier.\n");
        exit(1);
    } else {
        while(fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d",
              d.id,
              d.cin,
              &d.type_don_sang,
              &d.type_don_plasma,
              &d.type_don_plaquette,
              d.groupe_sanguin,
              &d.rhesus,
              &d.quantite,
              d.etablissement,
              &d.jour,
              &d.mois,
              &d.annee) == 12) {
            if (strcmp(d.id, id) == 0) {
                printf("%s %s %d %d %d %s %d %.2f %s %d %d %d\n",
                       d.id,
                       d.cin,
                       d.type_don_sang,
                       d.type_don_plasma,
                       d.type_don_plaquette,
                       d.groupe_sanguin,
                       d.rhesus,
                       d.quantite,
                       d.etablissement,
                       d.jour,
                       d.mois,
                       d.annee);
                fclose(f);
                return; 
            }
        }
        fclose(f);
        printf("don avec ID %s pas trouve.\n", id);  // Use %d to print integer
    }
}

void modifier_don(){
    FILE *f, *temp; 
    don d_; 
    don *d; 
    d = &d_;
    int trouve = 0;  
    char id [LENGTH];

    printf("Donner l'id.\n"); 
    scanf("%s", id); 

    f = fopen("don.txt", "r");
    temp = fopen("temp.txt", "a+"); 

	
    if(f == NULL || temp == NULL){
        printf("probleme avec le fichier.\n"); 
        exit(1); 
    } else {
        while(fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d",
                          d->id,
                          d->cin,
                          &d->type_don_sang,
                          &d->type_don_plasma,
                          &d->type_don_plaquette,
                          d->groupe_sanguin,
                          &d->rhesus,
                          &d->quantite,
                          d->etablissement,
                          &d->jour,
                          &d->mois,
                          &d->annee) == 12){


            if(strcmp(d->id, id) == 0){
                trouve = 1; 
                d = saisir_don(d); 

                fprintf(temp, "%s %s %d %d %d %s %d %.2f %s %d %d %d\n",
                        d->id,
                        d->cin,
                        d->type_don_sang,
                        d->type_don_plasma,
                        d->type_don_plaquette,
                        d->groupe_sanguin,
                        d->rhesus,
                        d->quantite,
                        d->etablissement,
                        d->jour,
                        d->mois,
                        d->annee);
            } else {
                fprintf(temp, "%s %s %d %d %d %s %d %.2f %s %d %d %d\n",
                        d->id,
                        d->cin,
                        d->type_don_sang,
                        d->type_don_plasma,
                        d->type_don_plaquette,
                        d->groupe_sanguin,
                        d->rhesus,
                        d->quantite,
                        d->etablissement,
                        d->jour,
                        d->mois,
                        d->annee);
            }
        }
        fclose(f);
        fclose(temp);

        if (trouve == 1) {
            remove("don.txt");
            rename("temp.txt", "don.txt");
            printf("Don avec l'ID %s modifié avec succès.\n", id);
        } else {
            remove("temp.txt");
            printf("Aucun don trouvé avec l'ID %s.\n", id);
        }
    }

}


don * saisir_don(don *d){
		int input; 

	do{
		printf("donner id.\n");
		scanf("%s", d->id);
		while(getchar() != '\n');  
	}while(champ_vide(d->id) == 1); 


	do{
		printf("donner cin.\n"); 
		scanf("%s", d->cin);
		while(getchar() != '\n'); 
	}while(champ_vide(d->cin) == 1); 

	do{
		printf("type sang: 0 non, 1 oui.\n"); 
		scanf("%d", &d->type_don_sang);
		while(getchar() != '\n');
	}while(d->type_don_sang != 0 && d->type_don_sang != 1);

	do{
		printf("type plasma: 0 non, 1 oui.\n"); 
		scanf("%d", &d->type_don_plasma);
		while(getchar() != '\n');
	}while(d->type_don_plasma != 0 && d->type_don_plasma != 1); 

	do{
		printf("type plaquette: 0 non, 1 oui.\n"); 
		scanf("%d", &d->type_don_plaquette);
		while(getchar() != '\n');
	}while(d->type_don_plaquette != 0 && d->type_don_plaquette != 1); 

	do{
		printf("donner groupe sanguin.\n");
		printf("0 : A\n"); 
		printf("1 : AB\n"); 
		printf("2 : B\n"); 
		printf("3: O\n"); 
		scanf("%d",&input);  
		while(getchar() != '\n');
	}while(input != 0 && input != 1 && input != 2 && input != 3); 

	switch(input){
		case 0: 
			strcpy(d->groupe_sanguin, "A"); 
			break; 
		case 1:
			strcpy(d->groupe_sanguin, "AB"); 
			break; 
		case 2:
			strcpy(d->groupe_sanguin, "B");
			break; 
		case 3:
			strcpy(d->groupe_sanguin, "O");			
			break; 	
	}

	do{
		printf("rhesus.\n");
		printf("0: - , 1: +.\n");
		scanf("%d", &d->rhesus); 
		while(getchar() != '\n');
	}while(d->rhesus != 0 && d->rhesus != 1 ); 

	do{
		printf("donner la quantite.\n"); 
		scanf("%f", &d->quantite); 
		while(getchar() != '\n');
	}while(!d->quantite); 

	do{
		printf("donner etablissment.\n"); 
		scanf("%s", d->etablissement); 
		while(getchar() != '\n');		
	}while(champ_vide(d->etablissement) == 1); 

	do{
		printf("donner le jour.\n");
		scanf("%d", &d->jour); 
	}while(!d->jour); 

	do{
		printf("donner le mois.\n");
		scanf("%d", &d->mois); 
	}while(!d->mois);

	do{
		printf("donner l'annee.\n");
		scanf("%d", &d->annee); 
	}while(!d->annee);


	return d; 
}

int champ_vide(char *str){
	if(strlen(str) == 0){
		return 1;
	}	
	return -1; 
}

void supprimer_don(){
	 FILE *f, *temp; 
    don d_; 
    don *d; 
    d = &d_;
    int trouve = 0;  
    char id [LENGTH];
    printf("Donner l'id.\n"); 
    scanf("%s", id); 

    f = fopen("don.txt", "r");
    temp = fopen("temp.txt", "w"); 

    if(f == NULL || temp == NULL){
        printf("probleme avec le fichier.\n"); 
        exit(1); 
    } else {
        while(fscanf(f, "%s %s %d %d %d %s %d %f %s %d %d %d",
                          d->id,
                          d->cin,
                          &d->type_don_sang,
                          &d->type_don_plasma,
                          &d->type_don_plaquette,
                          d->groupe_sanguin,
                          &d->rhesus,
                          &d->quantite,
                          d->etablissement,
                          &d->jour,
                          &d->mois,
                          &d->annee) == 12){

            if(strcmp(d->id, id) == 0){
                trouve = 1; 
                printf("Don avec l'ID %s supprimé avec succès.\n", id);
            } else {
                fprintf(temp, "%s %s %d %d %d %s %d %f %s %d %d %d\n",
                        d->id,
                        d->cin,
                        d->type_don_sang,
                        d->type_don_plasma,
                        d->type_don_plaquette,
                        d->groupe_sanguin,
                        d->rhesus,
                        d->quantite,
                        d->etablissement,
                        d->jour,
                        d->mois,
                        d->annee);
            }
        }
        fclose(f);
        fclose(temp);

        if (trouve == 1) {
            remove("don.txt");
            rename("temp.txt", "don.txt");
        } else {
            remove("temp.txt");
            printf("Aucun don trouvé avec l'ID %s.\n", id);
        }
    }

}
