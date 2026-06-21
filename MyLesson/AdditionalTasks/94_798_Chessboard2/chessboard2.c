#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\94_798_Chessboard2\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\94_798_Chessboard2\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static int get_colored_angle(int i, int j, int c);

int main(void)
{
    FILE *pf_source, *pf_target;
    int n = 0, m = 0, i = 0, j = 0, c = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d %d %d %d %d", &n, &m, &i, &j, &c);

    if (n % 2 == 0 || m % 2 == 0)
        fprintf(pf_target, "equal");
    else
    {
        c = get_colored_angle(i, j, c);
        if (c == 0)
            fprintf(pf_target, "black");
        else
            fprintf(pf_target, "white");
    }
    
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

static int get_colored_angle(int i, int j, int c)
{  
    if (i % 2 == 1 && j % 2 == 0)
        c = c == 0 ? 1 : 0;
    else if (i % 2 == 0 && j % 2 == 1)
        c = c == 0 ? 1 : 0;
        
    return c;
}