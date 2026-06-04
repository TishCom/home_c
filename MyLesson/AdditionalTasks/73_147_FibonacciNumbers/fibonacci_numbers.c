#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\73_147_FibonacciNumbers\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\73_147_FibonacciNumbers\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static long long get_fibonacci_number(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0;;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number);

    fprintf(pf_target, "%lld",  get_fibonacci_number(number));
    
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

static long long get_fibonacci_number(int number)
{
    if (number == 0)
        return 0;
    else if (number <= 2)
        return 1;

    long long previous = 1, current = 1, temp = 0;

    for (size_t i = 0; i < number - 2; i++)
    {
        temp = current;
        current += previous;
        previous = temp;
    }
    
    return current;
}