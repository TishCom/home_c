/*
 * 6_Inversion.c
 * 
 * Copyright 2026 tisha <tisha@DESKTOP-H2QK95F>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>

#define MONTHS		12

void inversionArr(double arr[], int size);
void swap(double *i, double *y);
int outputArr(double arr[], int size);

int main(int argc, char **argv)
{
	double rain[MONTHS] = {4.3, 4.3, 4.3, 3.0, 2.0, 31.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6};
	
	outputArr(rain, MONTHS);
	inversionArr(rain, MONTHS);
	outputArr(rain, MONTHS);
	
	return 0;
}

void inversionArr(double arr[], int size)
{
	for (int i = 0; i < size / 2; i++)
		swap(&arr[i], &arr[size - i - 1]);
}

void swap(double *i, double *y)
{
	double temp = *i;
	*i = *y;
	*y = temp;
}

int outputArr(double arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%.2f |", arr[i]);
		
	putchar('\n');
	
	return i;
}
