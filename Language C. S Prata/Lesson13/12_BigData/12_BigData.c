#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define STRING 20
#define COLUMNS 30
#define COLUMNS_CH COLUMNS + 1
#define FILE_SOURCE "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\12_BigData\\test.txt"
#define FILE_TARGET "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\12_BigData\\test1.txt"
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
void inputArrInt(FILE *pf, int string, int number[][COLUMNS]);
void inputArrChar(int string, int number[][COLUMNS], char simbol[][COLUMNS_CH]);
void outputArrChar(FILE *pf, int string, char simbol[][COLUMNS_CH]);

int main(int argc, char **argv)
{
    FILE *fsource, *ftarget;
    int arr[STRING][COLUMNS] = {0};
    char arr_ch[STRING][COLUMNS_CH] = {0};
    int temp = 0;
    
    fopen1(&fsource, FILE_SOURCE, "r");
    fopen1(&ftarget, FILE_TARGET, "w");

    inputArrInt(fsource, STRING, arr);
    inputArrChar(STRING, arr, arr_ch);
    outputArrChar(ftarget, STRING, arr_ch);
    
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

void inputArrInt(FILE *pf, int string, int number[][COLUMNS])
{
    int temp = 0;

    for (int i = 0; i < string; i++)
    {
        for (int y = 0; y < COLUMNS; y++)
        {
            if (fscanf(pf, "%d", &temp) == 1)
                number[i][y] = temp;
        }
    }
}

void inputArrChar(int string, int number[][COLUMNS], char simbol[][COLUMNS_CH])
{
    for (int i = 0; i < string; i++)
    {
        for (int y = 0; y < COLUMNS; y++)
        {
            simbol[i][y] = trnsformationChar(number[i][y]);

            if (y == COLUMNS - 1)
                simbol[i][COLUMNS] = '\0';
        }
    }
}

void outputArrChar(FILE *pf, int string, char simbol[][COLUMNS_CH])
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