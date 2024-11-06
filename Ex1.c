#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Ex1.h"

int is_prime_naive(long p){
	if(p%2==0){
		return 0;
	}
	for(int i=3;i<p;i++){
		if(p%i==0){
			return 0;
		}
	}
	return 1;
}

long modpow_naive(long a, long m, long n){
	int r = a;
	for(int i=0;i<m;i++){
		r = (r*a) % n;
	}
	return r;
}

int modpow(long a, long m, long n){
	int b;
	if(m==0){
		return 1;
	}
	else{
		a = a%n;
		if(m%2==0){
			b = modpow(a,m/2,n);
			return (b * b) % n;
		}
		else{
			b = modpow(a,floor(m/2),n);
			return (a * b * b) % n;
		}
	}
}

int witness(long a, long b, long d, long p){
	long x = modpow(a,d,p);
	if(x == 1){
		return 0;
	}
	for(long i = 0 ; i < b ; i++){
		if(x == p-1){
			return 0;
		}
		x = modpow(x,2,p);
	}
	return 1;
}

long rand_long(long low, long up){
	return rand() % (up - low +1)+ low;
}

int is_prime_miller(long p, int k){
	if (p==2){
		return 1;
	}
	if(!(p & 1) || p <= 1){
		return 0;
	}
	
	long b = 0;
	long d = p-1;
	while(!(d & 1)){
		d = d/2;
		b = b+1;
	}
	
	long a;
	int i;
	for(i=0;i<k;i++){
		a = rand_long(2,p-1);
		if(witness(a,b,d,p)){
			return 0;
		}
	}
	return 1;
}

long random_prime_number(int low_size, int up_size, int k){
	long mini = pow(2,low_size-1);
	long maxi = pow(2,up_size)-1;
	long p = rand_long(mini,maxi);
	while(is_prime_miller(p,k)!=1){
		p = rand_long(mini,maxi);
	}
	return p;
}

void test(){
	srand(time(NULL));

	/*Question 1 & 2
	int n = 99643;
	
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;
	temps_initial = clock ();
	is_prime_naive(n);
	temps_final = clock ();
	temps_cpu = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;
	
	printf("Nombre : %d ; Premier : %d ; Temps : %f\n",n,
	is_prime_naive(n),temps_cpu);
	*/
	
	/*Question 3 et 4
	printf("Naif : %ld ; Recursif : %d\n",modpow_naive(52,12,2),modpow(52,12,2));
	*/
	
	/*Question 5
	for(int a=100; a<200 ; a++){
		for(int b=50; b<a ; b++){
			for(int c=10; c<b ; c++){
				clock_t temps_initial1,temps_initial2;
				clock_t temps_final1,temps_final2;
				double temps_cpu1,temps_cpu2;
				temps_initial1 = clock ();
				modpow_naive(a,b,c);
				temps_final1 = clock ();
				temps_cpu1 = ((double) (temps_final1 - temps_initial1)) / CLOCKS_PER_SEC;
				
				temps_initial2 = clock ();
				modpow(a,b,c);
				temps_final2 = clock ();
				temps_cpu2 = ((double) (temps_final2 - temps_initial2)) / CLOCKS_PER_SEC;
				FILE* f = fopen("sortie_vitesse.txt","a");
				fprintf(f,"%f %f\n",temps_cpu1,temps_cpu2);
				fclose(f);
			}
		}
	}
	*/
	
	/*Question 8
	int k = 600;
	long p = random_prime_number(2,2000,k);
	printf("Numero : %ld ; Nb Test : %d ; Premier : %d\n",p,k,is_prime_naive(p));
	*/
	
}
