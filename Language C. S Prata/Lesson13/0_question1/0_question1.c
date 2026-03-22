#include <stdio.h>
#include <string.h>

#define SIZE 256

int main(int argc, char **argv)
{
    FILE *fp;
    char ch = 0;
    char str[SIZE] = {0};

    if (argc < 3)
        return -1;

    ch = argv[1][0];

    if ((fp = fopen(argv[2], "r")) == NULL)
        return -2;

    while (fgets(str, SIZE, fp) != NULL)
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] == ch)
            {
                printf("%s", str);
                break;
            }
        }
    }
    
	return 0;
}