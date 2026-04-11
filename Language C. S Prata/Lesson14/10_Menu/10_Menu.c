#include <stdio.h>
#include <string.h>

#define SIZE 4

typedef void (*funcPtr)(void);

void sum(void);
void sub(void);
void mult(void);
void divide(void);
void menu(void);
void skipString(void);
int correctInput(void);
int convertChar(char ch);

int main(int argc, char **argv)
{
    int numberFunc = 0;
    funcPtr arr[SIZE] = {sum, sub, mult, divide};

    //while ((numberFunc = correctInput()) != 'e' - 'a')
    while ((numberFunc = correctInput()) != 'e')
        arr[numberFunc - 'a']();

    printf("exit\n");

	return 0;
}

void menu(void)
{
    printf("Select a menu item:\n");
    printf("a) sum\n");
    printf("b) sub\n");
    printf("c) mult\n");
    printf("d) divide\n");
    printf("e) exit\n");
}

int correctInput(void)
{
    char ch = 0;

    menu();

    ch = getchar();
    skipString();
    while (strchr("abcde", ch) == NULL)
    {
        printf("Try again.\n");
        ch = getchar();
        skipString();
    }
    
    //return convertChar(ch);
    return ch;
}

int convertChar(char ch)
{
    return ch - 'a';
}

void skipString(void)
{
    while (getchar() != '\n')
        continue;
}

void sum(void)
{
    printf("sum\n");
}

void sub(void)
{
    printf("sub\n");
}

void mult(void)
{
    printf("mult\n");
}

void divide(void)
{
    printf("divide\n");
}