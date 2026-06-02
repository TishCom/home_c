#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\62_5_Statistics\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\62_5_Statistics\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE     100

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, int arr[], int size);
static void sort_even(FILE *pf, int arr[], int size);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = 0;
    int days[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);
    fill_array(pf_source, days, size);

    sort_even(pf_target, days, size);

    // fprintf(pf_target, "%d ", size + 8);

    fclose(pf_source);
    fclose(pf_target);
}

static void open_file(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

static void fill_array(FILE *pf, int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d", &arr[i]);
}

static void sort_even(FILE *pf, int arr[], int size)
{
    int become = 0; 

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 != 0)
        {
            fprintf(pf, "%d ", arr[i]);
            become--;
        }
    }
    fprintf(pf, "\n");

    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] % 2 == 0)
        {
            fprintf(pf, "%d ", arr[i]);
            become++;
        }
    }
    fprintf(pf, "\n");

    if (become < 0)
        fprintf(pf, "NO");
    else
        fprintf(pf, "YES");
}