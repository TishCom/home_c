#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #define INPUT_FILE   "F:\\C_2026_MFTI\\AdditionalTasks\\8_8_Arithmetic\\input.txt"
// #define OUTPUT_FILE  "F:\\C_2026_MFTI\\AdditionalTasks\\8_8_Arithmetic\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE   100

void fopen1(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int numberA = 0, numberB = 0,numberC = 0;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d", &numberA);
    fscanf(pf_source, "%d", &numberB);
    fscanf(pf_source, "%d", &numberC);

    if (numberA * numberB == numberC)
        fprintf(pf_target, "%s", "YES");
    else
        fprintf(pf_target, "%s", "NO");

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