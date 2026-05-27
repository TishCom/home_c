#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\19_755_StrawberryPicking\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\19_755_StrawberryPicking\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int collected_masha = 0, collected_misha = 0, eaten = 0, result = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d", &collected_masha, &collected_misha, &eaten);
    result = collected_masha + collected_misha - eaten;

    if (result >= 0)
        fprintf(pf_target, "%d", result);
    else
        fprintf(pf_target, "Impossible");

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