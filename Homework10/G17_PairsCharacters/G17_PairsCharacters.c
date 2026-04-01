#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G17_PairsCharacters\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G17_PairsCharacters\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        1100

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void swap(char *i, char *y);
int nextIndexChar(char *str, int index);
void changeCharacter(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Fail read!\n");

    changeCharacter(str);
    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void changeCharacter(char *str)
{
    for (int current = 0, previous = 0, i = 0; current < strlen(str); i++)
    {
        current = nextIndexChar(str, current);

        if (i % 2)
            swap(str + previous, str + current);
        
        previous = current++;
    }
}

int nextIndexChar(char *str, int index)
{
    int i;
    for (i = index; i < strlen(str); i++)
    {
        if (!isspace(str[i]) && !ispunct(str[i]))
            return i;
    }

    return i;
}

void swap(char *i, char *y)
{
	char temp = *i;
	*i = *y;
	*y = temp;
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