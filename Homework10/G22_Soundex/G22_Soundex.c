#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G22_Soundex\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G22_Soundex\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"

#define SIZE        100

#define DIGIT_CHAR1 '1'
#define DIGIT_CHAR2 '2'
#define DIGIT_CHAR3 '3'
#define DIGIT_CHAR4 '4'
#define DIGIT_CHAR5 '5'
#define DIGIT_CHAR6 '6'

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void transform(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};
    char ch = 0;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fgets1(str, SIZE, pf_source) == NULL)
        printf("Try again.\n");
        
    transform(str);
    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void transform(char *str)
{
    char arr[100] = {str[0]};
    char ch = 0;
    int number = 0;
    for (int i = 1; i < strlen(str); i++)
    {
        switch (str[i])
        {
            case 'b':
            case 'f':
            case 'p':
            case 'v':
                ch = DIGIT_CHAR1;
                break;
            case 'c':
            case 'g':
            case 'j':
            case 'k':
            case 'q':
            case 's':
            case 'x':
            case 'z':
                ch = DIGIT_CHAR2;
                break;
            case 'd':
            case 't':
                ch = DIGIT_CHAR3;
                break;
            case 'l':
                ch = DIGIT_CHAR4;
                break;
            case 'm':
            case 'n':
                ch = DIGIT_CHAR5;
                break;
            case 'r':
                ch = DIGIT_CHAR6;
                break;
        }
        
        if (arr[number] != ch && ch != 0)
            arr[++number] = ch;
    }

    while (number < 4)
        arr[++number] = '0';
    
    arr[4] = '\0';
    strncpy(str, arr, 5);
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