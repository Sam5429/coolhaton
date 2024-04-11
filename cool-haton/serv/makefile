all : main clean

main : test.o main.o fonction.o
	@gcc -Wall -o main main.o test.o fonction.o

main.o : main.c codeTest/test.h codeCli/fonction.h
	@gcc -Wall -c main.c codeTest/test.h codeCli/fonction.h

test.o : codeTest/test.c codeTest/test.h
	@gcc -Wall -c codeTest/test.c codeTest/test.h

fonction.o : codeCli/fonction.c codeCli/fonction.h
	@gcc -Wall -c codeCli/fonction.c codeCli/fonction.h

serv : serv.c
	gcc -Wall -o serv serv.c

#-f : pas de mess d'erreur si ficher existe pas
clean :
	@rm -f *.o code*/*.gch
	@rm -f codeCli/fonction.c
	@rm -f .main.c.swp
