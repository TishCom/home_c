#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\57_678_Thimbles\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\57_678_Thimbles\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = 0, age = 0, sex = 0;
    int max_age = 0, index_max_age = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);

    for (size_t i = 0; i < size; i++)
    {
        fscanf(pf_source, "%d %d", &age, &sex);

        if (sex == 1 && max_age < age)
        {
            max_age = age;
            index_max_age = i + 1;
        }
    }

    if (index_max_age == 0)
        index_max_age = -1;

    fprintf(pf_target, "%d", index_max_age);

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