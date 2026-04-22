#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

#define SIZE 100

int stringToInt(char *str);
void printBinary(uint32_t a);

int main(int argc, char **argv)
{
    //int arg1 = stringToInt(argv[1]), arg2 = stringToInt(argv[2]);
    int arg1 = stringToInt("10101010"), arg2 = stringToInt("01010101");
    
    printf("%d - %d\n", arg1, arg2);

    printBinary(arg1);
    printBinary(arg2);
    printBinary(~arg1);
    printBinary(~arg2);
    printBinary(arg1 & arg2);
    printBinary(arg1 | arg2);
    printBinary(arg1 ^ arg2);

	return 0;
}

int stringToInt(char *str)
{
    int rez = 0;

    for (int i = 0, y = strlen(str) - 1; y >= 0; y--, i++)
        rez += (str[y] - '0') * pow(2, i);
    
    return rez;
}

void printBinary(uint32_t a)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", (a >> i) % 2);
    
    printf("\n");
}
