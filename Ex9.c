#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>

#include <openssl/sha.h>

#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"
#include "Ex6.h"
#include "Ex7.h"
#include "Ex8.h"
#include "Ex9.h"

#define MAX_LINE_LENGTH 1000 //Taille max d'une ligne de fichier pour fgets

void submit_vote(Protected* p){
	FILE* f = fopen("Pending_votes.txt","a");
	char* s = protected_to_str(p);
	char* s2 = (char*)malloc(sizeof(char)*1000);
	sprintf(s2,"%s \n",s);
	fputs(s2,f);
	free(s);
	free(s2);
}

void create_block(CellTree* tree, Key* author, int d){
	Block* b = (Block*)malloc(sizeof(Block));
	FILE* f = fopen("Pending_votes.txt","r");
	FILE* f2 = fopen("Pending_block","w");
	CellProtected* cp;
	Protected* pr;
	int flag = 0;
	char line[MAX_LINE_LENGTH];
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
	
	b -> votes = cp;
	b -> author = author;
	b -> nonce = d;
	fclose(f);
	char* s = block_to_str(b);
	fputs(s,f2);
	free(s);
	remove("Pending_votes.txt");
	fclose(f2);
	
}

void add_block(int d, char* name){
	FILE* f = fopen("Pending_block","r");
	//if(verify_block(read_block(f),d); //Ne marche pas à cause du verify
	char* s = (char*)malloc(sizeof(char)*1000);
	char line[MAX_LINE_LENGTH];
	sprintf(s,"Blockchain/%s",name);
	FILE* f2 = fopen(s,"w");
	while(fgets(line,MAX_LINE_LENGTH,f)){
		fputs(line,f2);
	}
	fclose(f);
	fclose(f2);
	free(s);
	remove("Pending_block");
}

CellTree* read_tree(){
	CellTree* ct;
	DIR *rep = opendir("./Blockchain/");
	if(rep != NULL){
		struct dirent* dir;
		while((dir = readdir(rep))){
			if(strcmp(dir -> d_name,".")!=0 && strcmp(dir -> d_name,"..")!=0){
				printf("Chemin du fichier : ./Blockchaine/%s \n",dir -> d_name);
			}
		}
		closedir(rep);
	}
	return ct;
}














