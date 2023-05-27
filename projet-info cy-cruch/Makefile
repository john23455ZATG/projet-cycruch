cc=gcc

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
all: EXEC


main.o: main.c
	$(cc) -c main.c -o main.o

fonction.o: fonction.c
	$(cc) -c fonction.c -o fonction.o

affiche.o: affiche.c
	$(cc) -c  affiche.c -o affiche.o

sauvegarde.o: sauvegarde.c
	$(cc) -c sauvegarde.c -o sauvegarde.o



EXEC: fonction.o main.o affiche.o sauvegarde.o
	$(cc) $(OBJ) -o Exec -lm
clean:
	rm *.o EXEC
