#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\86_711_KartingCompetition\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\86_711_KartingCompetition\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 255

static void open_file(FILE **pf, char *fileName, char *mode);
static void get_winer(FILE *pf, char winer[], int number_participants, int number_arrivals);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_participants = 0, number_arrivals = 0;
    char name_winer[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d %d", &number_participants, &number_arrivals);

    get_winer(pf_source, name_winer, number_participants, number_arrivals);
    
    fprintf(pf_target, "%s", name_winer);
    
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

static void get_winer(FILE *pf, char winer[], int number_participants, int number_arrivals)
{
    char name_participants[SIZE] = {0};
    int time_arival = 0, sum_time = 0, min_time = 0;

    for (size_t i = 0; i < number_participants; i++)
    {
        fscanf(pf, "%s", name_participants);

        for (size_t y = 0; y < number_arrivals; y++)
        {
            fscanf(pf, "%d", &time_arival);
            sum_time += time_arival;
        }
        
        if (i == 0 || min_time > sum_time)
        {
            min_time = sum_time;
            strcpy(winer, name_participants);
        }

        sum_time = 0;
    }
    
}