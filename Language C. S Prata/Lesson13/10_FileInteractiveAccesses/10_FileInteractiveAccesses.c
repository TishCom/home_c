#include <stdio.h>
#include <stdlib.h>

#define MAX 256

void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
    FILE *fp;
    char buf[MAX];
    char ch;
    int index = 0, byte = 0;
    unsigned long pos = 0;

    fopen1(&fp, buf, "rb");

    printf("Enter an index between 0 - %d: ", MAX - 1);

    while (scanf("%d", &index) == 1 && index >= 0 && index < MAX - 1)
    {
        pos = (long)index * sizeof(char);
        fseek(fp, pos, SEEK_SET);

         while ((ch = getc(fp)) != '\n' && ch != EOF)
            putc(ch, stdout);

        printf("\nEnter an index between 0 and %d: ", MAX - 1);
    }

    if (fclose(fp) != 0)
        fprintf(stderr, "Error close.\n");
    
	return 0;
}

void fopen1(FILE **pf, char *fileName, char *mode)
{
    printf("Enter the name of the source file: ");
    scanf("%s", fileName);

    if ((*pf = fopen(fileName, mode)) == NULL)
    {
        fprintf(stderr, "%s\n", fileName);
        exit(EXIT_FAILURE);
    }
}