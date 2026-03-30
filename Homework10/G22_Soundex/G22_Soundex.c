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
char changeChar(char ch);

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

char changeChar(char ch)
{
    if (strchr("bfpv", ch) != NULL)
        return DIGIT_CHAR1;
    else if (strchr("cgjkqsxz", ch) != NULL)
        return DIGIT_CHAR2;
    else if (strchr("dt", ch) != NULL)
        return DIGIT_CHAR3;
    else if (strchr("l", ch) != NULL)
        return DIGIT_CHAR4;
    else if (strchr("mn", ch) != NULL)
        return DIGIT_CHAR5;
    else if (strchr("r", ch) != NULL)
        return DIGIT_CHAR6;
    
    return 0;
}

void transform(char *str)
{
    char ch = 0;
    int number = 0;
    for (int i = 1; i < strlen(str) && number < 4; i++)
    {
        ch = changeChar(str[i]);
        
        if (str[number] != ch && ch != 0)
            str[++number] = ch;
    }

    while (number < 4)
        str[++number] = '0';
    
    str[4] = '\0';
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