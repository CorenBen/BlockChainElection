#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"

void init_key(Key* key, long val, long n){
	key->c1 = val;
	key->c2 = n;
}

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size){
	long p = random_prime_number (low_size ,up_size , 5000) ;
	long q = random_prime_number (low_size,up_size, 5000) ;
	while ( p == q ) {
		q = random_prime_number (3 ,7 , 5000) ;
	}
	long n , s , u ;
	generate_key_values(p,q,&n,&s,&u) ;
	//Pour avoir des cles positives :
	if (u <0) {
		long t = (p-1) * (q-1) ;
		u = u + t ; //on aura toujours s*u mod t = 1
	}
	
	//Attribution des valeurs aux clés
	init_key(pKey,s,n);
	init_key(sKey,u,n);
}

char* key_to_str(Key* key){
	char* s = (char*)malloc(sizeof(char)*1000);
	sprintf(s,"(%lx,%lx)",key->c1,key->c2);
	return s;
}

Key* str_to_key(char* str){
	Key* k = malloc(sizeof(Key));
	long c1,c2;
	sscanf(str,"(%lx,%lx)",&c1,&c2);
	init_key(k,c1,c2);
	return k;	
}

Signature* init_signature(long* content, int size){
	Signature* s = (Signature*) malloc(sizeof(Signature));
	s->content = content;
	s->size = size;
	return s;
}

Signature* sign(char* mess, Key* skey){
	int size = strlen(mess);
	long* content = encrypt(mess,skey->c1,skey->c2);
	Signature *s = init_signature(content,size);
	return s;
}

char* signature_to_str(Signature* sgn){
	char* result = malloc (10* sgn -> size * sizeof (char) ) ;
	result[0]= '#' ;
	int pos = 1;
	char buffer [156];
	for(int i =0; i < sgn -> size ; i ++){
		sprintf( buffer , "%lx" , sgn -> content[i]) ;
		for(int j =0; j < strlen (buffer) ; j++) {
			result [ pos ] = buffer[j];
			pos = pos +1;
		}
		result[pos] = '#' ;
		pos = pos +1;
	}
	result [ pos ] = '\0' ;
	result = realloc ( result , ( pos +1) * sizeof ( char ) ) ;
	return result ;
}

Signature* str_to_signature(char * str){
	int len = strlen(str) ;
	long * content = (long*) malloc ( sizeof ( long ) * len ) ;
	int num = 0;
	char buffer[256];
	int pos = 0;
	for(int i =0; i < len ; i ++) {
		if ( str[i] != '#') {
			buffer[pos] = str[i];
			pos = pos +1;
		} 
		else {
			if ( pos != 0) {
				buffer[pos] = '\0' ;
				sscanf ( buffer , "%lx" , &(content[num]) ) ;
				num = num + 1;
				pos = 0;
			}
		}
	}
	content = realloc( content , num * sizeof(long) ) ;
	return init_signature( content , num ) ;
}

Protected* init_protected(Key* pKey, char* mess, Signature* sgn){
	Protected* p = (Protected*) malloc(sizeof(Protected));
	p -> pkey = pKey;
	p -> mess = mess;
	p -> s = sgn;
	p -> s -> content = sgn -> content;
	return p;
}

int verify(Protected* pr){
	return (strcmp(pr -> mess,decrypt(pr -> s -> content, pr -> s -> size, pr -> pkey -> c1, pr -> pkey -> c2))==0);
}

Protected* str_to_protected(char* msg){
	Key* k = (Key*)malloc(sizeof(Key));
	long c1,c2;
	char* m = (char*)malloc(sizeof(char)*1000);
	char* sign = (char*)malloc(sizeof(char)*1000);
	sscanf(msg,"Clé publique : (%lx,%lx), Message : %s , Signature : %s \n",&c1,&c2,m,sign);
	init_key(k,c1,c2);
	Signature* s = str_to_signature(sign);
	Protected* p = init_protected(k,m,s);
	return p;
}

char* protected_to_str(Protected* pr){
	char* s = (char*)malloc(sizeof(char)*1000);
	char* sign = signature_to_str(pr -> s);
	sprintf(s,"Clé publique : (%lx,%lx), Message : %s , Signature : %s",pr -> pkey -> c1,pr -> pkey -> c2,pr -> mess,sign);
	free(sign);
	return s;	
}

void libere_sign(Signature* s){
	free(s->content);
	free(s);
}

void libere_pr(Protected* p){
	//On libèrera la clé séparément 
	free(p->mess);
	libere_sign(p->s);
	free(p);
}
