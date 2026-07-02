all: prog

prog: driver.o fsm.o
	gcc -o prog driver.o fsm.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

fsm.o: fsm.c
	gcc -c -o fsm.o fsm.c

clean:
	rm -rf *.o prog