all: prog

prog: driver.o list.o
	gcc -o prog driver.o list.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

list.o: list.c
	gcc -c -o list.o list.c

clean:
	rm -rf *.o prog