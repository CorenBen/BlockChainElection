#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"

#define MAX_LINE_LENGTH 1000 //Taille max d'une ligne de fichier pour fgets

CellKey* create_cell_key(Key* key){
	CellKey* ck = (CellKey*)malloc(sizeof(CellKey));
	ck -> data = key;
	ck -> next = NULL;
	return ck;
}

CellKey* add_key(CellKey* ck, Key* key){
	CellKey* c = create_cell_key(key);
	c -> next = ck;
	return c;
	
}

CellKey* read_public_keys(FILE* f){
	CellKey* c;
	Key* k;
	int flag = 0; //On utilise un flag pour l'initialisation de c
	char line[MAX_LINE_LENGTH];
	//On vérifie l'existence et le nom du fichier
	if(f!=NULL){ //On vérifie que le fichier existe
		while(fgets(line,MAX_LINE_LENGTH,f)){ //On récupère le fichier ligne par ligne
			k = str_to_key(line);
			if(flag == 0){ 
				c = create_cell_key(k);
				flag = 1;
			}
			else{
				c = add_key(c,k);
			}
			
		}
	}
	else{
		printf("Fichier non existant.\n");
		exit(1);
	}
	return c;
}

void print_list_keys(CellKey* LCK){
	int i=1;
	char* c;
	while(LCK != NULL){
		c = key_to_str(LCK -> data);
		printf("Clé %d : %s \n",i,c);
		LCK = LCK -> next;
		i+=1;
		free(c);
	}
}

void delete_cell_keys(CellKey* c){
	free(c -> data);
	if(c -> next != NULL){
		CellKey* c2 = c;
		c = c -> next;
		free(c2);
	}
	else{
		free(c);
	}
}

void delete_list_keys(CellKey* c){
	while(c != NULL){
		delete_cell_keys(c);
	}
}

CellProtected* create_cell_protected(Protected* pr){
	CellProtected* cp = (CellProtected*)malloc(sizeof(CellProtected));
	cp -> data = pr;
	cp -> next = NULL;
	return cp;
}

CellProtected* add_protected(CellProtected* cp, Protected* pr){
	CellProtected* c = create_cell_protected(pr);
	c -> next = cp;
	return c;
}

CellProtected* read_protected(FILE* f){
	CellProtected* cp;
	Protected* pr;
	int flag = 0;
	char line[MAX_LINE_LENGTH];
	//On vérifie l'existence du fichier
	if(f != NULL){
		while(fgets(line,MAX_LINE_LENGTH,f)){ //On récupère le fichier ligne par ligne
			pr = str_to_protected(line);
			if(flag == 0){ 
				cp = create_cell_protected(pr);
				flag = 1;
			}
			else{
				cp = add_protected(cp,pr);
			}
		}
	}
	else{
		printf("Fichier non existant.\n");
		exit(1);
	}
	return cp;
}

void print_protected(CellProtected* cp){
	int i=1;
	char* c;
	while(cp != NULL){
		c = protected_to_str(cp -> data);
		printf("Déclaration %d : %s\n",i,c);
		cp = cp -> next;
		i+=1;
		free(c);
	}
}

CellProtected* delete_cell_protected(CellProtected* c){
	Protected *p = c -> data;
	free(p -> pkey);
	libere_sign(p -> s);
	free(p -> mess);
	if(c -> next != NULL){
		c -> data = c -> next -> data;
		CellProtected *c2 = c;
		c = c2 -> next;
		free(c2);
	}
	else{
		free(c);
	}
	free(p);
	return c;
}

void delete_list_cell_protected(CellProtected* c){
	while(c -> next != NULL){
		c = delete_cell_protected(c);
	}
	delete_cell_protected(c);
}
