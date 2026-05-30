#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\44_940_Spelling\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\44_940_Spelling\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE     81

static void openFile(FILE **pf, char *fileName, char *mode);
static void deleteFailChar(char word[], int char_number);
static void shiftLeftArry(char word[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    int char_number = 0;
    char word[SIZE];

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %s", &char_number, &word);

    deleteFailChar(word, char_number);
    
    fprintf(pf_target, "%s", word);
    
    fclose(pf_source);
    fclose(pf_target);
}

static void openFile(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

static void deleteFailChar(char word[], int char_number)
{
    shiftLeftArry(word + char_number - 1);
}

static void shiftLeftArry(char word[])
{
    int size = strlen(word) + 1;

    for (size_t i = 0; i < size; i++)
        word[i] = word[i + 1];
}