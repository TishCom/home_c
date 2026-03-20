#include <stdio.h>
#include <stdlib.h>

int* make_array(int size, int value);
void show_array(const int arr[], int size);

int main(int argc, char **argv)
{
    int *pa;
    int size, value;

    printf("Enter the number of items: ");
    while (scanf("%d", &size) == 1 && size > 0)
    {
        printf("Enter the initialization value: ");
        scanf("%d", &value);
        pa = make_array(size, value);

        if (pa)
        {
            show_array(pa, size);
            free(pa);
        }

        printf("Enter the number of items: ");
    }
    
    printf("Exit.");
    
	return 0;
}

int *make_array(int size, int value)
{
    int *ptr = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
        ptr[i] = value;
    
    return ptr;
}

void show_array(const int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i % 8 == 0 && i != 0)
            putchar('\n');

        printf("%d |", arr[i]);
    }

    putchar('\n');
}
