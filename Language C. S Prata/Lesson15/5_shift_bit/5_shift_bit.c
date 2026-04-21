#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

int shiftLeftBit(int number, int bit);
void printBinary(uint32_t a);

int main(int argc, char **argv)
{
    printBinary(30000000);
    printBinary(shiftLeftBit(30000000, 11));
    printf("%d\n", sizeof(int));

	return 0;
}

int shiftLeftBit(int number, int bit)
{
    for (int i = 0; i < bit - 1; i++)
    {
        if (number > (number << 1))
            number = (number << 1) + 1;
        else
            number <<= 1;
    }
    
    return number;
}

void printBinary(uint32_t a)
{
    for (int i = 31; i >= 0; i--)
        printf("%d", (a >> i) % 2);
    
    printf("\n");
}