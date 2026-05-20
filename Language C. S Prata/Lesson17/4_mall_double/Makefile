all: prog

prog: queue.o mall.o
	gcc -o prog queue.o mall.o

mall.o: mall.c
	gcc -c -o mall.o mall.c

queue.o: queue.c
	gcc -c -o queue.o queue.c

clean:
	rm -rf *.o prog