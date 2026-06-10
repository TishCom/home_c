#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\88_14_SmallestCommonMultiple\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\88_14_SmallestCommonMultiple\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static long long get_smallest_common_multiple(int number1, int number2);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number1 = 0, number2 = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d %d", &number1, &number2);

    fprintf(pf_target, "%lld", get_smallest_common_multiple(number1, number2));
    
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

static long long get_smallest_common_multiple(int number1, int number2)
{
    long long res = 0;

    for (int i = 1; ; i++)
    {
        res = number1 * i;

        if (res % number2 == 0)
            break;
    }

    return res;
}