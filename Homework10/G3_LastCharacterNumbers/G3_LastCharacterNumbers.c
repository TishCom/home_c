#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G3_LastCharacterNumbers\\input.txt"
#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G3_LastCharacterNumbers\\output.txt"
//#define INPUT_FILE  "input.txt"
//#define OUTPUT_FILE "output.txt"
#define SIZE        1000

void fopen1(FILE **pf, char *fileName, char *mode);
char* fgets1(char *str, int size, FILE *pf);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    int size = 0, index = 0;
    char str[SIZE] = {0}, ch = 0;

    fopen1(&pf_source, INPUT_FILE, "r");
    //fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fgets1(str, SIZE, pf_source) == NULL)
        printf("Try again.\n");

    size = strlen(str) - 1;
    ch = str[size];
    printf("%d\n", size);

    while (index < size)
    {
        index = (strchr(str + index, ch) - str) / sizeof(char);
        printf("%d ", index++);
    }

    //fprintf(pf_target, "%s", str);
    fclose(pf_source);
    //fclose(pf_target);
    
	return 0;
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