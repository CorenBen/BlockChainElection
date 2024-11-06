#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <openssl/sha.h>

#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"
#include "Ex6.h"
#include "Ex7.h"

#define MAX_LINE_LENGTH 1000 //Taille max d'une ligne de fichier pour fgets

void ecrire_block(Block* b){
	FILE* f = fopen("block.txt","w");
	char* c = (char*)malloc(sizeof(char)*1000);
	char* skp = key_to_str(b -> author); //Version texte de la clé de l'auteur
	char* spr; //Version texte d'une déclaration
	sprintf(c,"Auteur : %s , Valeur Hachée : %s , Valeur hachée précédente : %s , Preuve de Travail : %d\n",skp,b -> hash,b -> previous_hash,b -> nonce);
	fputs(c,f);
	while(b -> votes != NULL){
		spr = protected_to_str(b -> votes -> data);
		sprintf(c,"%s\n",spr);
		b -> votes = b -> votes -> next;
		free(spr);
		fputs(c,f);
	}
	
	free(skp);
	free(c);
}

Block* str_to_block(char* s){
	//Rend un bloc sans la liste de déclarations
	Block* b = (Block*)malloc(sizeof(Block));
	Key* k = (Key*)malloc(sizeof(Key));
	long c1,c2;
	unsigned char* vh = (char*)malloc(sizeof(char)*1000);
	unsigned char* vhp = (char*)malloc(sizeof(char)*1000);
	int pt;
	sscanf(s,"Auteur : (%lx,%lx) , Valeur Hachée : %s , Valeur hachée précédente : %s , Preuve de Travail : %d \n",&c1,&c2,vh,vhp,&pt);
	init_key(k,c1,c2);
	b -> author = k;
	b -> hash = vh;
	b -> previous_hash = vhp;
	b -> nonce = pt;
	return b;
}

Block* read_block(FILE* f){
	Block* b;
	Protected* pr;
	CellProtected* cp;
	int flag = 0;
	char line[MAX_LINE_LENGTH];
	//On vérifie l'existence du fichier
	if(f != NULL){
		while(fgets(line,MAX_LINE_LENGTH,f)){ //On récupère le fichier ligne par ligne
			if(flag == 0){ 
				b = str_to_block(line);
				flag = 1;
			}
			else{
				pr = str_to_protected(line);
				if(flag == 1){
					cp = create_cell_protected(pr);
					flag = 2;
				}
				else{
					cp = add_protected(cp,pr);
				}
			}
		}
	}
	else{
		printf("Fichier non existant.\n");
		exit(1);
	}
	b -> votes = cp;
	return b;
}

void print_block(Block* b){
	printf("Auteur : (%lx,%lx) , Valeur Hachée : %s , Valeur hachée précédente : %s , Preuve de Travail : %d \n",b -> author -> c1,b -> author -> c2,b -> hash,b -> previous_hash,b -> nonce);
	int i=1;
	char* c;
	CellProtected* cp = b -> votes;
	while(cp != NULL){
		c = protected_to_str(cp -> data);
		printf("Déclaration %d : %s\n",i,c);
		cp = cp -> next;
		i+=1;
		free(c);
	}
}

char* block_to_str(Block* b){
	char* s1 = (char*)malloc(sizeof(char)*10000);
	char* s2 = (char*)malloc(sizeof(char)*10000);
	char* c;
	int i=1;
	sprintf(s1,"Auteur : (%lx,%lx) , Valeur hachée précédente : %s , Preuve de Travail : %d \n",b -> author -> c1,b -> author -> c2,b -> previous_hash,b -> nonce);
	CellProtected* cp = b -> votes;
	while(cp != NULL){
		c = protected_to_str(cp -> data);
		sprintf(s2,"Déclaration %d : %s\n",i,c);
		cp = cp -> next;
		i+=1;
		free(c);
		strcat(s1,s2);
	}
	free(s2);
	return s1;
}

unsigned char* hache(char* s){
	unsigned char* d = SHA256(s,strlen(s),0);
	return d;
}

void compute_proof_of_work(Block* B, int d){

	//On créé la chaine de d zéros en supposant qu'il y en ai au moins un
	char* z = (char*)malloc(sizeof(char)*4*d);
	sprintf(z,"0");
	char* z2 = (char*)malloc(sizeof(char));
	sprintf(z2,"0");
	for(int i=0;i<4*d;i++){
		strcat(z,z2);
	}
	free(z2);
	char* c = block_to_str(B);
	while(strncmp(c,z,4*d)!=0){
		B->nonce+=1;
		free(c);
		c = block_to_str(B);
	}
	free(c);
	free(z);
}

int verify_block(Block* b, int d){

	//On créé la chaine de d zéros en supposant qu'il y en ai au moins un
	char* z = (char*)malloc(sizeof(char)*4*d);
	sprintf(z,"0");
	char* z2 = (char*)malloc(sizeof(char));
	sprintf(z2,"0");
	for(int i=0;i<4*d;i++){
		strcat(z,z2);
	}
	char* c = block_to_str(b);
	return (strncmp(c,z,4*d)==0);
}

void delete_block(Block* b){
	free(b -> hash);
	free(b -> previous_hash);
	CellProtected* v;
	while(b -> votes -> next!=NULL){
		v = b -> votes -> next;
		free(b -> votes);
		b -> votes = v;
	}
	free(b -> votes);
}
