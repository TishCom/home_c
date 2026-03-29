#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G18_RemoveSpaces\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G18_RemoveSpaces\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        1100

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void skipSpace(char *str, int leave);
void shiftLeftArr(char arr[], int size);
void deleteSpace(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Fail read!\n");

    deleteSpace(str);
    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void deleteSpace(char *str)
{
    skipSpace(str, 0);
    
    while (*str)
        skipSpace(str++, 1);
}

void skipSpace(char *str, int leave)
{
    if (isspace(*str))
    {
        while (isspace(*(str + leave)))
            shiftLeftArr(str + leave, strlen(str));
    }
}

void shiftLeftArr(char arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
        arr[i + 1] = '\0';
    }
}

char* fgets1(char *str, int size, FILE *pf)
{
	char *retVal, *find;
	
	retVal = fgets(str, size, pf);
	
	if (retVal)
	{
		find = strchr(str, '\n');
		
		if (find)
			*find = '\0';
	}
	
	return retVal;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}