#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 100

typedef bool (*comparator)(int, int);

void fillArrayRandomNumber(int arr[], int size);
void printContentArray(int arr[], int size);
void swap(int *a, int *b);
bool isMore(int a, int b);
bool isLess(int a, int b);
bool isEqual(int a, int b);
void insertionSorting(int arr[], size_t size, comparator comp);

int main(void)
{
    srand(time(NULL));

    int array[SIZE] = {0};

    fillArrayRandomNumber(array, SIZE);
    printContentArray(array, SIZE);
    printf("\n\n");
    insertionSorting(array, SIZE, isMore);
    printContentArray(array, SIZE);
}

void fillArrayRandomNumber(int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        arr[i] = rand();
}

void printContentArray(int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d |", arr[i]);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

bool isMore(int a, int b)
{
    return a > b;
}

bool isLess(int a, int b)
{
    return a < b;
}

bool isEqual(int a, int b)
{
    return a == b;
}

void insertionSorting(int arr[], size_t size, comparator comp)
{
    if (size <= 1)
        return;

    for (size_t i = 0; i < size - 1; i++)
    {
        for (size_t y = i + 1; y > 0; y--)
        {
            if (comp(arr[y], arr[y - 1]))
                swap(&arr[y], &arr[y - 1]);
            else
                break;
        }
    }
}