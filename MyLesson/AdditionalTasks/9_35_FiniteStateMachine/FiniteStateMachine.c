#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #define INPUT_FILE   "F:\\C_2026_MFTI\\AdditionalTasks\\9_35_FiniteStateMachine\\input.txt"
// #define OUTPUT_FILE  "F:\\C_2026_MFTI\\AdditionalTasks\\9_35_FiniteStateMachine\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE   100

void fopen1(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int numberK = 0, numberN = 0,numberM = 0;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d", &numberK);
    for (size_t i = 0; i < numberK; i++)
    {
        fscanf(pf_source, "%d", &numberN);
        fscanf(pf_source, "%d", &numberM);
        fprintf(pf_target, "%d\n", (19 * numberM) + (numberN + 239) * (numberN + 366) / 2);
    }

    fclose(pf_source);
    fclose(pf_target);
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}