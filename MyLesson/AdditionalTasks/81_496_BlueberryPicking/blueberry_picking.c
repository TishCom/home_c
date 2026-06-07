#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\81_496_BlueberryPicking\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\81_496_BlueberryPicking\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 1000

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, int size, int number[]);
static int get_max_berry(int size, int number[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = 0;
    int number[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);
    fill_array(pf_source, size, number);

    fprintf(pf_target, "%d", get_max_berry(size, number));
    
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

static void fill_array(FILE *pf, int size, int number[])
{
    for (size_t i = 0; i < size; i++)
        fscanf(pf, "%d", &number[i]);
}

static int get_max_berry(int size, int number[])
{
    int max_berry = 0, current_berry = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (i % (size - 1) == 0)
            current_berry = number[0] + number[i == 0 ? 1 : size - 2] + number[size - 1];
        else
            current_berry = number[i - 1] + number[i] + number[i + 1];

        if (max_berry < current_berry)
            max_berry = current_berry;
    }

    return max_berry;
}