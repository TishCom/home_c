#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\23_692_BinaryNumbers\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\23_692_BinaryNumbers\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define MIN_MASS    94
#define MAX_MASS    727

void openFile(FILE **pf, char *fileName, char *mode);
static bool isBinaryNumber(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0;;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number);

    if (isBinaryNumber(number))
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

static bool isBinaryNumber(int number)
{
    for (size_t i = 1; i < 1 << 16; i <<= 1)
    {
        if (number == i)
            return true;
    }
    
    return false;
}