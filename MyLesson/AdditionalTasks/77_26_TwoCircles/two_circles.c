#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    long x;
    long y;
    long radius;
} Circles;

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\77_26_TwoCircles\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\77_26_TwoCircles\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static bool are_they_related(Circles circule1, Circles circule2);

int main(void)
{
    FILE *pf_source, *pf_target;
    Circles circule1 = {.x = 0, .y = 0, .radius = 0};
    Circles circule2 = {.x = 0, .y = 0, .radius = 0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%ld %ld %ld", &circule1.x, &circule1.y, &circule1.radius);
    fscanf(pf_source, "%ld %ld %ld", &circule2.x, &circule2.y, &circule2.radius);

    if (are_they_related(circule1, circule2))
        fprintf(pf_target, "YES");
    else
        fprintf(pf_target, "NO");
    
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

static bool are_they_related(Circles circule1, Circles circule2)
{
    double rad = sqrt((circule1.x - circule2.x) * (circule1.x - circule2.x)
                + (circule1.y - circule2.y) * (circule1.y - circule2.y));

    if ((double)circule1.radius + (double)circule2.radius >= rad
        && (double)circule1.radius + rad >= (double)circule2.radius
        && (double)circule2.radius + rad >= (double)circule1.radius)
        return true;

    return false;
}