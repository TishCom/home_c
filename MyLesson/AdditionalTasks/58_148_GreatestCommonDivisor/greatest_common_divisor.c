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
static int get_greatest_common_divisor(int number1, int number2);

int main(void)
{
    FILE *pf_source, *pf_target;
    char ch = 0;
    int number1 = 0, number2 = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d", &number1, &number2);

    fprintf(pf_target, "%d", get_greatest_common_divisor(number1, number2));

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

static int get_greatest_common_divisor(int number1, int number2)
{
    while (number1 != 0 && number2 != 0)
    {
        if (number1 > number2)
            number1 %= number2;
        else
            number2 %= number1;
    }
    
    return number1 + number2;
}