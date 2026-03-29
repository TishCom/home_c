#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G15_CaoLing\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G15_CaoLing\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        1100

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void changeWord(char *str, int size, char *word1, char *word2);
void shiftRightArr(char arr[], int size);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Fail read!\n");

    changeWord(str, SIZE, "Cao", "Ling");
    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void shiftRightArr(char arr[], int size)
{
	for (int i = size - 1; i > 0; i--)
		arr[i] = arr[i - 1];
}

void changeWord(char *str, int size, char *word1, char *word2)
{
    char *pch;
    int sizeWord1 = strlen(word1);
    int sizeWord2 = strlen(word2);
    for (int i = 0; i < strlen(str); i++)
    {
        if ((pch = strstr(str + i, word1)) != NULL)
        {
            shiftRightArr(pch + sizeWord1, size - (pch - str) - sizeWord1);
            memcpy(pch, word2, sizeWord2);
            i = sizeWord1 - 1;
        }
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