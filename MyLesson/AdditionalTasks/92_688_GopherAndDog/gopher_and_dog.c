#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\92_688_GopherAndDog\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\92_688_GopherAndDog\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static int get_number_hole(FILE *pf, int gopher_x, int gopher_y, int dog_x, int dog_y, int number);

int main(void)
{
    FILE *pf_source, *pf_target;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, number = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");
    
    fscanf(pf_source, "%d %d %d %d %d", &x1, &y1, &x2, &y2, &number);

    if ((number = get_number_hole(pf_source, x1, y1, x2, y2, number)) == 0)
        fprintf(pf_target, "NO");
    else
        fprintf(pf_target, "%d", number);
    
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

static int get_number_hole(FILE *pf, int gopher_x, int gopher_y, int dog_x, int dog_y, int number)
{
    int hole_x = 0, hole_y = 0;
    float distance_gopher = 0, distance_dog = 0;

    for (int i = 1; i <= number; i++)
    {
        fscanf(pf, "%d %d", &hole_x, &hole_y);

        distance_gopher = sqrt((gopher_x - hole_x) * (gopher_x - hole_x)
                            + (gopher_y - hole_y) * (gopher_y - hole_y));

        distance_dog = sqrt((dog_x - hole_x) * (dog_x - hole_x)
                            + (dog_y - hole_y) * (dog_y - hole_y));

        if (distance_dog / 2 >= distance_gopher)
            return i;
    }
    
    return 0;
}