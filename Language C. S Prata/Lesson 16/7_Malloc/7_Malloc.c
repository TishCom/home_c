#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void show_array(const double arr[], int size);
double* new_d_array(int size, ...);

int main(int argc, char **argv)
{
	double *p1, *p2;

	p1 = new_d_array(5, 1.2, 2.3, 3.4, 4.5, 5.6);
	p2 = new_d_array(4, 100.0, 20.00, 8.08, -1890.0);

	show_array(p1, 5);
	show_array(p2, 4);

	free(p1);
	free(p2);

	return 0;
}

void show_array(const double arr[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%.2f |", arr[i]);

	printf("\n");
}

double *new_d_array(int size, ...)
{
	va_list ap;
	double *ptr = malloc(size * sizeof(double));
	va_start(ap, size);

	for (int i = 0; i < size; i++)
		ptr[i] = va_arg(ap, double);
	
	va_end(ap);

    return ptr;
}
