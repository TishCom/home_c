all: prog

prog: driver.o FSM.o
	gcc -o prog driver.o FSM.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

FSM.o: FSM.c
	gcc -c -o FSM.o FSM.c

clean:
	rm -rf *.o prog