#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 100

typedef bool (*comparator)(int, int);

void choiceSorting(int arr[], size_t size, comparator comp);
size_t principleSorting(const int arr[], size_t size, comparator comp);
void fillArrayRandomNumber(int arr[], int size);
void printContentArray(int arr[], int size);
void swap(int *a, int *b);
bool isMore(int a, int b);
bool isLess(int a, int b);
bool isEqual(int a, int b);
int minNumber(int arr[], int size);

int main(void)
{
    srand(time(NULL));

    int array[SIZE] = {0};

    fillArrayRandomNumber(array, SIZE);
    printContentArray(array, SIZE);
    printf("\n\n");
    choiceSorting(array, SIZE, isLess);
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

size_t principleSorting(const int arr[], size_t size, comparator comp)
{
    size_t principleIndex = 0;

    for (size_t i = 1; i < size; i++)
    {
        if (comp(arr[i], arr[principleIndex]))
            principleIndex = i;
    }
    
    return principleIndex;
}

void choiceSorting(int arr[], size_t size, comparator comp)
{
    if (size <= 1)
        return;

    size_t principleIndex = 0;

    for (size_t i = 0; i < size - 1; i++)
    {
        principleIndex = principleSorting(arr + i, size - i, comp);
        swap(&arr[i], &arr[principleIndex + i]);
    }
}