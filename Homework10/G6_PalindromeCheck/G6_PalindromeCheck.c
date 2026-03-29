#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G6_PalindromeCheck\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G6_PalindromeCheck\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SIZE        1000

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
bool is_palindrom(char *str);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fgets1(str, SIZE, pf_source) == NULL)
        fprintf(stderr, "%s\n", "Try again!");

    if (is_palindrom(str))
        fprintf(pf_target, "YES");
    else
        fprintf(pf_target, "NO");

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

bool is_palindrom(char *str)
{
    int size = strlen(str);
    for (int i = 0; i < size / 2; i++)
    {
        if (str[i] == str[size - i - 1])
            continue;
        else
            return false;
    }
    
    return true;
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