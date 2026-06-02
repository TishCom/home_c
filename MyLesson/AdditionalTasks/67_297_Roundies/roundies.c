#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\67_297_Roundies\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\67_297_Roundies\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 1000

static void open_file(FILE **pf, char *fileName, char *mode);
static long long sum_roundis(char number[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    char number[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%s", number);

    fprintf(pf_target, "%lld", sum_roundis(number));

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

static long long sum_roundis(char number[])
{
    int sum = 0;

    for (size_t i = 0; i < strlen(number); i++)
    {
        switch (number[i])
        {
            case '0':
                sum++;
                break;
            
            case '6':
                sum++;
                break;

            case '8':
                sum += 2;
                break;

            case '9':
                sum++;
                break;
            
            default:
                break;
        }
    }
    
    return sum;
}