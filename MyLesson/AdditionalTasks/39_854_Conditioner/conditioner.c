#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\39_854_Conditioner\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\39_854_Conditioner\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE    7

static void openFile(FILE **pf, char *fileName, char *mode);
static bool controlTemperature(char current_mode[], char mode[]);
static bool isUpper(int temp_room, int temp_cond);
static bool isLower(int temp_room, int temp_cond);

int main(void)
{
    FILE *pf_source, *pf_target;
    int temp_room = 0, temp_cond = 0;
    char mode[SIZE];

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d %d %s", &temp_room, &temp_cond, mode);

    if (controlTemperature(mode, "heat") && isLower(temp_room, temp_cond)
        || controlTemperature(mode, "freeze") && isUpper(temp_room, temp_cond)
        || controlTemperature(mode, "auto"))
        temp_room = temp_cond;

    fprintf(pf_target, "%d", temp_room);

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

static bool controlTemperature(char current_mode[], char mode[])
{
    return strcmp(current_mode, mode) ? false : true;
}

static bool isLower(int temp_room, int temp_cond)
{
    return temp_room < temp_cond;
}

static bool isUpper(int temp_room, int temp_cond)
{
    return temp_room > temp_cond;
}