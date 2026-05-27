#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\13_25_MoreLess\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\13_25_MoreLess\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    long number_a = 0, number_b = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d", &number_a, &number_b);

    if (number_a < number_b)
        fprintf(pf_target, "<");
    else if (number_a > number_b)
        fprintf(pf_target, ">");
    else
        fprintf(pf_target, "=");

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