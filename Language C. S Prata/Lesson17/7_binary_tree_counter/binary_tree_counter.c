#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define INPUT_FILE  "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson17\\7_binary_tree_counter\\my_text_file.txt"
#define SIZE   100

void fopen1(FILE **pf, char *fileName, char *mode);
void print_string(Item item);
void skip_string(void);
char *s_gets(char *str, int length);

int main(void)
{
    FILE *pf_source;
    char string[SIZE];
    Tree my_tree;
    Item item;
    char ch = 0;

    InitializeTree(&my_tree);
    fopen1(&pf_source, INPUT_FILE, "r");

    while (fscanf(pf_source, "%s", string) == 1)
    {
        strcpy(item.string, string);
        item.counter = 1;

        if (InTree(&item, &my_tree))
            IncrementItem(&item, &my_tree);
        else
            AddItem(&item, &my_tree);
    }

    ch = getchar();
    skip_string();
    switch (ch)
    {
        case 'a':
            Traverse(&my_tree, print_string);
            break;
        case 'b':
            s_gets(string, SIZE);
            strcpy(item.string, string);
            if (GetItem(&item, &my_tree))
                printf("%s - %d\n", item.string, item.counter);
            break;
        case 'c':
            printf("Exit.\n");
    }

    fclose(pf_source);
    DeleteAll(&my_tree);
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "Fail open - %s\n", fileName);
        exit(EXIT_FAILURE);
    }
}

void print_string(Item item)
{
    printf("%s - %d\n", item.string, item.counter);
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