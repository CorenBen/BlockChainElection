#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <dirent.h>

#include <openssl/sha.h>

#include "Ex1.h"
#include "Ex2.h"
#include "Ex3.h"
#include "Ex4.h"
#include "Ex5.h"
#include "Ex6.h"
#include "Ex7.h"
#include "Ex8.h"
#include "Ex9.h"

void print_long_vector ( long * result , int size ) {
	printf ( "Vector : [\t") ;
	for ( int i =0; i < size ; i ++) {
		printf ( "%lx \t", result[i]) ;
	}
	printf ( "] \n") ;
}

char* content_to_str(Signature* s){
	//Permet de transformer le tableau dans une Signature en chaine de characteres
	char* chaine = (char*)malloc(sizeof(char)*s->size);
	for(int i=0;i<s->size;i++){
		chaine[i] = s->content[i];
	}
	return chaine;
}

int main (){
	srand ( time ( NULL ) ) ;
///////////// TEST EXERCICE 2
/*
	//Generation de cle :
	long p = random_prime_number (3 ,7 , 5000) ;
	long q = random_prime_number (3 ,7 , 5000) ;
	while ( p == q ) {
		q = random_prime_number (3 ,7 , 5000) ;
	}
	long n , s , u ;
	printf(" \n");
	generate_key_values(p,q,&n,&s,&u) ;
	//Pour avoir des cles positives :
	if (u <0) {
		long t = (p-1) * (q-1) ;
		u = u + t ; //on aura toujours s*u mod t = 1
	}
	printf("p : %lx, q : %lx, n : %lx, s : %lx, u : %lx\n",p,q,n,s,u);
	//Afichage des cles en hexadecimal
	printf ( "clepublique = (%lx , %lx ) \n",s ,n ) ;
	printf ( "cleprivee = (%lx , %lx ) \n",u , n ) ;
	
	//Chiffrement:
	char mess [10] = "Hello" ;
	int len = strlen( mess ) ;
	long * crypted = encrypt(mess , s , n );
	
	printf( "Initial message : %s \n" , mess ) ;
	printf( "Encoded representation : \n" ) ;
	print_long_vector( crypted , len ) ;

	//Dechiffrement
	printf("crypted : %lx , len : %d , u : %lx, n : %lx\n", *crypted , len , u , n);
	char * decoded = decrypt( crypted , len , u , n ) ;
	printf( "Decoded : %s \n" , decoded ) ;

*/
///////////////////////// TEST EXERCICE 3
/*
	//Testing Init Keys
	Key* pKey = malloc(sizeof(Key));
	Key* sKey = malloc(sizeof(Key));
	init_pair_keys( pKey , sKey ,3 ,7) ;
	printf("pKey : %ld , %ld \n", pKey -> c1 , pKey -> c2 ) ;
	printf("sKey : %ld , %ld \n", sKey -> c1 , sKey -> c2 ) ;

	//Testing Key Serialization
	
	printf(" \n");
	char* chaine = key_to_str(pKey) ;
	printf("key_to_str : %s \n", chaine) ;
	Key* k = str_to_key(chaine);
	printf("str_to_key : %ld, %ld \n", k -> c1 , k -> c2);

	//Testing signature
	//Candidate keys:
	Key* pKeyC = malloc(sizeof(Key));
	Key* sKeyC = malloc(sizeof(Key));
	init_pair_keys( pKeyC , sKeyC ,3 ,7) ;
	printf(" \n");
	//Declaration:
	char* mess = key_to_str(pKeyC) ;
	printf("%s vote pour %s \n" ,key_to_str(pKey), mess);
	Signature* sgn = sign(mess, sKey);
	printf("signature : " );
	print_long_vector( sgn -> content , sgn -> size ) ;
	chaine = signature_to_str( sgn ) ;
	printf("signature_to_str : %s \n",chaine);
	sgn = str_to_signature(chaine);
	printf("str_to_signature : ");
	print_long_vector( sgn -> content , sgn -> size ) ;


	//Testing protected:
	Protected* pr = init_protected(pKey, mess, sgn);
	//Verification:
	if(verify(pr)){
		printf("Signature valide \n") ;
	}
	else {
		printf ("Signature non valide \n");
	}
	chaine = protected_to_str(pr);
	printf("protected_to_str : %s\n", chaine);
	pr = str_to_protected(chaine);
	printf("str_to_protected : %s %s %s \n", key_to_str(pr->pkey), pr->mess,
signature_to_str(pr->s));

	free ( pKey ) ;
	free ( sKey ) ;
	free ( pKeyC ) ;
	free ( sKeyC ) ;
*/
///////////////////////// TEST EXERCICE 4
	//generate_random_data(8,3);

///////////////////////// TEST EXERCICE 5
/*
	Key* pKeyC = malloc(sizeof(Key));
	Key* sKeyC = malloc(sizeof(Key));
	pKeyC -> c1 = 12;
	pKeyC -> c2 = 13;
	sKeyC -> c1 = 14;
	sKeyC -> c2 = 15;
	CellKey* c = create_cell_key(pKeyC);
	add_key(c,sKeyC);


	//Test fonction add_key
	while(c !=NULL){
		printf("%s\n",key_to_str(c -> data));
		c = c -> next;
	}

	//Test lecture clés et protected
	FILE* f = fopen("keys.txt","r");
	print_list_keys(read_public_keys(f));
	fclose(f);
	printf("\n");
	
	FILE* f2 = fopen("declarations.txt","r");
	print_protected(read_protected(f));
	fclose(f2);

*/
/*
	//Test suppression
	FILE* f = fopen("declarations.txt","r");

	CellProtected* votes = read_protected(f);
	delete_list_cell_protected(votes);
	fclose(f);
*/
////////////////////////// TEST EXERCICE 6
/*
	//Test Fraude
	FILE* f = fopen("declarations.txt","r");

	CellProtected* votes = read_protected(f);
	fraude(votes);
	
	fclose(f);
*/
/*
	//Test création de hashtable et recherche de clés
	Key* pKeyC = malloc(sizeof(Key));
	Key* sKeyC = malloc(sizeof(Key));
	pKeyC -> c1 = 12;
	pKeyC -> c2 = 13;
	sKeyC -> c1 = 14;
	sKeyC -> c2 = 15;
	CellKey* c = create_cell_key(pKeyC);
	c = add_key(c,sKeyC);
	HashTable* ht = create_hashtable(c,5);
	printf("%d\n",find_position(ht,pKeyC));
	printf("%d\n",find_position(ht,sKeyC));
*/

////////////////////////// TEST EXERCICE 7
/*
	//Test Ecriture de block dans un fichier
	FILE* f = fopen("declarations.txt","r");

	Key* author = malloc(sizeof(Key));
	author -> c1 = 12;
	author -> c2 = 13;
	
	CellProtected* votes = read_protected(f);
	unsigned char* hash = (unsigned char*)malloc(sizeof(unsigned char)*1000);
	unsigned char* previous_hash = (unsigned char*)malloc(sizeof(unsigned char)*1000);
	hash = "aab";
	previous_hash = "aaa";
	int nonce = 0;
	
	Block* b = malloc(sizeof(Block));
	b -> author = author;
	b -> votes = votes;
	b -> hash = hash;	
	b -> previous_hash = previous_hash;
	b -> nonce = nonce;
	
	ecrire_block(b);


	//Test Lecture fichier block
	FILE* f = fopen("block.txt","r");
	printf("%s\n",block_to_str(read_block(f)));
	fclose(f);
*/
/*
	//Test fonction hache
	const char *s = "Rosetta_code";
	unsigned char* d = hache(s);
	int i;
	for(i=0;i<SHA256_DIGEST_LENGTH;i++){
		printf("%02x",d[i]);
	}
	putchar('\n');

	compute_proof_of_work(b,3);
*/

/////////////////////////////// TEST EXERCICE 8
/*
	FILE* f = fopen("block.txt","r");
	CellTree* pere = create_node(read_block(f));
	CellTree* fils1 = create_node(read_block(f));
	CellTree* fils2 = create_node(read_block(f));
	CellTree* fils3 = create_node(read_block(f));
	add_child(pere,fils1);
	add_child(pere,fils2);
	add_child(pere,fils3);
	//Arbre à 3 fils
	print_tree(pere);
	
	//Les fonctions de libération ne marchent pas si les blocs sont identiques
*/

///////////////////////////////// TEST EXERCICE 9
/*
	Key* pKeyC = malloc(sizeof(Key));
	Key* sKeyC = malloc(sizeof(Key));
	init_pair_keys( pKeyC , sKeyC ,3 ,7) ;
	char* mess = key_to_str(pKeyC) ;
	Signature* sgn = sign(mess, sKeyC);

	Protected* pr = init_protected(pKeyC, mess, sgn);
	submit_vote(pr);
	
	FILE* f = fopen("block.txt","r");
	CellTree* ct = create_node(read_block(f));
	create_block(ct,pKeyC,3);
*/

/////////////////////////////// TEST FINAL
/*
	generate_random_data(1000,5);
	FILE* declaration = fopen("declarations.txt","r");
	FILE* key = fopen("keys.txt","r");
	FILE* candidat = fopen("candidates.txt","r");
	
	CellKey* cell_keys = read_public_keys(key);
	CellKey* cell_candidates = read_public_keys(candidat);
	CellProtected* cell_decla = read_protected(declaration);
	
	//print_list_keys(cell_keys);
	//print_list_keys(cell_candidates);
	//print_protected(cell_decla);
	
	CellProtected* c = cell_decla;
	while(c != NULL){
		submit_vote(c -> data);
		c = c -> next;
	}
*/
	read_tree();
	return 0;

}
