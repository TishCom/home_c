#include <stdio.h>
#include <string.h>
#include "stack.h"

#define MAXSTRING   100

char* s_gets(char *str, int length);
void skip_string(void);

int main(void)
{
    char string[MAXSTRING] = {0};
    Stack my_stack;
    Item item;

    InitializeStack(&my_stack);

    s_gets(string, MAXSTRING);

    for (size_t i = 0; i < strlen(string); i++)
    {
        item = string[i];
        PushStack(&item, &my_stack);
    }
    
    while (!StackIsEmpty(&my_stack))
    {
        PopStack(&item, &my_stack);
        printf("%c", item);
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