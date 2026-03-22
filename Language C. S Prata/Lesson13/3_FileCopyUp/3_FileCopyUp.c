#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 256

int main(int argc, char **argv)
{
    FILE *fsource, *ftarget;
    char ch = 0;
    char name[SIZE] = {0};

    printf("Enter the name of the source file: ");
    scanf("%s", name);
    
    if ((fsource = fopen(name, "r")) == NULL)
    {
        printf("%s", name);
        exit(EXIT_FAILURE);
    }

    printf("Enter the name of the file to edit: ");
    scanf("%s", name);

    if ((ftarget = fopen(name, "w")) == NULL)
    {
        printf("%s", name);
        exit(EXIT_FAILURE);
    }
    
    while ((ch = getc(fsource)) != EOF)
    {
        ch = toupper(ch);
        putc(ch, ftarget);
    }
    
    fclose(fsource);
    fclose(ftarget);
    
	return 0;
}