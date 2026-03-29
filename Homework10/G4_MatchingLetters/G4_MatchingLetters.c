#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define INPUT_FILE  "F:\\C_2026_MFTI\\Lesson10\\G4_MatchingLetters\\input.txt"
//#define OUTPUT_FILE "F:\\C_2026_MFTI\\Lesson10\\G4_MatchingLetters\\output.txt"
#define INPUT_FILE  "input.txt"
#define OUTPUT_FILE "output.txt"
#define SIZE        100

void fopen1(FILE **pf, char *fileName, char *mode);
bool isOnlyOne(char *str, int index);

int main(int argc, char **argv)
{
	FILE *pf_source, *pf_target;
    char word1[SIZE] = {0};
    char word2[SIZE] = {0};

    fopen1(&pf_source, INPUT_FILE, "r");
    fopen1(&pf_target, OUTPUT_FILE, "w");

    while (fscanf(pf_source, "%s %s", word1, word2) != 2)
        fprintf(stderr, "%s\n", "Try again!");

    for (int i = 0; i < strlen(word1); i++)
    {
        if (isOnlyOne(word1, i))
        {
            for (int y = 0; y < strlen(word2); y++)
            {
                if (isOnlyOne(word2, y) && (word1[i] == word2[y]))
                    fprintf(pf_target, "%c ", word1[i]);
            }
        }
    }

    fclose(pf_source);
    fclose(pf_target);
    
	return 0;
}

bool isOnlyOne(char *str, int index)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[index] == str[i] && i != index)
            return false;
    }

    return true;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}