#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\42_606_Triangle\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\42_606_Triangle\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int telephonePayment(int number_minute, int max_minute, int pay1, int pay2);

int main(void)
{
    FILE *pf_source, *pf_target;
    int lengthA = 0, lengthB = 0, lengthC = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d", &lengthA, &lengthB, &lengthC);

    if (lengthA + lengthB > lengthC
        && lengthA + lengthC > lengthB
        && lengthB + lengthC > lengthA)
        fprintf(pf_target, "YES");
    else
        fprintf(pf_target, "NO");
    
    fclose(pf_source);
    fclose(pf_target);
}

static void openFile(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

static int telephonePayment(int number_minute, int max_minute, int pay1, int pay2)
{
    int payment = 0;

    if (number_minute > max_minute)
        payment = max_minute * pay1 + (number_minute - max_minute) * pay2;
    else
        payment = number_minute * pay1;
    
    return payment;
}