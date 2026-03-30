#include <stdio.h>
#include <stdlib.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G2_StringNumbers\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G2_StringNumbers\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SIZE        40

void fopen1(FILE **pf, char *fileName, char *mode);
void makeString(char *str, int number);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    int number = 0;
    char str[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fscanf(pf_source, "%d", &number) != 1)
        printf("Try again.\n");

    makeString(str, number);

    fprintf(pf_target, "%s", str);

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

void makeString(char *str, int number)
{
    for (int i = 2, z = 0; z < number && number < SIZE; z++)
    {
        if (z % 2 == 1)
        {
            str[z] = i + '0';
            if (i == 8)
                i = 2;
            else    
                i += 2;
        }
        else
            str[z] = z / 2 + 'A';
    }
    str[number] = '\0';
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}