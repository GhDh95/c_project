my_prog:functions.o main.o
	gcc functions.o main.o -o my_prog
main.o:main.c
	gcc -c main.c
functions.o:functions.c
	gcc -c functions.c
