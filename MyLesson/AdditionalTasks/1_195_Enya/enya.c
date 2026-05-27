#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define INPUT_FILE   "F:\\C_2026_MFTI\\AdditionalTasks\\1_195_Enya\\input.txt"
// #define OUTPUT_FILE  "F:\\C_2026_MFTI\\AdditionalTasks\\1_195_Enya\\output.txt"
#define INPUT_FILE      "input.txt"
#define OUTPUT_FILE     "output.txt"
#define SIZE   100

void fopen1(FILE **pf, char *fileName, char *mode);
void skip_string(void);
char *s_gets(char *str, int length);

int main(void)
{
    FILE *pf_source, *pf_target;
    int number = 0, res = 1;

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");
    
    while (fscanf(pf_source, "%d", &number) == 1)
        res *= number;
    res *= 2;

    printf("%d", res);
    fprintf(pf_target, "%d", res);

    fclose(pf_source);
    fclose(pf_target);
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

char *s_gets(char *str, int length)
{
    char* ret_val;
    char* find;

    ret_val = fgets(str, length, stdin);
    if (ret_val)
    {
        find = strchr(str, '\n');
        if (find)
            *find = '\0';
        else
            skip_string();
    }
    
    return ret_val;
}

void skip_string(void)
{
    while (getchar() != '\n')
        continue;
}