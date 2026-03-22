#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 41
#define WORDY "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\9_CountString\\wordy.txt"

void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
    FILE *fp;
    char words[MAX];
    char ch;
    int byte = 0;

    fopen1(&fp, WORDY, "a+");

    while (fscanf(fp, "%d %40s", &byte, words) == 2)
        continue;

    printf("Enter a word to add to the file to complete the symbol #.");

    for (int i = byte + 1; (fscanf(stdin, "%40s", words) == 1) && (words[0] != '#'); i++)
        fprintf(fp, "%d %s\n", i, words);
    
    printf("The contents of the file.\n");

    rewind(fp);

    while ((ch = getc(fp)) != EOF)
        putchar(ch);

    if (fclose(fp) != 0)
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