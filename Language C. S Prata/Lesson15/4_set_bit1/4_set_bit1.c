#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

int setBit(int number, int bit);

int main(int argc, char **argv)
{
    printf("%d\n", setBit(11255, 10));

	return 0;
}

int setBit(int number, int bit)
{
    return (number >> bit) % 2;
}