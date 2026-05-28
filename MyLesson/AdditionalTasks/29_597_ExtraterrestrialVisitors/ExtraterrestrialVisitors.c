#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "C:\\MFTI\\MyLesson\\AdditionalTasks\\29_597_ExtraterrestrialVisitors\\input.txt"
// #define OUTPUT_FILE "C:\\MFTI\\MyLesson\\AdditionalTasks\\29_597_ExtraterrestrialVisitors\\output.txt"

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\29_597_ExtraterrestrialVisitors\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\29_597_ExtraterrestrialVisitors\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

#define MIN_MASS    94
#define MAX_MASS    727

static void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    long radius1 = 0, radius2 = 0, radius3 = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%ld %ld %ld", &radius1, &radius2, &radius3);

    if ((radius2 + radius3) <= radius1)
        fprintf(pf_target, "YES");
    else
        fprintf(pf_target, "NO");

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