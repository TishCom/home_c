#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\57_678_Thimbles\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\57_678_Thimbles\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    char ch = 0;
    int result = 1;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    while (fscanf(pf_source, "%c", &ch) == 1)
    {
        switch (ch)
        {
            case 'A':
                if (result == 1)
                    result = 2;
                else if (result == 2)
                    result = 1;
                break;
            
            case 'B':
                if (result == 2)
                    result = 3;
                else if (result == 3)
                    result = 2;
                break;

            case 'C':
                if (result == 1)
                    result = 3;
                else if (result == 3)
                    result = 1;
                break;
            
            default:
                break;
        }
    }

    fprintf(pf_target, "%d", result);

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