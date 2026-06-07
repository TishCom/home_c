#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\78_817_ManhattanStreets\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\78_817_ManhattanStreets\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"

static void open_file(FILE **pf, char *fileName, char *mode);
static long long asphalt_area(long long n, long long m, long long d, long long k);

int main(void)
{
    FILE *pf_source, *pf_target;
    long long n = 0, m = 0, d = 0, k = 0;

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%lld %lld %lld %lld", &n, &m, &d, &k);

    fprintf(pf_target, "%lld", asphalt_area(n, m, d, k));
    
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

static long long asphalt_area(long long n, long long m, long long d, long long k)
{
    return (n + m) * d * k - n * m * d * d;
}