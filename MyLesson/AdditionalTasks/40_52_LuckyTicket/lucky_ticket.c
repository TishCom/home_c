#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\40_52_LuckyTicket\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\40_52_LuckyTicket\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static bool isLuckyTicket(int number_ticket);
static int sumDigit(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_ticket = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &number_ticket);

    fprintf(pf_target, "%s", isLuckyTicket(number_ticket) ? "YES" : "NO");

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

static bool isLuckyTicket(int number_ticket)
{
    return sumDigit(number_ticket / 1000) == sumDigit(number_ticket % 1000);
}

static int sumDigit(int number)
{
    int sum = 0;

    while (number > 0)
    {
        sum += number % 10;
        number /= 10;
    }
    
    return sum;
}