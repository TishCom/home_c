#include <stdio.h>

#define HARMONIC_MEAN(X, Y) (1 / ((1 / (X) + 1 / (Y)) / 2))

int main(int argc, char **argv)
{
    float a = 8.8, b = 3.4;
	printf("Hello world!\n");

    printf("%.2f, %.2f, %.2f\n", a, b, HARMONIC_MEAN(a, b));

	return 0;
}