all: prog

prog: driver.o fsm.o event_buffer_fsm.o
	gcc -o prog driver.o fsm.o event_buffer_fsm.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

fsm.o: fsm.c 
	gcc -c -o fsm.o fsm.c 

event_buffer_fsm.o: event_buffer_fsm.c
	gcc -c -o event_buffer_fsm.o event_buffer_fsm.c

clean:
	rm -rf *.o prog