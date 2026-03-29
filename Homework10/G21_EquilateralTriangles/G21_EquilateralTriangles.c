#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G21_EquilateralTriangles\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G21_EquilateralTriangles\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        11000

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
int numberStones(char *str);
bool isPossible(int number);
int numberString(int number);
void printTriangle(char *str, FILE *pf);
void paintStar(FILE *pf, int number);
void paintSpace(FILE *pf, int numberStr, int number);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};
    char ch = 0;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    for (int i = 0; (ch = getc(pf_source)) != EOF; i++)
        str[i] = ch;
    
    printTriangle(str, pf_target);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void printTriangle(char *str, FILE *pf)
{
    int string = 0, number = numberStones(str);
    if (isPossible(number))
    {
        string = numberString(number);
        for (int i = 1; i <= string; i++)
        {
            number -= i;
            paintSpace(pf ,string, i);
            paintStar(pf, i);
        }
    }
    else
        fprintf(pf, "NO");
}

void paintSpace(FILE *pf, int numberStr, int number)
{
    for (int i = 0; i < numberStr - number; i++)
        putc(' ', pf);
}

void paintStar(FILE *pf, int number)
{
    for (int i = 0; i < number; i++)
        fprintf(pf, "* ");

    putc('\n', pf);
}

int numberString(int number)
{
    int i;
    for (i = 1; number != 0; i++)
        number -= i;
    
    return i - 1;
}

bool isPossible(int number)
{
    int i;
    for (i = 1; i <= number; i++)
        number -= i;

    if (number == 0 && i != 1)
        return true;
    
    return false;
}

int numberStones(char *str)
{
    int number = 0;
    while (*str)
    {
        if (*str == '*')
            number++;
        
        str++;
    }

    return number;
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