#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\16_21_Salary\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\16_21_Salary\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);
int min(int number1, int number2);
int max(int number1, int number2);
int min3(int number1, int number2, int number3);
int max3(int number1, int number2, int number3);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number1 = 0, number2 = 0, number3 = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d", &number1, &number2, &number3);
    fprintf(pf_target, "%d",
            max3(number1, number2, number3) -
            min3(number1, number2, number3));

    fclose(pf_source);
    fclose(pf_target);
}

void openFile(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

int max3(int number1, int number2, int number3)
{
    return max(max(number1, number2), number3);
}

int min3(int number1, int number2, int number3)
{
    return min(min(number1, number2), number3);
}

int max(int number1, int number2)
{
    return number1 > number2 ? number1 : number2;
}

int min(int number1, int number2)
{
    return number1 < number2 ? number1 : number2;
}