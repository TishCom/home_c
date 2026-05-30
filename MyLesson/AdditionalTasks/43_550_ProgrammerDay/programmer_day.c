#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\43_550_ProgrammerDay\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\43_550_ProgrammerDay\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define PROGRAMMER_DAY_NUMBER   255
#define IS_LEAP_YEAR(YEAR)      ((!((YEAR) % 400)) || ((!((YEAR) % 4)) && ((YEAR) % 100)))

enum
{
    NUMBER_DAY_JANUARY      = 31,
    NUMBER_DAY_FEBRUARY     = 28,
    NUMBER_DAY_MARCH        = 31,
    NUMBER_DAY_APRIL        = 30,
    NUMBER_DAY_MAY          = 31,
    NUMBER_DAY_JUNE         = 30,
    NUMBER_DAY_JULY         = 31,
    NUMBER_DAY_AUGUST       = 31,
    NUMBER_DAY_SEPTEMBER    = 30,
    NUMBER_DAY_OCTOBER      = 31,
    NUMBER_DAY_NOVEMBER     = 30,
    NUMBER_DAY_DECEMBER     = 31,
};

static void openFile(FILE **pf, char *fileName, char *mode);
static bool getData(int *days, int *month, int year);

int main(void)
{
    FILE *pf_source, *pf_target;
    int year = 0, day = 0, month = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d", &year);

    getData(&day, &month, year);

    fprintf(pf_target, "%02d/%02d/%04d", day, month, year);
    
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

static bool getData(int *days, int *month, int year)
{
    int day_in_month[12] = 
    {
        NUMBER_DAY_JANUARY,
        NUMBER_DAY_FEBRUARY,
        NUMBER_DAY_MARCH,
        NUMBER_DAY_APRIL,
        NUMBER_DAY_MAY,
        NUMBER_DAY_JUNE,
        NUMBER_DAY_JULY,
        NUMBER_DAY_AUGUST,
        NUMBER_DAY_SEPTEMBER,
        NUMBER_DAY_OCTOBER,
        NUMBER_DAY_NOVEMBER,
        NUMBER_DAY_DECEMBER
    };
    int day = 0;

    *days = 0;
    
    for (*month = 0; day < PROGRAMMER_DAY_NUMBER - day_in_month[*month]; *month += 1)
         day += day_in_month[*month];
    
    
    *month += 1;
    *days = PROGRAMMER_DAY_NUMBER - day;
    if (!IS_LEAP_YEAR(year))
        *days += 1;

    return true;
}