#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\90_850_Herons\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\90_850_Herons\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static long long get_min(long long number1, long long number2);
static long long get_max(long long number1, long long number2);

int main(void)
{
    FILE *pf_source, *pf_target;
    long long number1 = 0, number2 = 0, min = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%lld %lld", &number1, &number2);

    min = get_max(number1, number2);
    min = min / 2 + min % 2;

    fprintf(pf_target, "%lld %lld", min, get_min(number1, number2));
    
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

static long long get_min(long long number1, long long number2)
{
    return number1 > number2 ? number2 : number1;
}

static long long get_max(long long number1, long long number2)
{
    return number1 > number2 ? number1 : number2;
}