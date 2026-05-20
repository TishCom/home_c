all: prog

prog: films3.o list.o
	gcc -o prog films3.o list.o

films3.o: films3.c
	gcc -c -o films3.o films3.c

list.o: list.c
	gcc -c -o list.o list.c

clean:
	rm -rf *.o prog