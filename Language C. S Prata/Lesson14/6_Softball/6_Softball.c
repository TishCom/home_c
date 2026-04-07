#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 15

#define INPUT_FILE  "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson14\\6_Softball\\input.txt"

struct gamer
{
    char lastname[30];
    char firstname[30];
    uint16_t score;
    uint16_t passage;
    uint16_t run;
    float average;
};
//номер имя фамилия прием_мяча нанесенные_удары проходы пробежки

void fopen1(FILE **pf, char *fileName, char *mode);
void init(struct gamer *a);

int main(int argc, char **argv)
{
    struct gamer team[SIZE] = {0};
    int number = 0, tresh = 0;
    FILE *pf;

    for (int i = 0; i < SIZE; i++)
        init(&team[i]);
    
    fopen1(&pf, INPUT_FILE, "r");

    while (fscanf(pf, "%d", &number) == 1)
    {
        fscanf(pf, "%s%s%d%d%d%d", team[number].firstname, team[number].lastname, &tresh, &tresh, &team[number].passage, &team[number].run);
    }

    for (int i = 0; i < SIZE; i++)
    {
        printf("%s %s - %d %d\n", team[i].firstname, team[i].lastname, team[i].passage, team[i].run);
    }
    
	return 0;
}

void init(struct gamer *a)
{
    a->average = 0;
    strcpy(a->firstname, "");
    strcpy(a->lastname, "");
    a->passage = 0;
    a->run = 0;
    a->score = 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}