#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"
#include "Ex6.h"
#ifndef _EX7_H_
#define _EX7_H_

typedef struct block{
	Key* author;
	CellProtected* votes;
	unsigned char* hash;
	unsigned char* previous_hash;
	int nonce;
}Block;

void ecrire_block(Block* b);
Block* str_to_block(char* s);
Block* read_block(FILE* f);
void print_block(Block* b);
char* block_to_str(Block* b);
unsigned char* hache(char* s);
void compute_proof_of_work(Block* B, int d);
int verify_block(Block* b, int d);
void delete_block(Block* b);

#endif
