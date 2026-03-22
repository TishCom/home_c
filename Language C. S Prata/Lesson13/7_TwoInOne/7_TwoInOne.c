#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 256

char* fgets1(char *str, int size, FILE *fl);
void fopen1(FILE **pf, char *fileName, char *mode);

int main(int argc, char **argv)
{
    FILE *in1, *in2;
    char *ch1, *ch2;
    char buf[LEN];

    fopen1(&in1, buf, "r");
    fopen1(&in2, buf, "r");
    
    do
    {
        if ((ch1 = fgets1(buf, LEN, in1)) != NULL)
            printf("%s ", buf);
        if ((ch2 = fgets(buf, LEN, in2)) != NULL)
            printf("%s", buf);
    }while (ch1 || ch2);
    
    if (fclose(in1) != 0 || fclose(in2) != 0)
        fprintf(stderr, "Error\n");
    
	return 0;
}

char* fgets1(char *str, int size, FILE *pf)
{
	char *retVal, *find;
	
	retVal = fgets(str, size, pf);
	
	if (retVal)
	{
		find = strchr(str, '\n');
		
		if (find)
			*find = '\0';
	}
	
	return retVal;
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