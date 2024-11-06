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
#include "Ex6.h"

void fraude(CellProtected* cp){
	//On suppose qu'une signature non valide signifie qu'elle n'est pas égale au message encrypté
	Signature* s = init_signature(encrypt(cp -> data -> mess,cp -> data -> pkey -> c1,cp -> data -> pkey -> c2),strlen(cp -> data -> mess));
	char* s1 = signature_to_str(s);
	char *s2 = signature_to_str(cp -> data -> s);
	while(cp != NULL){
		if(strcmp(s1,s2)==0){
			printf("Signature non valide.\n");
			cp = delete_cell_protected(cp);
		}
		else{
			cp = cp -> next;
		}
	}
}

HashCell* create_hashcell(Key* key){
	HashCell* hc = (HashCell*)malloc(sizeof(HashCell));
	hc -> key = key;
	hc -> val = 0;
	return hc;
}

int hash_function(Key* key, int size){
	//On suppose que pour calculer la position d'une clé dans sa table de hachage on effectue le calcul (c1 + c2) modulo taille de la table
	return (key -> c1 + key -> c2) % size;
}

int find_position(HashTable* t, Key* key){
	int i=0;
	while(t -> tab[i] != NULL){
		if(t -> tab[i] -> key == key){
			return i;
		}
		i+=1;
	}
	printf("eeee\n");
	return hash_function(key,t -> size);
}

HashTable* create_hashtable(CellKey* keys, int size){
	//On suppose que la taille de la cellule de clés est inférieur ou égale à size
	HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
	HashCell** hc = (HashCell**)malloc(sizeof(HashCell*)*size);
	int i=0;
	while(keys != NULL){
		hc[i] = (HashCell*)malloc(sizeof(HashCell));
		hc[i] -> key = keys -> data;
		hc[i] -> val = 0;
		keys = keys -> next;
		i+=1;
	}
	ht -> tab = hc;
	ht -> size = size;
	return ht;
}

void delete_hashtable(HashTable* t){
	for(int i=0;i<t -> size;i++){
		free(t -> tab[i] -> key);
	}
	free(*(t -> tab));
	free(t);
}

Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV){
	HashTable* hc = create_hashtable(candidates,sizeC);
	HashTable* hv = create_hashtable(voters,sizeV);
	int pos;
	int max = 0;
	Key* winner;
	for(int i=0;i<sizeV;i++){
		while(decl != NULL){
			if(hv -> tab[i] -> key == decl -> data -> pkey || hv -> tab[i] -> val == 0){ //Vérifie le droit de vote du citoyen et son unicité
				pos = find_position(hc,str_to_key(decl -> data -> mess));
				hc -> tab[pos] -> val += 1;
				hv -> tab[i] -> val = 1;	
			}
			decl = decl -> next;
		}
	}
	for(int i=0;i<sizeC;i++){
		if(hc -> tab[i] -> val > max){
			max = hc -> tab[i] -> val;
			winner = hc -> tab[i] -> key;
		}
	}
	return winner;
}
