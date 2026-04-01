all: prog

prog: HomeworkTemperature.o Sensor_Temperature.o
	gcc -o prog HomeworkTemperature.o Sensor_Temperature.o

main.o: HomeworkTemperature.c Sensor_Temperature.h
	gcc -c -o HomeworkTemperature.o HomeworkTemperature.c

func.o: Sensor_Temperature.c
	gcc -c -o Sensor_Temperature.o Sensor_Temperature.c

clean:
	rm -rf *.o prog