#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
    FILE *fp;
    char buf[MAX];
    char *str;

    if (argc != 3)
    {
        fprintf(stderr, "%s\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    fopen1(&fp, argv[2], "r");

    while (fgets(buf, MAX, fp) != NULL)
    {
        if ((str = strstr(buf, argv[1])) != NULL)
            fputs(buf, stdout);
    }

    if (fclose(fp) != 0)
        fprintf(stderr, "Error close.\n");
    
	return 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "%s\n", fileName);
        exit(EXIT_FAILURE);
    }
}