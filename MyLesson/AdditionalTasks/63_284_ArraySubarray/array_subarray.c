#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\63_284_ArraySubarray\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\63_284_ArraySubarray\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE     1000

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, long long arr[], int size);
static void print_subarray(FILE *pf_in, FILE *pf_out, long long arr[], int size, int size_sub);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = 0, size_sub = 0;
    long long arr[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);
    fill_array(pf_source, arr, size);
    fscanf(pf_source, "%d", &size_sub);
    print_subarray(pf_source, pf_target, arr, size, size_sub);

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

static void fill_array(FILE *pf, long long arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%lld", &arr[i]);
}

static void print_subarray(FILE *pf_in, FILE *pf_out, long long arr[], int size, int size_sub)
{
    long long min = 0, max = 0;

    for (size_t i = 0; i < size_sub; i++)
    {
        fscanf(pf_in, "%lld %lld", &min, &max);

        for (size_t y = 0; y < size; y++)
        {
            if (y >= (min - 1) && y <= (max - 1))
                fprintf(pf_out, "%lld ", arr[y]);
        }

        fprintf(pf_out, "\n", size + 8);
    }
}