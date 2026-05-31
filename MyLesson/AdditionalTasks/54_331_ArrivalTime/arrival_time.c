#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\54_331_ArrivalTime\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\54_331_ArrivalTime\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void openFile(FILE **pf, char *fileName, char *mode);
static int maxGapNumber(int horizontal, int vertical);

int main(void)
{
    FILE *pf_source, *pf_target;
    int current_hour = 0, current_minut = 0, trevel_hour = 0, trevel_minut = 0;

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%d:%d %d %d", &current_hour, &current_minut, &trevel_hour, &trevel_minut);

    if ((current_minut + trevel_minut) / 60)
        trevel_hour++;
    trevel_hour = (current_hour + trevel_hour) % 24;
    trevel_minut = (current_minut + trevel_minut) % 60;
    
    fprintf(pf_target, "%02d:%02d", trevel_hour, trevel_minut);

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