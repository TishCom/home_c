#include <stdio.h>
#include <stdlib.h>

#define ARSIZE 1000

int main(int argc, char **argv)
{
    double numbers[ARSIZE];
    double value;
    const char *file = "F:\\C_2026_MFTI\\Language_C_S_Prata\\Lesson13\\5_FileCmd\\numbers.txt";
    int i;
    long pos;
    FILE *iofile;

    for (i = 0; i < ARSIZE; i++)
        numbers[i] = 100.0 * i + 1.0 / (i + 1.0);

    if (argc != 3)
    {
        printf("%s", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((iofile = fopen(argv[1], "wb")) == NULL)
    {
        fprintf(stderr, "%s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    fwrite(numbers, sizeof(double), ARSIZE, iofile);

    fclose(iofile);

    if ((iofile = fopen(file, "rb")) == NULL)
    {
        fprintf(stderr, "%s\n", file);
        exit(EXIT_FAILURE);
    }

    pos = atol(argv[2]) * sizeof(double);
    fseek(iofile, pos, SEEK_SET);
    fread(&value, sizeof(double), 1, iofile);
    printf("The value for this index is: %lf.\n", value);
    
    fclose(iofile);
    puts("Exit.");
    
	return 0;
}