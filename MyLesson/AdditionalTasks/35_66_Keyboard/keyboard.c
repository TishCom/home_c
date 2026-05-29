#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\34_324_FourDigitPalindrome\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\34_324_FourDigitPalindrome\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int getNextIndex(char ch, char keyboard[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    char my_keyboard[] = "qwertyuiopasdfghjklzxcvbnm";
    char ch = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%c", &ch);

    fprintf(pf_target, "%c", my_keyboard[getNextIndex(ch, my_keyboard)]);

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

static int getNextIndex(char ch, char keyboard[])
{
    int index = 0;
    int size = strlen(keyboard);

    for (; index < size; index++)
    {
        if (ch == keyboard[index])
            break;
    }
    
    index++;
    return index % 26;
}