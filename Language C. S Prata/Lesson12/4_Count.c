#include <stdio.h>

int counter(void);

int main(int argc, char **argv)
{
    for (int i = 0; i < 10; i++)
        printf("Hello World!!! - %d\n", counter());

	return 0;
}

int counter(void)
{
    static int count = 0;
    return ++count;
}