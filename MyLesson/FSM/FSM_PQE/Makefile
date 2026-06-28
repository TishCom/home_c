all: prog

prog: driver.o fsm.o ring_buffer_fsm.o
	gcc -o prog driver.o fsm.o ring_buffer_fsm.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

FSM.o: fsm.c 
	gcc -c -o fsm.o fsm.c 

ring_buffer_fsm.o: ring_buffer_fsm.c
	gcc -c -o ring_buffer_fsm.o ring_buffer_fsm.c

clean:
	rm -rf *.o prog