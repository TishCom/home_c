#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\57_678_Thimbles\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\57_678_Thimbles\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE            3

typedef struct 
{
    int x;
    int y;
} Point;

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, Point arr[], int size);
static float get_area_triangle(Point arr[], int size);

int main(void)
{
    FILE *pf_source, *pf_target;
    Point arr[SIZE];
    double result = 0, cela = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    // fscanf(pf, "%d %d", &arr[i].x, &arr[i].y);
    fill_array(pf_source, arr, SIZE);

    result = get_area_triangle(arr, SIZE);

    if ((modf(result, &cela)) <= 0)
        fprintf(pf_target, "%d", (int)cela);
    else
        fprintf(pf_target, "%f", result);

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

static void fill_array(FILE *pf, Point arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d %d", &arr[i].x, &arr[i].y);
}

static float get_area_triangle(Point arr[], int size)
{
    return -(((arr[1].x - arr[0].x) * (arr[2].y - arr[0].y)
                - (arr[2].x - arr[0].x) * (arr[1].y - arr[0].y)) / 2.0);
}