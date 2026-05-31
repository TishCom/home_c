all: prog

prog: driver.o stack.o
	gcc -o prog driver.o stack.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

stack.o: stack.c
	gcc -c -o stack.o stack.c

clean:
	rm -rf *.o prog