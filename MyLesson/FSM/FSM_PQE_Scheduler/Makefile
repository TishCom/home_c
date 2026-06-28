all: prog

prog: driver.o fsm.o ring_buffer_fsm.o fsm_scheduler_data.o fsm_scheduler.o
	gcc -o prog driver.o fsm.o ring_buffer_fsm.o fsm_scheduler_data.o fsm_scheduler.o

driver.o: driver.c
	gcc -c -o driver.o driver.c

fsm.o: fsm.c 
	gcc -c -o fsm.o fsm.c 

ring_buffer_fsm.o: ring_buffer_fsm.c
	gcc -c -o ring_buffer_fsm.o ring_buffer_fsm.c

fsm_scheduler_data.o: fsm_scheduler_data.c
	gcc -c -o fsm_scheduler_data.o fsm_scheduler_data.c

fsm_scheduler.o: fsm_scheduler.c
	gcc -c -o fsm_scheduler.o fsm_scheduler.c

clean:
	rm -rf *.o prog