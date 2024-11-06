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
#include "Ex8.h"

CellTree* create_node(Block* b){
	CellTree* ct = (CellTree*)malloc(sizeof(CellTree));
	ct -> block = b;
	ct -> height = 0;
	ct -> father = ct;
	ct -> firstChild = NULL;
	ct -> nextBro = NULL;
	return ct;
}

int update_height(CellTree* father, CellTree* child){
	if((father -> height) < (child -> height) + 1){
		father -> height = child -> height + 1;
		return 1;
	}
	if(father != child){	//NE MARCHE PAS SI LES ARBRES SONT BASES SUR LE MEME BLOC
		update_height(father -> father,father);
	}
	return 0;
}

void add_child(CellTree* father, CellTree* child){
	if(father -> firstChild == NULL){
		father -> firstChild = child;
		update_height(father,child);
	}
	else{
		CellTree* c = father -> firstChild;
		while(c -> nextBro != NULL){
			c = c -> nextBro;
		}
		c -> nextBro = child;
	}
	child -> father = father;
}

void print_tree(CellTree* ct){
	if(ct != NULL){
		char* s = block_to_str(ct -> block);
		unsigned char* d = hache(s);
		if(ct -> father == ct){
			printf("Père = Hauteur : %d , ID : %s \n",ct -> height,d);
		}
		CellTree* copie = ct -> firstChild;
		while(copie != NULL){
			s = block_to_str(copie -> block);
			d = hache(s);
			printf("Hauteur : %d , ID : %s \n",copie -> height,d);
			print_tree(copie);
			copie = copie -> nextBro;
		}
	}
}

void delete_node(CellTree* node){
	delete_block(node -> block);
	CellTree* c = node -> father -> firstChild;
	if(c != node){
		while(c -> nextBro != node){
			c = c -> nextBro;
		}
		c -> nextBro = NULL;
	}
	free(node);
}

void delete_tree(CellTree* ct){
	CellTree* ct2;
	while(ct -> firstChild != NULL){
		ct2 = ct;
		while(ct2 -> firstChild != NULL){
			ct2 = ct2 -> firstChild;
		}
		while(ct2 -> nextBro != NULL){
			ct2 = ct -> nextBro;
		}
		delete_node(ct2);
	}
	delete_node(ct -> father);
}

CellTree* highest_child(CellTree* cell){
	if(cell -> firstChild == NULL){
		return cell;
	}
	int max = -1;
	CellTree* res;
	CellTree* c = cell -> firstChild;
	while(c -> nextBro != NULL){
		if(max < c -> height){
			max = c -> height;
			res = c;
		}
		c = c -> nextBro;
	}
	return res;
}

CellTree* last_node(CellTree* tree){
	CellTree* c = tree;
	while(c != highest_child(c)){
		c = highest_child(c);
	}
	return c;
}

CellProtected* fusionChaine(CellProtected* cp1, CellProtected* cp2){
	//Si l'on ajoute cp2 en tête de cp1 on peut atteindre une complexité en O(1)
	//Sinon ce sera en O(n) avec n la taille de la liste cp
	CellProtected* cp = cp1;
	while(cp -> next != NULL){
		cp = cp -> next;
	}
	cp -> next = cp2;
	return cp1;
}

CellProtected* fusionChaineTree(CellTree* t){
	CellProtected* cp = t -> block -> votes;
	CellTree* ct = t;
	while(ct != highest_child(ct)){
		cp = fusionChaine(cp,ct -> block -> votes);
		ct = highest_child(ct);
	}
	return cp;
}


