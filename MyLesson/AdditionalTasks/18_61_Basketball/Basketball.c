#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\18_61_Basketball\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\18_61_Basketball\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int score_a = 0, score_b = 0, result = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    for (size_t i = 0; i < 4; i++)
    {
        fscanf(pf_source, "%d %d", &score_a, &score_b);
        result += score_a - score_b;
    }

    if (result > 0)
        fprintf(pf_target, "%d", 1);
    else if (result < 0)
        fprintf(pf_target, "%d", 2);
    else
        fprintf(pf_target, "DRAW");

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