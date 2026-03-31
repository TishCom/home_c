#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G9_RemoveDuplicateCharacters\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G9_RemoveDuplicateCharacters\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SIZE        1000

typedef int (*func)(int);

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void ciclicShiftLeftArr(char arr[], int size, int offset);
int matching(char *str, int size, int offset);
void group(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fgets(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Tray again!\n");

    group(str);
    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void group(char *str)
{
    int size = strlen(str);
    for (int offset = 0, match = 0; offset < size;)
    {
        if (str[offset] == '\0')
            return;
        else if ((match = matching(str, size, offset)) != offset)
            ciclicShiftLeftArr(str, size, match);
        else if (str[offset] == ' ')
            ciclicShiftLeftArr(str, size, offset);
        else
            offset++;
    } 
}

int matching(char *str, int size, int offset)
{
    for (int i = offset; i < size - offset; i++)
    {
        if (str[offset] == str[i] && i != offset)
            return i;
    }

    return offset;
}

void ciclicShiftLeftArr(char arr[], int size, int offset)
{
	for (int i = offset; i < size - 1; i++)
		arr[i] = arr[i + 1];
		
	arr[size - 1] = '\0';
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