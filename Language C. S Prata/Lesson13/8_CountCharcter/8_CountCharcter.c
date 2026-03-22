#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *in;
    char ch;
    int count = 0;

    if (argc < 2)
    {
        fprintf(stderr, "%s\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    else if (argc == 2)
    {
        while ((ch = getchar()) != EOF)
        {
            if (ch == argv[1][0])
                count++;
        }

        printf("%d - %s - %c\n", count, "stdin", argv[1][0]);
    }
    else
    {
        for (int i = 2; i < argc; i++)
        {
            if ((in = fopen(argv[i], "r")) == NULL)
            {
                fprintf(stderr, "%s\n", argv[i]);
                continue;
            }

            while ((ch = getc(in)) != EOF)
            {
                if (ch == argv[1][0])
                    count++;
            }
            
            printf("%d - %s - %c\n", count, argv[i], argv[1][0]);
            count = 0;
            fclose(in);
        }
    }
    
	return 0;
}