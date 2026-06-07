#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\83_952_OnBus\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\83_952_OnBus\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int adult = 0, children = 0, min = 0, max = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d", &adult, &children);

    if (adult == 0 && children > 0)
    {
        fprintf(pf_target, "Impossible");
    }
    else
    {
        min = adult >= children ? adult : children;
        max = children == 0 ? adult : adult + children - 1;

        fprintf(pf_target, "%d %d", min, max);
    }
    
    fclose(pf_source);
    fclose(pf_target);
}

static void open_file(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}