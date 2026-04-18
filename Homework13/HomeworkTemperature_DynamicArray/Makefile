CFLAGS = -O0 -g -fno-omit-frame-pointer -Wall -Wextra -Wformat -Wformat-security -Wconversion -Wsign-conversion

all: prog

prog: HomeworkTemperature.o Sensor_Temperature.o DYNAMIC_ARRAY.o
	gcc $(CFLAGS) -o prog HomeworkTemperature.o Sensor_Temperature.o  DYNAMIC_ARRAY.o

HomeworkTemperature.o: HomeworkTemperature.c Sensor_Temperature.h DYNAMIC_ARRAY.h
	gcc $(CFLAGS) -c -o HomeworkTemperature.o HomeworkTemperature.c

Sensor_Temperature.o: Sensor_Temperature.c Sensor_Temperature.h DYNAMIC_ARRAY.h
	gcc $(CFLAGS) -c -o Sensor_Temperature.o Sensor_Temperature.c

DYNAMIC_ARRAY.o: DYNAMIC_ARRAY.c Sensor_Temperature.h DYNAMIC_ARRAY.h
	gcc $(CFLAGS) -c -o DYNAMIC_ARRAY.o DYNAMIC_ARRAY.c

clean:
	rm -rf *.o prog