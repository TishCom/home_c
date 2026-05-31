#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\53_1681_HelloWorld\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\53_1681_HelloWorld\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int maxGapNumber(int horizontal, int vertical);

int main(void)
{
    FILE *pf_source, *pf_target;
    int horizontal = 0, vertical = 0;

    // openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    // fscanf(pf_source, "%d %d", &horizontal, &vertical);
    
    fprintf(pf_target, "Hello world!");

    // fclose(pf_source);
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