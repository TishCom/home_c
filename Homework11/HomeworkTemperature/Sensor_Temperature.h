#ifndef SENSOR_YEMPERATURE_H
#define SENSOR_YEMPERATURE_H

#include <stdio.h>
#include <inttypes.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
}sensor_readings;

int averageMonthlyTemperature(sensor_readings info[], uint8_t month);
int minimumMonthlyTemperature(sensor_readings info[], uint8_t month);
int maximumMonthlyTemperature(sensor_readings info[], uint8_t month);
int averageYearTemperature(sensor_readings info[], uint16_t year);
int minimumYearTemperature(sensor_readings info[], uint16_t year);
int maximumYearTemperature(sensor_readings info[], uint16_t year);

#endif