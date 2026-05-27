#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #define INPUT_FILE   "F:\\C_2026_MFTI\\AdditionalTasks\\6_504_Flowers\\input.txt"
// #define OUTPUT_FILE  "F:\\C_2026_MFTI\\AdditionalTasks\\6_504_Flowers\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE   100

enum flower
{
    GCV = 0,
    VGC,
    CVG
};

char string[3][4] = 
{
    "GCV",
    "VGC",
    "CVG"
};

void fopen1(FILE **pf, char *fileName, char *mode);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0, res = GCV;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d", &number);

    for (size_t i = 0; i < number; i++)
    {
        switch (res)
        {
            case GCV:
                res = VGC;
                break;
            case VGC:
                res = CVG;
                break;
            case CVG:
                res = GCV;
        }
    }
    
    fprintf(pf_target, "%s", string[res]);

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