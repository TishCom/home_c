#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int rsndomNumber(int limit);
int outputArr(int arr[], int size);
int inputRandArr(int arr[], int size, int limit);
void sortDescendingArr(int arr[], int size);
void swap(int *i, int *y);

int main(int argc, char **argv)
{
    srand(time(NULL));

    int arr[SIZE] = {0};

    inputRandArr(arr, SIZE, 10);
    sortDescendingArr(arr, SIZE);
    outputArr(arr, SIZE);

	return 0;
}

int rsndomNumber(int limit)
{
	return rand() % limit + 1;
}

int inputRandArr(int arr[], int size, int limit)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rsndomNumber(limit);
	
	return i;
}

int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d |", arr[i]);
	
	return i;
}

void sortDescendingArr(int arr[], int size)
{
	int sortingFinished;
	
	for (int i = 0; i < size - 1; i++)
	{
		sortingFinished = 1;
		
		for (int y = size - 1; y > i; y--)
		{
			if (arr[y] > arr[y - 1])
			{
				swap(&arr[y], &arr[y - 1]);
				sortingFinished = 0;
			}
		}
		
		if (sortingFinished)
			break;
	}
}

void swap(int *i, int *y)
{
	int temp = *i;
	*i = *y;
	*y = temp;
}