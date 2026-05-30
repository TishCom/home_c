#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\46_233_BusTour\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\46_233_BusTour\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define HIGHT_BUS     437

static void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_bridge = 0, hright_bridge = 0, number_bridg_crash = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number_bridge);

    for (size_t i = 1; i <= number_bridge; i++)
    {
        fscanf(pf_source, "%d", &hright_bridge);

        if (hright_bridge <= HIGHT_BUS)
        {
            number_bridg_crash = i;
            break;
        }
    }
    
    if (number_bridg_crash)
        fprintf(pf_target, "Crash %d", number_bridg_crash);
    else
        fprintf(pf_target, "No crash");
    
    fclose(pf_source);
    fclose(pf_target);
}

static void openFile(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}