all: prog

prog: HomeworkTemperature.o Sensor_Temperature.o DYNAMIC_ARRAY.o
	gcc -o prog HomeworkTemperature.o Sensor_Temperature.o  DYNAMIC_ARRAY.o

HomeworkTemperature.o: HomeworkTemperature.c
	gcc -c -o HomeworkTemperature.o HomeworkTemperature.c

Sensor_Temperature.o: Sensor_Temperature.c
	gcc -c -o Sensor_Temperature.o Sensor_Temperature.c

DYNAMIC_ARRAY.o: DYNAMIC_ARRAY.c Sensor_Temperature.h
	gcc -c -o DYNAMIC_ARRAY.o DYNAMIC_ARRAY.c

clean:
	rm -rf *.o prog