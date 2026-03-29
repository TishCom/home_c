#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G19_MakePalindrome\\input.txt"
#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G19_MakePalindrome\\output.txt"
// #define INPUT_FILE  "input.txt"
// #define OUTPUT_FILE "output.txt"

#define SIZE        1100

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void skipSpace(char *str, int leave);
void shiftLeftArr(char arr[], int size);
void deleteSpace(char *str);
bool is_palindrom(char *string);
int pairChar(char ch, char *str);
void makePalindrom(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    //fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "Fail read!\n");

    printf("%s\n", str);
    makePalindrom(str);
    printf("%s\n", str);

    fclose(pf_source);
    //fclose(pf_target);
    
	return 0;
}

int comparator1 (const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}
int comparator2 (const void *a, const void *b)
{
    return *(char *)b - *(char *)a;
}

void swap(char *i, char *y)
{
	char temp = *i;
	*i = *y;
	*y = temp;
}

void shiftRightArr(char arr[], int size)
{
	for (int i = size; i > 0; i--)
    {
        arr[i] = arr[i - 1];
        arr[i - 1] = ' ';
    }
}

void makePalindrom(char *str)
{
    char ch = 255;
    for (int i = 0; i < strlen(str); )
    {
        if (pairChar(str[i], str) % 2 == 1)
        {
            if ((unsigned char)ch > (unsigned char)str[i])
                ch = str[i];
            
            shiftLeftArr(str + i, strlen(str) - i);
        }
        else    
            i++;
    }
    char arr[strlen(str) + 2];
    strcpy(arr, str);
    shiftRightArr((arr + strlen(arr) / 2), strlen(arr) / 2);
    arr[strlen(arr) / 2] = ch;
    printf("%s\n", arr);
    qsort(arr, strlen(arr) / 2, sizeof (char), comparator1);
    qsort(arr + strlen(arr) / 2 + strlen(arr) % 2, strlen(arr) / 2, sizeof (char), comparator2);
    strncpy(str, arr, sizeof(arr));
    printf("%s %s %c\n", arr, str, ch);
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
	for (int i = 0; i < size; i++)
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