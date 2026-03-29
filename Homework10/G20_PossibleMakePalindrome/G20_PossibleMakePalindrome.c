#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G20_PossibleMakePalindrome\\input.txt"
#define INPUT_FILE  "input.txt"

#define SIZE        1100

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void skipSpace(char *str, int leave);
void shiftLeftArr(char arr[], int size);
void deleteSpace(char *str);
bool is_palindrom(char *string);
int pairChar(char ch, char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");

    if (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Fail read!\n");

    if (is_palindrom(str))
        printf("YES");
    else
        printf("NO");

    fclose(pf_source);
    
	return 0;
}

bool is_palindrom(char *string)
{
    int number = 0;

    deleteSpace(string);

    for (int i = 0; i < strlen(string); i++)
    {
        if (pairChar(string[i], string) % 2 == 1)
            number++;

        if (number > 1)
            return false;
    }

    if (number <= 1)
        return true;

    return false;
}

int pairChar(char ch, char *str)
{
    int coincidence = 0;

    for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ch)
			coincidence++;
	}
	
	return coincidence;
}

void deleteSpace(char *str)
{
    while (*str)
        skipSpace(str++, 0);
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