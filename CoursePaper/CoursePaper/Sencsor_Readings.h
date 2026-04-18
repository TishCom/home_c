#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

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

#endif