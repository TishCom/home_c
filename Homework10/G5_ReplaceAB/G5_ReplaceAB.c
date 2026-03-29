#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G5_ReplaceAB\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G5_ReplaceAB\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SIZE        1000

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void replaceAB(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "%s\n", "Try again!");

    replaceAB(str);

    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void replaceAB(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        switch (str[i])
        {
            case 'a':
                str[i] = 'b';
                break;
            case 'b':
                str[i] = 'a';
                break;
            case 'A':
                str[i] = 'B';
                break;
            case 'B':
                str[i] = 'A';
        }
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