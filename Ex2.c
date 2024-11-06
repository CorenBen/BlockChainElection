#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Ex1.h"
#include "Ex2.h"

long extended_gcd(long s, long t, long *u, long *v){
	if(s==0){
		*u = 0;
		*v = 1;
		return t;
	}
	long uPrim, vPrim;
	long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
	*u = vPrim -(t/s)*uPrim;
	*v = uPrim;
	return gcd;
}

void generate_key_values(long p, long q, long* n, long *s, long* u){
	*n = p*q;
	long t = (p-1) * (q-1);
	long v;
	*s = rand_long(1,t);
	while(extended_gcd(*s,t,u,&v)!=1){
		*s = rand_long(1,t);
	}
}

long* encrypt(char* chaine, long s, long n){
	int l = strlen(chaine);
	long m;
	long* c = (long*) malloc(sizeof(long)*l);
	for(int i=0;i<l;i++){
		m = (long)chaine[i];
		c[i] = modpow(m,s,n);
	}
	return c;
}

char* decrypt(long* crypted, int size, long u, long n){
	char* chaine = (char*) malloc(sizeof(char)*size);
	int m ;
	for(int i=0;i<size;i++){
		m = modpow(crypted[i],u,n);
		sprintf(&chaine[i],"%c",m);
	}
	chaine[size] = '\0';
	return chaine;
}

void test2(){
	/*Question 1
	long p = 12;
	long q = 18;
	long n, s, u;
	generate_key_values(p,q,&n,&s,&u);
	printf("Clé publique = (%ld,%ld)\n",s,n);
	printf("Clé secrète = (%ld,%ld)\n",u,n);
	*/
	
	
}
