#include "pe12-2a.h"

void get_info(float *fuel, float *distance)
{
    printf("How much gas did you spend?\n");
    scanf("%f", fuel);
    printf("How far have you traveled?\n");
    scanf("%f", distance);
}

void show_info(float fuel, float distance, int mode)
{
    if (mode == 1)
    {
        printf("Your enter is imperial.\n");
        printf("Your expense: %.2f miles per 1 gallon.\n", distance / fuel);
    }
    else if (mode == 0)
    {
        printf("Your enter is metric.\n");
        printf("Your expense: %.2f liter per 100 km.\n", (fuel / distance) * 100);
    }
}

void set_mode(int *mode, int previuos)
{
    if (*mode != 0 && *mode != 1) 
    {
        printf("Your enter is truble.\n");
        *mode = previuos;
    }  
}