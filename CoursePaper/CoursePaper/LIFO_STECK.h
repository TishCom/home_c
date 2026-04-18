#ifndef LIFO_STECK_H
#define LIFO_STECK_H

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Sensor_Temperature.h"

//typedef sensor_readings datatypeStack;
typedef int datatypeStack;

typedef struct list 
{
    datatypeStack value;
    struct list * next;
}stack;

void pushStack(stack **p, datatypeStack data);
bool emptyStack(stack *p);
datatypeStack popStack(stack **p);

#endif