#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE   45

struct film
{
    char title[TSIZE];
    int rating;
    struct film* next;
    struct film* previous;
};

char* s_gets(char* str, int length);
void skip_string(void);

int main(void)
{
    struct film* head = NULL;
    struct film *prev = NULL, *current = NULL;
    char input[TSIZE] = {0};

    puts("Enter the name of the first movie:");
    while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
    {
        current = (struct film*) malloc(sizeof(struct film));

        if (head == NULL)
        {
            head = current;
        }
        else
        {
            prev->next = current;
        }
            
        current->next = NULL;
        current->previous = prev;
        strcpy(current->title, input);

        puts("Enter your rating value(1 - 10):");
        scanf("%d", &current->rating);
        skip_string();
        puts("Enter the name of the next movie (or an empty line to stop entering):");

        prev = current;
    }

    if (head == NULL)
        printf("No data entered.");
    else
        printf("List of films:\n");
    
    current = head;
    while (current != NULL)
    {
        printf("Movie: \"%s\" Rating: %d\n", current->title, current->rating);
        current = current->next;
    }
    current = head;
    while (current->next != NULL)
        current = current->next;
    while (current != NULL)
    {
        printf("Movie: \"%s\" Rating: %d\n", current->title, current->rating);
        current = current->previous;
    }
    
    current = head;
    while (current != NULL)
    {
        head = current->next;
        free(current);
        current = head;
    }

    printf("Exit.\n");
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