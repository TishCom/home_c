#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\56_62_Cells\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\56_62_Cells\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0;
    char ch = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%c%d", &ch, &number);

    if (((ch -'A') % 2) != (number % 2))
        fprintf(pf_target, "BLACK");
    else
        fprintf(pf_target, "WHITE");

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