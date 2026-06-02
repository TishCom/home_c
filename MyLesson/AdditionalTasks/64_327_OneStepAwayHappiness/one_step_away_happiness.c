#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\64_327_OneStepAwayHappiness\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\64_327_OneStepAwayHappiness\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static bool previous_or_next_is_lucky(int number);
static int sum_digits(int number);
static bool is_lucky(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int size = 0, number = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &size);

    for (size_t i = 0; i < size; i++)
    {
        fscanf(pf_source, "%d", &number);

        if (previous_or_next_is_lucky(number))
            fprintf(pf_target, "Yes\n");
        else 
            fprintf(pf_target, "No\n");
    }

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

static bool previous_or_next_is_lucky(int number)
{
    return is_lucky(number - 1) || is_lucky(number + 1);
}

static bool is_lucky(int number)
{
    return sum_digits(number / 1000) == sum_digits(number % 1000);
}

static int sum_digits(int number)
{
    int sum = 0;

    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    
    return sum;
}