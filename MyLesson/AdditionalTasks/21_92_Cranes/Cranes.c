#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\21_92_Cranes\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\21_92_Cranes\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_cranes = 0, number_cranes_K = 0, number_cranes_PS = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number_cranes);

    number_cranes_K = (number_cranes * 2) / 3;
    number_cranes_PS = (number_cranes - number_cranes_K) / 2;

    fprintf(pf_target, "%d %d %d", number_cranes_PS, number_cranes_K, number_cranes_PS);

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