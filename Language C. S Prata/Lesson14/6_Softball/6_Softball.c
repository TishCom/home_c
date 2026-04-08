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
    uint16_t receiving;
    uint16_t blowsInflicted;
    uint16_t passage;
    uint16_t run;
    float average;
};
//номер имя фамилия прием_мяча нанесенные_удары проходы пробежки

void fopen1(FILE **pf, char *fileName, char *mode);
void init(struct gamer *a);
void read(FILE *pf, struct gamer *a);
void average(struct gamer *a);

int main(int argc, char **argv)
{
    struct gamer team[SIZE] = {0};
    int number = 0, tresh = 0;
    FILE *pf;

    for (int i = 0; i < SIZE; i++)
        init(&team[i]);
    
    fopen1(&pf, INPUT_FILE, "r");

    while (fscanf(pf, "%d", &number) == 1)
        read(pf, &team[number]);

    for (int i = 0; i < SIZE; i++)
        average(&team[i]);

    for (int i = 0; i < SIZE; i++)
        printf("%s %s - %d %d %d %d %.2f\n", team[i].firstname, team[i].lastname, team[i].receiving, team[i].blowsInflicted, team[i].passage, team[i].run, team[i].average);
    
    fclose(pf);
    
	return 0;
}

void average(struct gamer *a)
{
    a->average = (float)a->blowsInflicted / (float)a->receiving;
}

void read(FILE *pf, struct gamer *a)
{
    struct gamer player = {0};
    fscanf(pf, "%s%s%d%d%d%d", a->firstname, a->lastname, &player.receiving, &player.blowsInflicted, &player.passage, &player.run);

    a->receiving += player.receiving;
    a->blowsInflicted += player.blowsInflicted;
    a->passage += player.passage;
    a->run += player.run;
}

void init(struct gamer *a)
{
    a->average = 0;
    strcpy(a->firstname, "");
    strcpy(a->lastname, "");
    a->passage = 0;
    a->run = 0;
    a->receiving = 0;
    a->blowsInflicted = 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}