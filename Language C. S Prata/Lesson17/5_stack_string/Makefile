all: prog

prog: stack.o stack_string.o
	gcc -o prog stack.o stack_string.o

stack.o: stack.c
	gcc -c -o stack.o stack.c

stack_string.o: stack_string.c
	gcc -c -o stack_string.o stack_string.c

clean:
	rm -rf *.o prog