all: prog

prog: driver.o queue.o
	gcc -o prog driver.o queue.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

queue.o: queue.c
	gcc -c -o queue.o queue.c

clean:
	rm -rf *.o prog