all : main clean

main : main.o fonction.o
	@gcc -Wall -o main main.o fonction.o

main.o : main.c fonction.h
	@gcc -Wall -c main.c fonction.h

fonction.o : fonction.c fonction.h
	@gcc -Wall -c fonction.c fonction.h

clean :
	@rm -f *.o *.h.gch