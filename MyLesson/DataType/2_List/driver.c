#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\28_149_Revers\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\28_149_Revers\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define MIN_MASS    94
#define MAX_MASS    727

static void openFile(FILE **pf, char *fileName, char *mode);
static bool printArray(FILE *pf, int arr[], int size);
static bool fillArray(FILE *pf, int arr[], int size);

int main(void)
{
    FILE *pf_source, *pf_target;
    long numberA = 0, numberB = 0, numberC = 0;
    int size = 0;
    int arr[1000] = {0};

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);

    fillArray(pf_source, arr, size);
    printArray(pf_target, arr, size);

    // fprintf(pf_target, "NO");

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

static bool fillArray(FILE *pf, int arr[], int size)
{
    if (size <= 0)
        return false;

    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d", &arr[i]);
    
    return true;
}

static bool printArray(FILE *pf, int arr[], int size)
{
    if (size <= 0)
        return false;

    for (size_t i = size; i > 0; i--)
        fprintf(pf, "%d ", arr[i - 1]);
    
    return true;
}