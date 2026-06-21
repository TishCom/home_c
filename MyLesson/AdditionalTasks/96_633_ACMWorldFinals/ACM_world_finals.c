#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\96_633_ACMWorldFinals\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\96_633_ACMWorldFinals\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 50

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, int size, char arr[][50]);
static int func(const void *a, const void *b);
static void get_string(FILE *pf, int size, char arr[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    char lable[SIZE];
    char name[3][SIZE];

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    // fscanf(pf_source, "%s", lable);
    get_string(pf_source, SIZE, lable);
    fill_array(pf_source, 3, name);
    qsort(name, 3, sizeof(name[0]), func);

    fprintf(pf_target, "%s: %s, %s, %s", lable, name[0], name[1], name[2]);
    
    fclose(pf_source);
    fclose(pf_target);
}

static void open_file(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

static void fill_array(FILE *pf, int size, char arr[][SIZE])
{
    for (int i = 0; i < size; i++)
        get_string(pf, SIZE, arr[i]);
}

static int func(const void *a, const void *b)
{
    return strcmp((char*)a, (char*)b);
}

static void get_string(FILE *pf, int size, char arr[])
{
    char *ch;

    fgets(arr, SIZE, pf);
    ch  = strchr(arr, '\n');

    if (ch)
        *ch = '\0';
}