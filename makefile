main : main.o Ex9.o Ex8.o Ex7.o Ex6.o Ex5.o Ex4.o Ex3.o Ex2.o Ex1.o
	gcc -o main main.o Ex9.o Ex8.o Ex7.o Ex6.o Ex5.o Ex4.o Ex3.o Ex2.o Ex1.o -lm -lssl -lcrypto

main.o : main.c Ex1.h Ex2.h Ex3.h Ex4.h Ex5.h Ex6.h Ex7.h Ex8.h Ex9.h
	gcc -c main.c -lm -Wall

Ex9.o : Ex9.c Ex9.h Ex8.h Ex7.h Ex6.h Ex5.h Ex4.h Ex3.h Ex2.h Ex1.h
	gcc -c Ex9.c -Wall

Ex8.o : Ex8.c Ex8.h Ex7.h Ex6.h Ex5.h Ex4.h Ex3.h Ex2.h Ex1.h
	gcc -c Ex8.c -Wall

Ex7.o : Ex7.c Ex7.h Ex6.h Ex5.h Ex4.h Ex3.h Ex2.h Ex1.h
	gcc -c Ex7.c -Wall

Ex6.o : Ex6.c Ex6.h Ex5.h Ex4.h Ex3.h Ex2.h Ex1.h
	gcc -c Ex6.c -Wall
	
Ex5.o : Ex5.c Ex5.h Ex4.h Ex3.h Ex2.h Ex1.h
	gcc -c Ex5.c -Wall

Ex4.o : Ex4.c Ex4.h Ex3.h Ex2.h Ex1.h
	gcc -c Ex4.c -Wall

Ex3.o : Ex3.c Ex3.h Ex2.h Ex1.h
	gcc -c Ex3.c -Wall

Ex2.o : Ex2.c Ex2.h Ex1.h
	gcc -c Ex2.c -Wall

Ex1.o : Ex1.c Ex1.h
	gcc -c Ex1.c -Wall

clean :
	rm -f *.o main
