#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G12_ParseWords\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G12_ParseWords\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define STRING        1000
#define COLUMN        100

typedef int (*func)(int);

void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[COLUMN] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fscanf(pf_source, "%s", str) == 1)
        fprintf(pf_target, "%s\n", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}