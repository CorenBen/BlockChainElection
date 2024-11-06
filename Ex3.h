#include "Ex1.h"
#include "Ex2.h"
#ifndef _EX3_H_
#define _EX3_H_

typedef struct key{
	long c1;
	long c2;
} Key;

void init_key(Key* key, long val, long n);
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);
char* key_to_str(Key* key);
Key* str_to_key(char* str);

typedef struct signature{
	long* content;
	int size;
} Signature;

Signature* init_signature(long* content, int size);
Signature* sign(char* mess, Key* skey);
char* signature_to_str(Signature* sgn);
Signature* str_to_signature(char * str);

typedef struct protected{
	Key* pkey;
	char* mess;
	Signature* s;
} Protected;

Protected* init_protected(Key* pKey, char* mess, Signature* sgn);
int verify(Protected* pr);
Protected* str_to_protected(char* msg);
char* protected_to_str(Protected* pr);

void libere_sign(Signature* s);
void libere_pr(Protected* p);

#endif
