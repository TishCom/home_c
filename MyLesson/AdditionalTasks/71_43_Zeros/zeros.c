#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\71_43_Zeros\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\MyLesson\\AdditionalTasks\\71_43_Zeros\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE   100

static void open_file(FILE **pf, char *fileName, char *mode);
static int max_serial_zero(char serial[]);

int main(void)
{
    FILE *pf_source, *pf_target;
    char serials[SIZE] = {0};

    open_file(&pf_source, INPUT_FILE, "r");
    open_file(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%s", serials);

    fprintf(pf_target, "%d",  max_serial_zero(serials));

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

static int max_serial_zero(char serial[])
{
    int max_serial = 0, current_serial = 0;

    for (size_t i = 0; i < strlen(serial); i++)
    {
        switch (serial[i])
        {
            case '0':
                current_serial++;
                break;

            case '1':
                if (current_serial > max_serial)
                    max_serial = current_serial;
                current_serial = 0;
                break;
            
            default:
                break;
        }
    }
    
    return max_serial > current_serial ? max_serial : current_serial;
}