#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\85_778_Office\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\85_778_Office\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 31

static void open_file(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int sum = 0;
    int number[31] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    for (size_t i = 0; i < SIZE; i++)
        fscanf(pf_source, "%d", &number[i]);

    for (size_t i = 0; i < SIZE; i++)
        sum += number[i];
    
    fprintf(pf_target, "%d", sum / (SIZE - 4));
    
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