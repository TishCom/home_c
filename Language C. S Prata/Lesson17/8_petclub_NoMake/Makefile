all: prog

prog: tree.o petclub.o list.o
	gcc -o prog tree.o petclub.o list.o

tree.o: tree.c
	gcc -c -o tree.o tree.c

petclub.o: petclub.c
	gcc -c -o petclub.o petclub.c

list.o: list.c tree.h
	gcc -c -o list.o list.c

clean:
	rm -rf *.o prog