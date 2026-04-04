#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G19_MakePalindrome\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G19_MakePalindrome\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        1100
#define SIZE_ALF    30

typedef struct
{
    int num;
    char polindrom[SIZE];
    char alf[SIZE_ALF];
    int number[SIZE_ALF];
}dictionary;

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void deleteSpace(char *str);
void skipSpace(char *str, int leave);
void shiftLeftArr(char arr[], int size);
void haveLetter(char *str, dictionary *string);
bool isHaveNotLetter(char ch, dictionary *string);
void numberLetter(char *str, dictionary *string);
void makePolindrome(dictionary *string);
int numberAsymmetricalLetter(int arr[], int size);
int comparator (const void *a, const void *b);
void swapChar(char *i, char *y);
int numberCharacter(dictionary *string);
char findSymbol(dictionary *string);
void deleteAsymmetricalLetter(dictionary *string, int numberDelete);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};
    dictionary string = {.alf = {0}, .num = 0, .number = {0}, .polindrom = {0}};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Fail read!\n");

    deleteSpace(str);
    haveLetter(str, &string);
    qsort(string.alf, string.num, sizeof (char), comparator);
    numberLetter(str, &string);
    deleteAsymmetricalLetter(&string, numberAsymmetricalLetter(string.number, string.num) - 1);
    makePolindrome(&string);
    fprintf(pf_target, "%s", string.polindrom);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void makePolindrome(dictionary *string)
{
    int size = numberCharacter(string);
    char ch = 0;
    for (int i = 0, y = 0; i < string->num; i++)
    {
        while (string->number[i] > 1)
        {
            string->polindrom[y] = string->alf[i];
            string->polindrom[size - y - 1] = string->alf[i];
            string->number[i] -= 2;
            y++;
        }
    }

    if (ch = findSymbol(string))
        string->polindrom[size / 2] = ch;

    string->polindrom[size] = '\0';
}

int comparator (const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

char findSymbol(dictionary *string)
{
    for (int i = 0; i < string->num; i++)
    {
        if (string->number[i] == 1)
            return string->alf[i];
    }

    return 0;
}

int numberCharacter(dictionary *string)
{
    int number = 0;

    for (int i = 0; i < string->num; i++)
        number += string->number[i];

    return number;
}

void deleteAsymmetricalLetter(dictionary *string, int numberDelete)
{
    for (int i = string->num - 1; numberDelete > 0; i--)
    {
        if (string->number[i] % 2)
        {
            string->number[i]--;
            numberDelete--;
        }
    }
}

void swapChar(char *i, char *y)
{
	char temp = *i;
	*i = *y;
	*y = temp;
}

int numberAsymmetricalLetter(int arr[], int size)
{
    int number = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] % 2)
            number++;
    }
    
    return number;
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