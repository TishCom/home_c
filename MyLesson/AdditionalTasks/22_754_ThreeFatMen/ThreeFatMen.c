#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\22_754_ThreeFatMen\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\22_754_ThreeFatMen\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define MIN_MASS    94
#define MAX_MASS    727

void openFile(FILE **pf, char *fileName, char *mode);
static void maxNumber(int *max_number, int numberA, int numberB);
static bool maxNumber3(int *max_number, int numberA, int numberB, int numberC);
static bool isCorrect(int numberA, int numberB, int numberC);

int main(void)
{
    FILE *pf_source, *pf_target;
    int mass1 = 0, mass2 = 0, mass3 = 0, max_mass = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d", &mass1, &mass2, &mass3);

    if (maxNumber3(&max_mass, mass1, mass2, mass3))
        fprintf(pf_target, "%d", max_mass);
    else
        fprintf(pf_target, "Error");

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

static void maxNumber(int *max_number, int numberA, int numberB)
{
    *max_number = numberA > numberB ? numberA : numberB;
}

static bool maxNumber3(int *max_number, int numberA, int numberB, int numberC)
{
    bool ret = isCorrect(numberA, numberB, numberC);

    if (ret)
    {
        maxNumber(max_number, numberA, numberB);
        *max_number = *max_number > numberC ? *max_number : numberC;
        return true;
    }
    
    return false;
}

static bool isCorrect(int numberA, int numberB, int numberC)
{
    if (numberA < MIN_MASS || numberA > MAX_MASS)
        return false;
    if (numberB < MIN_MASS || numberB > MAX_MASS)
        return false;
    if (numberC < MIN_MASS || numberC > MAX_MASS)
        return false;

    return true;
}