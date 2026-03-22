#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 256
#define STRING 20
#define COLUMNS 30
#define COLUMNS_CH COLUMNS + 1
#define FILE_SOURCE "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\14_12\\test.txt"
#define FILE_TARGET "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\14_12\\test1.txt"
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
void interferenceSuppression(int string, int number[][COLUMNS]);
int itFits(int number1, int number2);
int interferenceSuppression1(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression2(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression3(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression4(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression5(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression6(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression7(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression8(int i, int y, int string, int number[][COLUMNS]);
int interferenceSuppression9(int i, int y, int string, int number[][COLUMNS]);

int main(int argc, char **argv)
{
    FILE *fsource, *ftarget;
    int arr[STRING][COLUMNS] = {0};
    char arr_ch[STRING][COLUMNS_CH] = {0};
    int temp = 0;
    
    fopen1(&fsource, FILE_SOURCE, "r");
    fopen1(&ftarget, FILE_TARGET, "w");

    inputArrInt(fsource, STRING, arr);
    for (int i = 0; i < STRING; i++)
    {
        for (int y = 0; y < COLUMNS; y++)
        {
            printf("%d", arr[i][y]);
            if (y == COLUMNS - 1)
                printf("\n");
        }
    }
    printf("\n");
    interferenceSuppression(STRING, arr);
    for (int i = 0; i < STRING; i++)
    {
        for (int y = 0; y < COLUMNS; y++)
        {
            printf("%d", arr[i][y]);
            if (y == COLUMNS - 1)
                printf("\n");
        }
    }
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

int itFits(int number1, int number2)
{
    int temp = number1 - number2;
    temp = (temp >= 0 ? temp : -temp);
    return temp <= 1;
}

int interferenceSuppression1(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i - 1][y]) || !itFits(number[i][y], number[i + 1][y])
        || !itFits(number[i][y], number[i][y - 1]) || !itFits(number[i][y], number[i][y + 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression2(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i + 1][y]) || !itFits(number[i][y], number[i][y - 1]) || !itFits(number[i][y], number[i][y + 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression3(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i - 1][y]) || !itFits(number[i][y], number[i][y - 1]) || !itFits(number[i][y], number[i][y + 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression4(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i - 1][y]) || !itFits(number[i][y], number[i + 1][y]) || !itFits(number[i][y], number[i][y + 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression5(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i - 1][y]) || !itFits(number[i][y], number[i + 1][y]) || !itFits(number[i][y], number[i][y - 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression6(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i + 1][y]) || !itFits(number[i][y], number[i][y + 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression7(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i - 1][y]) || !itFits(number[i][y], number[i][y + 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression8(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i + 1][y]) || !itFits(number[i][y], number[i][y - 1]))
        return 1;
        
    return 0;
}

int interferenceSuppression9(int i, int y, int string, int number[][COLUMNS])
{
    if (!itFits(number[i][y], number[i - 1][y]) || !itFits(number[i][y], number[i][y - 1]))
        return 1;
        
    return 0;
}

void interferenceSuppression(int string, int number[][COLUMNS])
{
    for (int i = 0; i < string; i++)
    {
        for (int y = 0; y < COLUMNS; y++)
        {
            if (interferenceSuppression1(i, y, string, number) && (i > 0 && i < string - 1) && (y > 0 && y < COLUMNS - 1))
                number[i][y] = round((number[i - 1][y] + number[i + 1][y] + number[i][y - 1] + number[i][y + 1]) / 4.0);
            else if (interferenceSuppression2(i, y, string, number) && (i == 0) && (y > 0 && y < COLUMNS - 1))
                number[i][y] = round((number[i + 1][y] + number[i][y - 1] + number[i][y + 1]) / 3.0);
            else if (interferenceSuppression3(i, y, string, number) && (i == (string - 1)) && (y > 0 && y < COLUMNS - 1))
                number[i][y] = round((number[i - 1][y] + number[i][y - 1] + number[i][y + 1]) / 3.0);
            else if (interferenceSuppression4(i, y, string, number) && (i > 0 && i < string - 1) && (y == 0))
                number[i][y] = round((number[i - 1][y] + number[i + 1][y] + number[i][y + 1]) / 3.0);
            else if (interferenceSuppression5(i, y, string, number) && (i > 0 && i < string - 1) && (y == (COLUMNS - 1)))
                number[i][y] = round((number[i - 1][y] + number[i + 1][y] + number[i][y - 1]) / 3.0);
            else if (interferenceSuppression6(i, y, string, number) && (i == 0) && (y == 0))
                number[i][y] = round((number[i + 1][y] + number[i][y + 1]) / 2.0);
            else if (interferenceSuppression7(i, y, string, number) && (i == (string - 1)) && (y == 0))
                number[i][y] = round((number[i - 1][y] + number[i][y + 1]) / 2.0);
            else if (interferenceSuppression8(i, y, string, number) && (i == 0) && (y == (COLUMNS - 1)))
                number[i][y] = round((number[i + 1][y] + number[i][y + 1]) / 2.0);
            else if (interferenceSuppression9(i, y, string, number) && (i == (string - 1)) && (y == (COLUMNS - 1)))
                number[i][y] = round((number[i - 1][y] + number[i][y - 1]) / 2.0);
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