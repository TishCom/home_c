#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\41_933_Telephone\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\41_933_Telephone\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int telephonePayment(int number_minute, int max_minute, int pay1, int pay2);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_minute = 0, max_minute = 0, pay1 = 0, pay2 = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %d %d", &max_minute, &pay1, &pay2, &number_minute);

    fprintf(pf_target, "%d", telephonePayment(number_minute, max_minute, pay1, pay2));

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