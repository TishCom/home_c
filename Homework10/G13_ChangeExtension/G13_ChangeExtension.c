#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G13_ChangeExtension\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G13_ChangeExtension\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define COLUMN        100

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);
void expansionFile(char *file, char *expansion);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char str[COLUMN] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    if (fgets1(str, COLUMN, pf_source) != NULL)
        expansionFile(str, ".html");

    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void expansionFile(char *file, char *expansion)
{
    for (int i = strlen(file) - 1; i >= 0; i--)
    {
        if (file[i] == '/')
        {
            strncat(file, expansion, 6);
            break;
        }
        else if (file[i] == '.')
        {
            strncpy(file + i, expansion, 6);
            break;
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