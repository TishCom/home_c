#include <stdio.h>
#include <stdbool.h>

#define SIZE   100

bool find_binary(int arr[], int size, int find_number);

int main(void)
{
    int arr[SIZE];
    for (size_t i = 0, y = 0; y < SIZE; i+=2, y++)
        arr[y] = i;
    
    if (find_binary(arr, SIZE, 188))
        printf("Hello");
    else if (find_binary(arr, SIZE, 17))
        printf("Hi");
    else
        printf("Bad");
}

bool find_binary(int arr[], int size, int find_number)
{
    int left = 0, right = size - 1, number;

    while (right >= left)
    {
        number = (right + left) / 2;

        if (arr[number] == find_number)
            return true;
        else if (arr[number] > find_number)
            right = number - 1;
        else
            left = number + 1;
    }

    return false;
}