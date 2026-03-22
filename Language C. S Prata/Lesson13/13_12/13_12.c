#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define STRING 20
#define COLUMNS 30
#define COLUMNS_CH COLUMNS + 1
#define FILE_SOURCE "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\13_12\\test.txt"
#define FILE_TARGET "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\13_12\\test1.txt"
#define CHAR_0 ' '
#define CHAR_1 '.'
#define CHAR_2 '\''
#define CHAR_3 ':'
#define CHAR_4 '~'
#define CHAR_5 '*'
#define CHAR_6 '='
#define CHAR_7 '@'
#define CHAR_8 '%'
#define CHAR_9 '#'

void fopen1(FILE **pf, char *fileName, char *mode);
char trnsformationChar(int number);
void inputArrInt(FILE *pf, int string, int columns, int number[string][columns]);
void inputArrChar(int string, int columns, int number[string][columns], char simbol[string][columns + 1]);
void outputArrChar(FILE *pf, int string, int columns, char simbol[string][columns]);

int main(int argc, char **argv)
{
    FILE *fsource, *ftarget;
    int string = 20, columns = 30;
    int arr[string][columns];
    char arr_ch[string][columns + 1];
    
    fopen1(&fsource, FILE_SOURCE, "r");
    fopen1(&ftarget, FILE_TARGET, "w");

    inputArrInt(fsource, string, columns, arr);
    inputArrChar(string, columns, arr, arr_ch);
    outputArrChar(ftarget, string, columns + 1, arr_ch);
    
    if (fclose(fsource) != 0 || fclose(ftarget) != 0)
        fprintf(stderr, "Error close.\n");
    
	return 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "%s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void inputArrInt(FILE *pf, int string, int columns, int number[string][columns])
{
    int temp = 0;

    for (int i = 0; i < string; i++)
    {
        for (int y = 0; y < columns; y++)
        {
            if (fscanf(pf, "%d", &temp) == 1)
                number[i][y] = temp;
        }
    }
}

void inputArrChar(int string, int columns, int number[string][columns], char simbol[string][columns + 1])
{
    for (int i = 0; i < string; i++)
    {
        for (int y = 0; y < columns; y++)
        {
            simbol[i][y] = trnsformationChar(number[i][y]);

            if (y == columns - 1)
                simbol[i][columns] = '\0';
        }
    }
}

void outputArrChar(FILE *pf, int string, int columns, char simbol[string][columns])
{
    for (int i = 0; i < string; i++)
        fprintf(pf, "%s\n", simbol[i]);
}

char trnsformationChar(int number)
{
    switch (number)
    {
        case 0:
            return CHAR_0;
        case 1:
            return CHAR_1;
        case 2:
            return CHAR_2;
        case 3:
            return CHAR_3;
        case 4:
            return CHAR_4;
        case 5:
            return CHAR_5;
        case 6:
            return CHAR_6;
        case 7:
            return CHAR_7;
        case 8:
            return CHAR_8;
        case 9:
            return CHAR_9;
    }

    return -1;
}