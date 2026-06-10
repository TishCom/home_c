#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\89_929_PlayingDice\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\89_929_PlayingDice\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static long long get_min(long long number);

int main(void)
{
    FILE *pf_source, *pf_target;
    long long number = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%lld", &number);

    fprintf(pf_target, "%lld %lld", get_min(number), number * 6);
    
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

static long long get_min(long long number)
{
    long long min = number / 6;

    switch (number % 6)
    {
        case 1:
            min += 6;
            break;

        case 2:
            min += 5;
            break;
        
        case 3:
            min += 4;
            break;

        case 4:
            min += 3;
            break;

        case 5:
            min += 2;
            break;
        
        default:
            break;
    }

    return min;
}