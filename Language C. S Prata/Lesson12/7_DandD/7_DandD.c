#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "diceroll.h"

int main(int argc, char **argv)
{
    srand(time(NULL));

    int dice, sides, status, throws;

    printf("Enter the number of throws or q to complete.\n");
    while (scanf("%d", &throws) == 1 && throws > 0)
    {
        printf("How many faces and how many bones? ");
        if ((status = scanf("%d%d", &sides, &dice)) != 2)
        {
            if (status == EOF)
                break;
            else
            {
                printf("You must enter a whole number. Let's start over.\n");
                skip_string();
                printf("Enter the number of throws or q to complete.\n");
                continue;
            }
        }

        printf("We have %d throws of %d dice with %d faces.\n", throws, dice, sides);
        for (int i = 0; i < throws; i++)
            printf("%d ",  roll_n_dice(dice, sides));
        
        printf("\nEnter the number of throws or q to complete.\n");
    }

    printf("May luck always be with you.\n");
    
	return 0;
}