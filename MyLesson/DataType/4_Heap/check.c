#include <stdio.h>
#include <math.h>

int ResetHighBit(int number);

void main (void)
{
    printf("Hello\n");
    printf("%d\n", ResetHighBit(9));
}

int ResetHighBit(int number) 
{
    if (number <= 0)
        return number;

    int msb = 1;
    while (msb <= number / 2) 
        msb <<= 1;
    
    return number & ~msb; 
}