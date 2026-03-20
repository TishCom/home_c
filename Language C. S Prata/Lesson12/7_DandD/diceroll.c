#include "diceroll.h"

int roll_count = 0;

int rollem(int sides)
{
    int roll;

    roll = rand() % sides + 1;
    ++roll_count;

    return roll;
}

int roll_n_dice(int dice, int sides)
{
    int total = 0;

    if (sides < 2)
    {
        printf("At least 2 faces are required..\n");
        return -2;
    }
    if (dice < 1)
    {
        printf("At least 1 bone is required..\n");
        return -1;
    }
    
    for (int d = 0; d < dice; d++)
        total += rollem(sides);
    
    return total;
}

void skip_string(void)
{
    while (getchar() != '\n')
        continue;
}