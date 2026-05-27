#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\14_766_Nuts\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\14_766_Nuts\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    long number_n = 0, number_m = 0, number_k = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d", &number_n, &number_m, &number_k);

    if (number_k <= number_n * number_m)
        fprintf(pf_target, "YES");
    else
        fprintf(pf_target, "NO");

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