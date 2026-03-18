#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int rsndomNumber(int limit);
void printNumberDigit(int size, int limit);

int main(int argc, char **argv)
{
    int arr[SIZE] = {0};

    for (int i = 0; i < 10; i++)
    {
        srand(i);
        printNumberDigit(SIZE, 10);
        printf("------------------------------\n");
    }

	return 0;
}

int rsndomNumber(int limit)
{
	return rand() % limit + 1;
}

void printNumberDigit(int size, int limit)
{
	int digit[10] = {0};
	
	for (int i = 0; i < size; i++)
		digit[rsndomNumber(limit) - 1]++;
		
	for (int i = 0; i < 10; i++)
	{
		if (digit[i])
			printf("%d %d\n", i + 1, digit[i]);
	}
}