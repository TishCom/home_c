#include <stdio.h>
#include <math.h>

#define SIZE 100

typedef double (*funcPtr)(double);

double mult(double a);
double divide(double a);
void transform(double source[], double target[], int size, funcPtr func);
void printArr(double target[], int size);
void fillArr(double source[], int size);

int main(int argc, char **argv)
{
    double source[SIZE] = {0};
    double target[SIZE] = {0};

	fillArr(source, SIZE);
    printArr(source, SIZE);
    printf("\n");
    transform(source, target, SIZE, sin);
    printArr(target, SIZE);
    printf("\n");
    transform(source, target, SIZE, cos);
    printArr(target, SIZE);
    printf("\n");
    transform(source, target, SIZE, mult);
    printArr(target, SIZE);
    printf("\n");
    transform(source, target, SIZE, divide);
    printArr(target, SIZE);
    printf("\n");

	return 0;
}

void fillArr(double source[], int size)
{
    for (int i = 0; i < size; i++)
        source[i] = i * 1.23;
}

void printArr(double target[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%.2f ", target[i]);
    printf("\n");
}

void transform(double source[], double target[], int size, funcPtr func)
{
    for (int i = 0; i < size; i++)
        target[i] = func(source[i]);
}

double mult(double a)
{
    return a * 1.54;
}

double divide(double a)
{
    return a / 1.54;
}