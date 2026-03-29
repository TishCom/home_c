#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G11_EndsWithA\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G11_EndsWithA\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define STRING        1000
#define COLUMN        100

typedef int (*func)(int);

void fopen1(FILE **pf, char *fileName, char *mode);
int endWithA(int string, char str[][COLUMN]);
int fillArray(FILE *pf, int string, char str[][COLUMN]);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[STRING][COLUMN] = {0};
    int string;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    string = fillArray(pf_source, STRING, str);
    fprintf(pf_target, "%d", endWithA(string, str));

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

int fillArray(FILE *pf, int string, char str[][COLUMN])
{
    int number;
    for (number = 0; number < string; number++)
    {
        if (fscanf(pf, "%s", str[number]) != 1)
            break;
    }

    return number;
}

int endWithA(int string, char str[][COLUMN])
{
    int number = 0;
    for (int i = 0; i < string; i++)
    {
        if (str[i][strlen(str[i]) - 1] == 'a')
            number++;
    }

    return number;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}