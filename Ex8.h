#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"
#include "Ex6.h"
#include "Ex7.h"
#ifndef _EX8_H_
#define _EX8_H_

typedef struct block_tree_cell{
	Block* block;
	struct block_tree_cell* father;
	struct block_tree_cell* firstChild;
	struct block_tree_cell* nextBro;
	int height;
}CellTree;

CellTree* create_node(Block* b);
int update_height(CellTree* father, CellTree* child);
void add_child(CellTree* father, CellTree* child);
void print_tree(CellTree* ct);
void delete_node(CellTree* node);
void delete_tree(CellTree* ct);
CellTree* highest_child(CellTree* cell);
CellTree* last_node(CellTree* tree);
CellProtected* fusionChaine(CellProtected* cp1, CellProtected* cp2);
CellProtected* fusionChaineTree(CellTree* t);

#endif
