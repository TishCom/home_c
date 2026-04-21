#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

int setBit(int a);

int main(int argc, char **argv)
{
    printf("%d\n", setBit(11255));

	return 0;
}

int setBit(int a)
{
    int b = 0;

    while (a > 0)
    {
        if (a % 2)
            b++;
        
        a >>= 1;
    }
    
    return b;
}