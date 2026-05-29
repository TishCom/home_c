#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\34_324_FourDigitPalindrome\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\34_324_FourDigitPalindrome\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

#define MIN_C      2
#define MIN_H      6
#define MIN_O      1

static void openFile(FILE **pf, char *fileName, char *mode);
static bool isPolindrom(char number[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    long long C = 0, H = 0, O = 0;
    long long result = 0;
    char number[5];

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%s", number);
    
    fprintf(pf_target, "%s", isPolindrom(number) ? "YES" : "NO");

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

static bool isPolindrom(char number[])
{
    bool ret = true;

    for (size_t i = 0, y = strlen(number) - 1; i < (y + 1) / 2; i++)
    {
        if (number[i] == number[y - i])
            continue;
        
        ret = false;
        break;
    }
    
    return ret;
}