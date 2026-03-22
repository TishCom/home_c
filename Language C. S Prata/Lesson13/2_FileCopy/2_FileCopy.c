#include <stdio.h>
#include <stdlib.h>

#define SIZE 256

int main(int argc, char **argv)
{
    FILE *fsource, *ftarget;
    int bytes = 0;
    char buf[SIZE] = {0};

    if (argc != 3)
    {
        printf("%s", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if ((fsource = fopen(argv[1], "rb")) == NULL)
    {
        printf("%s", argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((ftarget = fopen(argv[2], "wb")) == NULL)
    {
        printf("%s", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    while ((bytes = fread(buf, sizeof(char), SIZE, fsource)) > 0)
        fwrite(buf, sizeof(char), bytes, ftarget);
    
    fclose(fsource);
    fclose(ftarget);
    
	return 0;
}