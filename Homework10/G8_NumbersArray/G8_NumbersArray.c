#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G8_NumbersArray\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G8_NumbersArray\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SIZE        1000

typedef int (*func)(int);

void fopen1(FILE **pf, char *fileName, char *mode);
int fillingArray(FILE * pf, int arr[], int size);
int comparator (const void *a, const void *b);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    int number[SIZE] = {0}, size = 0;;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    size = fillingArray(pf_source, number, SIZE);
    qsort(number, size, sizeof (int), comparator);

    for (int i = 0; i < size; i++)
        fprintf(pf_target, "%d ", number[i]);
    
    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

int comparator (const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int fillingArray(FILE * pf, int arr[], int size)
{
    int i = 0;
    do
    {
        if (fscanf(pf, "%d", &arr[i]) == 1)
            i++;
    } while (getc(pf) != EOF && i < size);

    return i;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}