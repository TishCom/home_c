#include <stdio.h>
#include <time.h>

void diley(double time);

int main(int argc, char **argv)
{
	printf("Hello world!\n");
    diley(10);
    printf("Hello world!\n");
    
	return 0;
}

void diley(double time)
{
    clock_t time1 = clock();

    while ((((double)clock() - (double)time1) / (double)CLOCKS_PER_SEC) < time)
        continue;
}