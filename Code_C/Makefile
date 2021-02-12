$(EXEC)
EXEC = my_emul_mips
all: main.o convert.o affichage.o memory.o register.o
	gcc -Wall -g *.o -o $(EXEC)
	rm -rf *.o
main.o: main.c
	gcc -Wall -g -c main.c
convert.o: convert.c convert.h
	gcc -Wall -g -c convert.c
memory.o: memory.c memory.h
	gcc -Wall -g -c memory.c
register.o: register.c register.h
	gcc -Wall -g -c register.c
affichage.o: affichage.c affichage.h
	gcc -Wall -g -c affichage.c
clean: 
	rm -rf *.o 