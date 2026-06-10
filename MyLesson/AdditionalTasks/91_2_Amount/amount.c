#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\91_2_Amount\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\91_2_Amount\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static long long factorial(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d", &number);

    fprintf(pf_target, "%lld", factorial(number));
    
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

static long long factorial(int number)
{
    long long fact = 1;

    if (number > 0)
    {
        for (int i = 2; i <= number; i++)
            fact += i;
    }
    else if (number < 0)
    {
        for (int i = number; i < 0; i++)
            fact += i;
    }
    
    return fact;
}