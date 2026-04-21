#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

#define SIZE 100

int binaryToDecimal(int a);
void printBinary(uint32_t a);

int main(int argc, char **argv)
{
    int arg1 = binaryToDecimal(atoi(argv[1])), arg2 = binaryToDecimal(atoi(argv[2]));

    printBinary(arg1);
    printBinary(arg2);
    printBinary(~arg1);
    printBinary(~arg2);
    printBinary(arg1 & arg2);
    printBinary(arg1 | arg2);
    printBinary(arg1 ^ arg2);

	return 0;
}

int binaryToDecimal(int a)
{
    int b = 0;

    for (int i = 0; a > 0; i++)
    {
        b += (a % 10) * pow(2, i);
        a /= 10;
    }
    
    return b;
}

void printBinary(uint32_t a)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", (a >> i) % 2);
    
    printf("\n");
}