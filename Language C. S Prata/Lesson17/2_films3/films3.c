#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void showmovies(Item item);
char* s_gets(char *str, int length);
void skip_string(void);

int main(void)
{
    List movies;
    Item temp;
    InitializeList(&movies);
    if (ListIsFull(&movies))
    {
        fprintf(stderr, "No available memory! The program has been terminated.\n");
        exit(1);
    }

    puts("Enter the name of the first movie:");
    while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
    {
        puts("Enter your rating value(1 - 10):");
        scanf("%d", &temp.rating);
        skip_string();
        if (AddItem(temp, &movies) == false)
        {
            fprintf(stderr, "Memory allocation error.\n");
            exit(1);
        }
        if (ListIsFull(&movies))
        {
            puts("The list is full.");
            break;
        }
        puts("Enter the name of the next movie (or an empty string to stop entering):");
    }
    
    if (ListIsEmpty(&movies))
        printf("No data has been entered.");
    else
    {
        printf("Movie list:\n");
        Traverse(&movies, showmovies);
    }
    printf("You have entered %d movies.\n", ListItemCount(&movies));

    EmptyTheList(&movies);
    printf("The program has ended.\n");
}

void showmovies(Item item)
{
    printf(" Movie: \"%s\" Rating: %d\n", item.title, item.rating);
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