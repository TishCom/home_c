#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 256

int main(int argc, char **argv)
{
    FILE *fsource;
    char ch = 0;

    if (argc < 2)
    {
        printf("%s", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i < argc; i++)
    {
        if ((fsource = fopen(argv[i], "r")) == NULL)
        {
            printf("%s", argv[i]);
            exit(EXIT_FAILURE);
        }
    
        while ((ch = getc(fsource)) != EOF)
            putc(ch, stdout);
    
        printf("\n");
        fclose(fsource);
    }
    
	return 0;
}