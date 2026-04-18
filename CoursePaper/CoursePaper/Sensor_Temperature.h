#ifndef SENSOR_TEMPERATURE_H
#define SENSOR_TEMPERATURE_H

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "Sencsor_Readings.h"
#include "DYNAMIC_ARRAY.h"

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
#define MY_ERROR        -1

float averageMonthlyTemperature(dynamicArr *da, uint8_t month);
int minimumMonthlyTemperature(dynamicArr *da, uint8_t month);
int maximumMonthlyTemperature(dynamicArr *da, uint8_t month);
float averageYearTemperature(dynamicArr *da);
int minimumYearTemperature(dynamicArr *da);
int maximumYearTemperature(dynamicArr *da);
int addingData(dynamicArr *da, datatypeDA data);
int deleteData(int tergetDelete, dynamicArr *da);
int fillArrSensor(dynamicArr *da); 
void printArrSensor(dynamicArr *da);
void sortDate(dynamicArr *da);
void sortTemperature(dynamicArr *da);

#endif