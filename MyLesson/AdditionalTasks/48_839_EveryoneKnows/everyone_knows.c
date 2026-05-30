#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\48_839_EveryoneKnows\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\48_839_EveryoneKnows\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE     10000

static void openFile(FILE **pf, char *fileName, char *mode);
static bool isEveryoneKnows(char number[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    char arr[SIZE] = {0};

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%s", arr);
    
    fprintf(pf_target, "%s", isEveryoneKnows(arr) ? "YES" : "NO");

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

static bool isEveryoneKnows(char number[])
{
    int size = strlen(number);

    for (size_t i = 0; i < size; i++)
    {
        if (number[i] == '0')
            return false;
    }
    
    return true;
}