all: proyecto

proyecto: Main.o Funciones.o
	gcc -o proyecto Main.o Funciones.o -lncurses -lm
Main.o: Main.c Funciones.h
	gcc -c Main.c -lncurses -lm -g

Funciones.o: Funciones.c Funciones.h 
	gcc -c Funciones.c -lm -lncurses -g

clean:
	rm -f proyecto *.o