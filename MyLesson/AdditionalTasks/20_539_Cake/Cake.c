#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\20_539_Cake\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\20_539_Cake\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_guests = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number_guests);

    if (number_guests == 1)
        fprintf(pf_target, "%d", 0);
    else if (number_guests % 2 == 0)
        fprintf(pf_target, "%d", number_guests / 2);
    else
        fprintf(pf_target, "%d", number_guests);

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