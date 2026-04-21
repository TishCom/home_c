#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int stringToInt(char *str);

int main(int argc, char **argv)
{
	printf("Hello world!\n");
    printf("%d\n", stringToInt("10101010"));
    printf("%d\n", stringToInt("01010101"));
    printf("%d\n", stringToInt("00000000"));
    printf("%d\n", stringToInt("11111111"));

	return 0;
}

int stringToInt(char *str)
{
    int a = atoi(str);
    int b = 0;

    for (int i = 0; a > 0; i++)
    {
        b += (a % 10) * pow(2, i);
        a /= 10;
    }
    
    return b;
}