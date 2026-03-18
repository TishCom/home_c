#include "pe12-2a.h"

static int variableMode = 0;
static float variableFuel = 0;
static float variableDistance = 0;

void get_info(void)
{
    printf("How much gas did you spend?\n");
    scanf("%f", &variableFuel);
    getchar();
    printf("How far have you traveled?\n");
    scanf("%f", &variableDistance);
    getchar();
}

void show_info(void)
{
    if (variableMode == 1)
    {
        printf("Your enter is imperial.\n");
        printf("Your expense: %.2f miles per 1 gallon.\n", variableDistance / variableFuel);
    }
    else if (variableMode == 0)
    {
        printf("Your enter is metric.\n");
        printf("Your expense: %.2f liter per 100 km.\n", (variableFuel / variableDistance) * 100);
    }
}

void set_mode(int mode)
{
    if (mode == 0)
        variableMode = 0;
    else if (mode == 1)
        variableMode = 1;
    else    
        printf("Your enter is truble.\n");
}
