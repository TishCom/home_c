#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #define INPUT_FILE   "F:\\C_2026_MFTI\\AdditionalTasks\\7_643_TemporaryKey\\input.txt"
// #define OUTPUT_FILE  "F:\\C_2026_MFTI\\AdditionalTasks\\7_643_TemporaryKey\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE   100

void fopen1(FILE **pf, char *fileName, char *mode);
int number_set_bit(int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0, res = 0;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d", &number);
    number += number_set_bit(number);
    
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

int number_set_bit(int number)
{
    int set_bit = 0;

    while (number > 0)
    {
        if (number % 2)
            set_bit++;
        
        number /= 2;
    }
    
    return set_bit;
}