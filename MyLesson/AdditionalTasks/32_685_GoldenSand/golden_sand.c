#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\32_685_GoldenSand\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\32_685_GoldenSand\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define ZEROING     0
#define SIZE        3

static void openFile(FILE **pf, char *fileName, char *mode);
static int getMax(int arr[], int size);
static bool fillArray(FILE *pf, int arr[], int size);
static int bestResult(int arr[], int arr1[], int size);

int main(void)
{
    FILE *pf_source, *pf_target;
    int arr[SIZE] = {0};
    int arr1[SIZE] = {0};

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    // fscanf(pf_source, "%lld %lld %lld", &a, &b, &c);
    fillArray(pf_source, arr, SIZE);
    fillArray(pf_source, arr1, SIZE);
    
    fprintf(pf_target, "%d", bestResult(arr, arr1, SIZE));

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

static int getMax(int arr[], int size)
{
    int max = ZEROING, max_index = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
            max_index = i;
        }
    }

    arr[max_index] = ZEROING;
    
    return max;
}

static bool fillArray(FILE *pf, int arr[], int size)
{
    if (size <= 0)
        return false;

    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d", &arr[i]);
    
    return true;
}

static int bestResult(int arr[], int arr1[], int size)
{
    int res = 0;

    for (size_t i = 0; i < SIZE; i++)
        res += getMax(arr, SIZE) * getMax(arr1, SIZE);

    return res;
}