user_prog:functions_users.o user.o
	gcc functions_users.o user.o -o user_prog
user.o:user.c
	gcc -c user.c
functions_users.o:functions_users.c
	gcc -c functions_users.c
