#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\27_970_PermutationChangesSomething\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\27_970_PermutationChangesSomething\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define MIN_MASS    94
#define MAX_MASS    727

static void openFile(FILE **pf, char *fileName, char *mode);
static long absolut(long number);
static bool isCorrect(long numberA, long numberB, long numberC);

int main(void)
{
    FILE *pf_source, *pf_target;
    long numberA = 0, numberB = 0, numberC = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%ld %ld %ld", &numberA, &numberB, &numberC);

    if (isCorrect(numberA, numberB, numberC))
        fprintf(pf_target, "YES");
    else
        fprintf(pf_target, "NO");

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

static bool isCorrect(long numberA, long numberB, long numberC)
{
    // if (absolut(absolut(numberA) - absolut(numberB)) == absolut(numberC)
    //     || absolut(absolut(numberA) + absolut(numberB)) == absolut(numberC))
    //     return true;
    if (absolut(numberA - numberB) == absolut(numberC)
        || absolut(numberA + numberB) == absolut(numberC))
        return true;

    return false;
}

static long absolut(long number)
{
    return number >= 0 ? number : -number;
}