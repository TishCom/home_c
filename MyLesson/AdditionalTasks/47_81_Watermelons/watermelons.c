#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\47_81_Watermelons\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\47_81_Watermelons\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int minArr(int arr[], int size);
static int maxArr(int arr[], int size);
static void fillArr(FILE *pf, int arr[], int size);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_watermelons = 0;
    int *arr = NULL;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number_watermelons);

    arr = (int*)malloc(number_watermelons * sizeof(int));
    fillArr(pf_source, arr, number_watermelons);
    
    fprintf(pf_target, "%d %d", minArr(arr, number_watermelons), maxArr(arr, number_watermelons));
    
    free(arr);
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

static void fillArr(FILE *pf, int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d", &arr[i]);
}

static int minArr(int arr[], int size)
{
    int min_number = arr[0];

    for (size_t i = 1; i < size; i++)
    {
        if (min_number > arr[i])
            min_number = arr[i];
    }
    
    return min_number;
}

static int maxArr(int arr[], int size)
{
    int max_number = arr[0];

    for (size_t i = 1; i < size; i++)
    {
        if (max_number < arr[i])
            max_number = arr[i];
    }
    
    return max_number;
}