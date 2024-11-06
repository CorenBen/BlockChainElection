#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"

int est_dans(int* tab, int n, int size){
	for(int i=0;i<size;i++){
		if(tab[i] == n){
			return 1;
		}
	}
	return 0;
}


void generate_random_data(int nv, int nc){

	//On vérifie que le nombre de clés candidates ne dépassent pas le nombre de citoyens
	if(nv<nc){
		printf("Plus de clés que de citoyens. Echec de la fonction.\n");
		return;
	}
	
	long *content;
	Key* kp = (Key*)malloc(sizeof(Key));
	Key* ks = (Key*)malloc(sizeof(Key));
	FILE* fkey = fopen("keys.txt","w");
	FILE* fcandidates = fopen("candidates.txt","w");
	FILE* fdeclarations = fopen("declarations.txt","w");
	char* c = (char*)malloc(sizeof(char)*1000);
	char* mess; //Clé publique citoyenne
	char* messCandidat; //Clé publique candidat choisi
	int* tab = (int*)malloc(sizeof(int)*1000); //Tableau d'indices des candidats
	int r,candidat_choisi,size;
	Signature* sign;
	Protected* pr;
	
	char* clepubl; //Version texte de kp
	char* clesecr; //Version texte de ks
	char* spr; //Version texte de pr
	
	//On initialise le tableau de clés
	Key** tabKey = (Key**)malloc(sizeof(Key*)*nv);
	for(int i=0;i<nv;i++){
		tabKey[i] = (Key*)malloc(sizeof(Key));
	}

	
	//Sélection des futures clés candidates
	for(int i=0;i<nc;i++){
		r = rand() % nv;
		tab[i] = r;
	}
	
	//Sélection du candidat dans la déclaration
	for(int i=0;i<nv;i++){ //On créé les clés citoyennes
		
		init_pair_keys(kp,ks,3,7);
		
		tabKey[i] -> c1 = kp -> c1;
		tabKey[i] -> c2 = kp -> c2;
		
		clepubl = key_to_str(kp);
		clesecr = key_to_str(ks);
		
		//Ecriture dans le fichier
		sprintf(c,"%s,%s\n",clepubl,clesecr);
		if(fkey!=NULL){
			fputs(c,fkey);
		}
		
		
		//On vérifie si la clé est candidate et l'ajoute si c'est le cas
		if(est_dans(tab,i,nc)){
			sprintf(c,"%s\n",clepubl);
			if(fcandidates!=NULL){
				fputs(c,fcandidates);
			}
		}
		
		free(clepubl);
		free(clesecr);
	}
	
	free(kp);
	free(ks);
	
	for(int i=0;i<nv;i++){ //On re-parcours les citoyens pour ne pas appeler une clé non existante
		r = rand() % nc;
		candidat_choisi = tab[r]; //On attribue une clé candidate aléatoire au citoyen courant
		messCandidat = key_to_str(tabKey[candidat_choisi]); //On transforme la clé publique du candidat choisi en message
		mess = key_to_str(tabKey[i]); //On transforme la clé publique du citoyen en message
		size = strlen(mess);
		
		//On créé les déclarations
		content = encrypt(mess,tabKey[i] -> c1, tabKey[i] -> c2);
		sign = init_signature(content,size);
		pr = init_protected(tabKey[i],messCandidat,sign);
		
		spr = protected_to_str(pr);
		
		//Ecriture dans le fichier
		sprintf(c,"%s\n",spr);
		if(fdeclarations!=NULL){
			fputs(c,fdeclarations);
		}
		
		free(spr);
		free(mess);
		libere_pr(pr);
	}

	
	fclose(fkey);
	fclose(fcandidates);
	fclose(fdeclarations);

	free(tab);
	free(c);
	
	for(int i=0;i<nv;i++){
		free(tabKey[i]);
	}
	free(tabKey);
}	
