#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int randomNumber(int limit);
void printMas(int size, int arr[], int number);
void shiftLeftArr(int arr[], int size);

int main(int argc, char **argv)
{
    srand(time(NULL));

    int mas[100] = {0};

    for (int i = 0; i < 100; i++)
        mas[i] = i;
    
    for (int i = 0; i < 100; i++)
        printf("%d ", mas[i]);

    printf("\n");
    printMas(100, mas, 7);
    printf("\n");
    for (int i = 0; i < 93; i++)
        printf("%d ", mas[i]);

	return 0;
}

void printMas(int size, int arr[], int number)
{
    int n = 0;
    for (int i = 0; i < number; i++)
    {
        n = randomNumber(size);
        printf("%d ", arr[n]);
        shiftLeftArr(arr + n, size - n);
    }
}

int randomNumber(int limit)
{
	return (rand() % limit);
}

void shiftLeftArr(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
		arr[i] = arr[i + 1];
}