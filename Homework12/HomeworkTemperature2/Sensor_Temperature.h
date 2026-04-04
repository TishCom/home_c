#ifndef SENSOR_YEMPERATURE_H
#define SENSOR_YEMPERATURE_H

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
}sensor_readings;

enum MONTH
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

#define PRIMARY_MINIMUM 300
#define PRIMARY_MAXIMUM -300
#define ERROR           -1

float averageMonthlyTemperature(int size, sensor_readings info[], uint8_t month);
int minimumMonthlyTemperature(int size, sensor_readings info[], uint8_t month);
int maximumMonthlyTemperature(int size, sensor_readings info[], uint8_t month);
float averageYearTemperature(int size, sensor_readings info[]);
int minimumYearTemperature(int size, sensor_readings info[]);
int maximumYearTemperature(int size, sensor_readings info[]);
int addingData(int size, int amountAvailableData, sensor_readings info[], sensor_readings data);
int deleteData(int size, int amountAvailableData, sensor_readings info[]);
int fillArrSensor(int size, sensor_readings info[]);
void printArrSensor(int amountAvailableData, sensor_readings info[]);
void sortDate(int size, sensor_readings info[]);
void sortTemperature(int size, sensor_readings info[]);

#endif