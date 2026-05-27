#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\11_950_CompressionBinarySequences\\input.txt"
// #define OUTPUT_FILE "F:\\C_2026_MFTI\\AdditionalTasks\\11_950_CompressionBinarySequences\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE 100

void openFile(FILE **pf, char *fileName, char *mode);
void compressionBinarySequences(char *origin_number, char *compression_number);

int main(void)
{
    FILE *pf_source, *pf_target;
    char number[300] = {0};
    char compression[20] = {0};

    openFile(&pf_source, INPUT_FILE, "r");
    openFile(&pf_target, OUTPUT_FILE, "w");

    fscanf(pf_source, "%s", number);
    compressionBinarySequences(number, compression);
    fprintf(pf_target, "%s", compression);

    fclose(pf_source);
    fclose(pf_target);
}

void openFile(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void compressionBinarySequences(char *origin_number, char *compression_number)
{
    int number_zero = 0;

    for (size_t i = 0, y = 0; i < strlen(origin_number); i++)
    {
        switch (origin_number[i])
        {
            case '0':
                number_zero++;
                break;

            case '1':
                compression_number[y] = 'a' + number_zero;
                number_zero = 0;
                y++;
        }
    }
}