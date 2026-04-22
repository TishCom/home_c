#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int stringToInt(char *str);

int main(int argc, char **argv)
{
    printf("%d\n", stringToInt("10101010"));
    printf("%d\n", stringToInt("01010101"));
    printf("%d\n", stringToInt("00000000"));
    printf("%d\n", stringToInt("11111111"));

	return 0;
}

int stringToInt(char *str)
{
    int rez = 0;

    for (int i = 0, y = strlen(str) - 1; y >= 0; y--, i++)
        rez += (str[y] - '0') * pow(2, i);
    
    return rez;
}
