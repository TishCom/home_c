#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\36_697_Repair\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\36_697_Repair\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define AREA_PER_JAR    16
#define AREA_PARALELEPIPED(X, Y, Z) (2 * ((X) * (Y) + (X) * (Z) + (Y) * (Z)))

static void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int length = 0, height = 0, width = 0, result = 0, area = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d", &length, &width, &height);

    area = 2 * height * (length + width);
    result = area / AREA_PER_JAR;
    if (area % AREA_PER_JAR)
        result++;

    fprintf(pf_target, "%d", result);

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