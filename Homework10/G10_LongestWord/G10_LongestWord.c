#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G10_LongestWord\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G10_LongestWord\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define STRING        100
#define COLUMN        1000

typedef int (*func)(int);

void fopen1(FILE **pf, char *fileName, char *mode);
int indexMaxString(int string, char str[][COLUMN]);
int fillArray(FILE *pf, int string, char str[][COLUMN]);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[STRING][COLUMN] = {0};
    int string;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    string = fillArray(pf_source, STRING, str);
    
    fprintf(pf_target, "%s", str[indexMaxString(string, str)]);

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

int indexMaxString(int string, char str[][COLUMN])
{
    int index = 0;
    for (int i = 1; i < string; i++)
    {
        if (strlen(str[index]) < strlen(str[i]))
            index = i;
    }

    return index;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}