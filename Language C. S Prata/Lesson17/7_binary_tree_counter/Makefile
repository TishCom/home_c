all: prog

prog: tree.o binary_tree_counter.o
	gcc -o prog tree.o binary_tree_counter.o

tree.o: tree.c
	gcc -c -o tree.o tree.c

binary_tree_counter.o: binary_tree_counter.c
	gcc -c -o binary_tree_counter.o binary_tree_counter.c

clean:
	rm -rf *.o prog