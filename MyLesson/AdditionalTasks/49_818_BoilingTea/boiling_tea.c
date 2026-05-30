#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\49_818_BoilingTea\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\49_818_BoilingTea\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int sumArray(int arr[], int size);
static void fillArray(FILE *pf, int arr[], int size);
static void createArray(int **arr, int size);
static void deleteArray(int **arr);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = {0};
    int *arr = NULL;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);

    createArray(&arr, size);
    fillArray(pf_source, arr, size);
    
    fprintf(pf_target, "%d", sumArray(arr, size) + 1 - size);

    deleteArray(&arr);
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

static void deleteArray(int **arr)
{
    free(*arr);
}

static void createArray(int **arr, int size)
{
    *arr = (int*)malloc(size * sizeof(int));
}

static void fillArray(FILE *pf, int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d", &arr[i]);
}

static int sumArray(int arr[], int size)
{
    int sum = 0;

    for (size_t i = 0; i < size; i++)
        sum += arr[i];
    
    return sum;
}