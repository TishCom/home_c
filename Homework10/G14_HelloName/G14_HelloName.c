#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G14_HelloName\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G14_HelloName\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        100

void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char sname[SIZE] = {0};
    char lname[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fscanf(pf_source, "%s %s", sname, lname) != 2)
        fprintf(stderr, "Fail read!\n");
    
    fprintf(pf_target, "Hello, %s %s!", lname, sname);

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