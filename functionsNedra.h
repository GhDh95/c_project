#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH 40



typedef struct Don{
	char id [LENGTH];
	char cin [LENGTH]; 
	int type_don_sang;	 
	int type_don_plasma;	 
	int type_don_plaquette;	 
	char groupe_sanguin [LENGTH]; 
	int rhesus; 
	float quantite; 
	char etablissement [LENGTH]; 
	int jour, mois, annee;  
	

	
}don; 

void ajouter_don();
don * saisir_don(don *d); 
int champ_vide(char *str);
void afficher_don_tout(); 
void afficher_don(); 
void modifier_don(); 
void supprimer_don();

#endif
