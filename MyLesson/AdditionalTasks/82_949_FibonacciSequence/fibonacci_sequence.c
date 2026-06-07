#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\82_949_FibonacciSequence\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\82_949_FibonacciSequence\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static bool get_numbers(int n, long long numberN, long long numberN1, long long *num1, long long *num2);

int main(void)
{
    FILE *pf_source, *pf_target;
    int n = 0;
    long long numberN = 0, numberN1 = 0;
    long long number1 = 0, number2 = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %lld %lld", &n, &numberN, &numberN1);
    get_numbers(n, numberN, numberN1, &number1, &number2);

    fprintf(pf_target, "%lld %lld", number1, number2);
    
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

static bool get_numbers(int n, long long numberN, long long numberN1, long long *num1, long long *num2)
{
    long long previous = 0;

    if (n == 1)
    {
        *num2 = numberN1;
        *num1 = numberN;
        return true;
    }
    else if (n == 2)
    {
        *num2 = numberN;
        *num1 = numberN1- numberN;
        return true;
    }

    for (size_t i = n; i >= 3; i--)
    {
        previous = numberN1 - numberN;
        numberN1 = numberN;
        numberN = previous;
    }

    *num2 = previous;
    *num1 = numberN1 - *num2;
    
    return true;
}