#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G20_PossibleMakePalindrome\\input.txt"
#define INPUT_FILE  "input.txt"

#define SIZE        1100
#define SIZE_ALF    30

typedef struct
{
    int num;
    char alf[SIZE_ALF];
    int number[SIZE_ALF];
}dictionary;

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void skipSpace(char *str, int leave);
void deleteSpace(char *str);
void shiftLeftArr(char arr[], int size);
int readLetter(char *str, dictionary *string);
void haveLetter(char *str, dictionary *string);
bool isHaveNotLetter(char ch, dictionary *string);
void numberLetter(char *str, dictionary *string);
bool is_palindrom(char *str);

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

bool is_palindrom(char *str)
{
    dictionary string = {.alf = {0}, .num = 0, .number = {0}};

    readLetter(str, &string);

    for (int i = 0, number = 0; i < string.num; i++)
    {
        if (string.number[i] % 2)
            number++;
        
        if (number > 1)
            return false;
    }

    return true;
}

int readLetter(char *str, dictionary *string)
{
    deleteSpace(str);
    haveLetter(str, string);
    numberLetter(str, string);
}

void haveLetter(char *str, dictionary *string)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isHaveNotLetter(str[i], string))
            string->alf[string->num++] = str[i];
    }
}

bool isHaveNotLetter(char ch, dictionary *string)
{
    for (int i = 0; i < string->num; i++)
    {
        if (ch == string->alf[i])
            return false;
    }

    return true;
}

void numberLetter(char *str, dictionary *string)
{
    for (int i = 0; i < string->num; i++)
    {
        for (int y = 0; y < strlen(str); y++)
        {
            if (str[y] == string->alf[i])
                string->number[i]++;
        }
    }
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