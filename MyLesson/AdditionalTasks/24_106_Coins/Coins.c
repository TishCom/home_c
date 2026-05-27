#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\24_106_Coins\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\24_106_Coins\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define MIN_MASS    94
#define MAX_MASS    727

void openFile(FILE **pf, char *fileName, char *mode);
static int min(int numberA, int numberB);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_coin = 0, number_eagle = 0, number_tails = 0, coin = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number_coin);
    for (size_t i = 0; i < number_coin; i++)
    {
        fscanf(pf_source, "%d", &coin);

        if (coin == 0)
            number_eagle++;
        else
            number_tails++;
    }
    
    fprintf(pf_target, "%d", min(number_eagle, number_tails));

    fclose(pf_source);
    fclose(pf_target);
}

void openFile(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

static int min(int numberA, int numberB)
{
    return numberA < numberB ? numberA : numberB;
}