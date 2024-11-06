#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"
#ifndef _EX6_H_
#define _EX6_H_

typedef struct hashcell{
	Key* key;
	int val;
} HashCell;

typedef struct hastable{
	HashCell** tab;
	int size;
} HashTable;

void fraude(CellProtected* cp);
HashCell* create_hashcell(Key* key);
int hash_function(Key* key, int size);
int find_position(HashTable* t, Key* key);
HashTable* create_hashtable(CellKey* keys, int size);
void delete_hashtable(HashTable* t);
Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);

#endif
