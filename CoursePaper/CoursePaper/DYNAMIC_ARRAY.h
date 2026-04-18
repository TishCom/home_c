#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Sencsor_Readings.h"

typedef sensor_readings datatypeDA;

typedef struct
{
    datatypeDA *item;
    int size;
    int sp;
} dynamicArr;

void initDynamicArr(dynamicArr *da);
void deleteDynamicArr(dynamicArr *da);
void pushDynamicArr(dynamicArr *da, datatypeDA value);
datatypeDA popDynamicArr(dynamicArr *da);
bool emptyDynamicArr(dynamicArr *da);

#endif