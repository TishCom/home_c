#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

int main(int argc, char **argv)
{
    FILE *fp;
    int ch = 0;
    char name[SIZE] = {0};
    unsigned long count = 0;

    printf("Enter the file name: ");
    scanf("%s", name);

    if ((fp = fopen(name, "r")) == NULL)
    {
        printf("%s", name);
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(fp)) != EOF)
    {
        putc(ch, stdout);
        count++;
    }
    
    fclose(fp);
    printf("\nFile %s contains %d characters.", name, count);
    
	return 0;
}