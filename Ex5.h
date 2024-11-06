#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#ifndef _EX5_H_
#define _EX5_H_

typedef struct cellKey {
	Key * data ;
	struct cellKey * next ;
} CellKey ;

CellKey* create_cell_key(Key* key);
CellKey* add_key(CellKey* ck, Key* key);
CellKey* read_public_keys(FILE* f);
void print_list_keys(CellKey* LCK);
void delete_cell_keys(CellKey* c);
void delete_list_keys(CellKey* c);

typedef struct cellProtected {
	Protected * data ;
	struct cellProtected * next ;
} CellProtected ;

CellProtected* create_cell_protected(Protected* pr);
CellProtected* add_protected(CellProtected* cp, Protected* pr);
CellProtected* read_protected(FILE* f);
void print_protected(CellProtected* cp);
CellProtected* delete_cell_protected(CellProtected* c);
void delete_list_cell_protected(CellProtected* c);


#endif
