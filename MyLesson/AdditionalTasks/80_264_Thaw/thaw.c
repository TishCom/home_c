#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\80_264_Thaw\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\80_264_Thaw\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, int size, int number[]);
static int get_max_days_thaw(int size, int number[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = 0;
    int number[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);
    fill_array(pf_source, size, number);

    fprintf(pf_target, "%d", get_max_days_thaw(size, number));
    
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

static int get_max_days_thaw(int size, int number[])
{
    int max_days_thaw = 0, current_days_thaw = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (number[i] > 0)
        {
            current_days_thaw++;
        }
        else 
        {
            if (current_days_thaw > max_days_thaw)
                max_days_thaw = current_days_thaw;
            current_days_thaw = 0;
        }
    }

    return max_days_thaw > current_days_thaw ? max_days_thaw : current_days_thaw;
}