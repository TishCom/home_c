#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\95_895_TicTacToe\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\95_895_TicTacToe\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static void fill_array(FILE *pf, char arr[], int size);
static bool win_horisontal(char arr[], char ch);
static bool win_vertical(char arr[], char ch);
static bool win_diagonal(char arr[], char ch);
static bool is_win(char arr[], char ch);

int main(void)
{
    FILE *pf_source, *pf_target;
    char arr[9] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    // fscanf(pf_source, "%d %d %d %d %d", &n, &m, &i, &j, &c);
    fill_array(pf_source, arr, 9);

    if (is_win(arr, 'X'))
        fprintf(pf_target, "Win");
    else if (is_win(arr, 'O'))
        fprintf(pf_target, "Lose");
    else
        fprintf(pf_target, "Draw");
    
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

static void fill_array(FILE *pf, char arr[], int size)
{
    char ch = 0;

    for (int i = 0; i < size;)
    {
        fscanf(pf, "%c", &ch);

        if (!isspace(ch))
        {
            arr[i] = ch;
            i++;
        }
    }
}

static bool win_horisontal(char arr[], char ch)
{
    int counter = 0;

    for (size_t i = 0; i < 9; i += 3)
    {
        for (size_t y = 0; y < 3; y++)
        {
            if (arr[i + y] == ch)
                counter++;
        }

        if (counter == 3)
            return true;

        counter = 0;
    }

    return false;
}

static bool win_vertical(char arr[], char ch)
{
    int counter = 0;

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t y = 0; y < 9; y += 3)
        {
            if (arr[i + y] == ch)
                counter++;
        }

        if (counter == 3)
            return true;

        counter = 0;
    }

    return false;
}

static bool win_diagonal(char arr[], char ch)
{
    if (arr[0] == ch && arr[4] == ch && arr[8] == ch
        || arr[2] == ch && arr[4] == ch && arr[6] == ch)
        return true;

    return false;
}

static bool is_win(char arr[], char ch)
{
    return win_horisontal(arr, ch) || win_vertical(arr, ch) || win_diagonal(arr, ch);
}