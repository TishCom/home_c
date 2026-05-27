#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE \
    "F:\\C_2026_MFTI\\AdditionalTasks\\10_23_FortuneTelling\\input.txt"
#define OUTPUT_FILE \
    "F:\\C_2026_MFTI\\AdditionalTasks\\10_23_FortuneTelling\\output.txt"
// #define INPUT_FILE      "input.txt"
// #define OUTPUT_FILE     "output.txt"
#define SIZE 100

void fopen1(FILE **pf, char *fileName, char *mode);
int sum_natural_divisors(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0;
    int NUMberFGER;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number);
    number = sum_natural_divisors(number);
    fprintf(pf_target, "%d", number);

    fclose(pf_source);
    fclose(pf_target);
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

int sum_natural_divisors(int number)
{
    int sum = 0;

    for (size_t i = 1; i <= number; i++)
    {
        if (number % i == 0)
            sum += i;
    }

    return sum;
}