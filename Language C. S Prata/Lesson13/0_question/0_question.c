#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *fp;
    double number = 0, average = 0;
    int size = 0;

    if (argc < 2)
        fp = stdin;
    else    
        fp = fopen(argv[1], "r");

    while (fscanf(fp,"%lf", &number) == 1)
    {
        average += number;
        size++;
    }

    average /= (double)size;

    printf("%.2f", average);
    
	return 0;
}