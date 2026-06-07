#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\79_715_MishaAndNnegative\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\79_715_MishaAndNnegative\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define STRING 100
#define COLUMN 100

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, int string, int column, char foto[][COLUMN]);
static int get_number_fail(int string, int column, char foto1[][COLUMN], char foto2[][COLUMN]);

int main(void)
{
    FILE *pf_source, *pf_target;
    int string = 0, column = 0;
    char foto1[STRING][COLUMN] = {0};
    char foto2[STRING][COLUMN] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d", &string, &column);
    fill_array(pf_source, string, column, foto1);
    fill_array(pf_source, string, column, foto2);

    fprintf(pf_target, "%d", get_number_fail(string, column, foto1, foto2));
    
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

static void fill_array(FILE *pf, int string, int column, char foto[][COLUMN])
{
    char ch = 0;

    for (size_t s = 0; s < string; s++)
    {
        for (size_t c = 0; c < column; c++)
        {
            fscanf(pf, "%c", &ch);
            if (isspace(ch))
                c--;
            else
                foto[s][c] = ch;
        }
    }
}

static int get_number_fail(int string, int column, char foto1[][COLUMN], char foto2[][COLUMN])
{
    int number_fail = 0;

    for (size_t s = 0; s < string; s++)
    {
        for (size_t c = 0; c < column; c++)
        {
            if (foto1[s][c] == foto2[s][c])
                number_fail++;
        }
    }

    return number_fail;
}