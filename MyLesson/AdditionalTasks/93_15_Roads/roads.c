#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <inttypes.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\93_15_Roads\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\93_15_Roads\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static int get_number_road(FILE *pf, int number_city);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number_city = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d", &number_city);

    fprintf(pf_target, "%d", get_number_road(pf_source, number_city));
    
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

static int get_number_road(FILE *pf, int number_city)
{
    if (number_city == 0)
        return 0;

    int number_road = 0;
    int city_road = 0;

    for (size_t i = 0; i < number_city * number_city; i++)
    {
        fscanf(pf, "%d", &city_road);

        if (city_road == 1)
            number_road++;
    }

    return number_road / 2;
}