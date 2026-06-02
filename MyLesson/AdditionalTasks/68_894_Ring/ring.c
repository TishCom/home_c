#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\68_894_Ring\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\68_894_Ring\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define PI   3.14159265358979

static void open_file(FILE **pf, char *fileName, char *mode);
static double inner_radius(double area, double radius);

int main(void)
{
    FILE *pf_source, *pf_target;
    double area = 0, radius = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%lf %lf", &area, &radius);

    fprintf(pf_target, "%.3lf", inner_radius(area, radius));

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

static double inner_radius(double area, double radius)
{
    return sqrtf(radius * radius - (area / PI));
}