#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 256

int main(int argc, char **argv)
{
    FILE *in, *out;
    int ch;
    char name[LEN];
    int count;

    printf("Enter the name of the source file: ");
    scanf("%s", name);

    if ((in = fopen(name, "r")) == NULL)
    {
        fprintf(stderr, "%s\n", name);
        exit(EXIT_FAILURE);
    }

    printf("Enter the name of the file to edit: ");
    scanf("%s", name);

    if ((out = fopen(name, "w")) == NULL)
    {
        fprintf(stderr, "%s\n", name);
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(in)) != EOF)
    {
        if (count++ % 3 == 0)
            putc(ch, out);
    }
    
    if (fclose(in) != 0 || fclose(out) != 0)
        fprintf(stderr, "Error\n");

    puts("Exit.");
    
	return 0;
}