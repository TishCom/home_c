/*
 * 7_DoubleArray.c
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
#define YEARS		5

void copyArr(int column, int string, double arr[string][column], double arr1[string][column]);
int outputArr(double arr[], int size);
void copyArr1(double arr[], double arr1[], int size);

int main(int argc, char **argv)
{
	double rain[YEARS][MONTHS] = 
	{
		{4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6},
		{8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3},
		{9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4},
		{7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2},
		{7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 0.0, 1.3, 2.6, 5.2}
	};
	double rain1[YEARS][MONTHS] = {0};
	
	for (int i = 0; i < YEARS; i++)
		outputArr(rain1[i], MONTHS);
	
	copyArr(MONTHS, YEARS, rain, rain1);
	
	putchar('\n');
	
	for (int i = 0; i < YEARS; i++)
		outputArr(rain[i], MONTHS);
		
	putchar('\n');
	
	for (int i = 0; i < YEARS; i++)
		outputArr(rain1[i], MONTHS);
		
	return 0;
}

void copyArr(int column, int string, double arr[string][column], double arr1[string][column])
{
	for (int i = 0; i < string; i++)
		copyArr1(arr[i], arr1[i], column);
}

void copyArr1(double arr[], double arr1[], int size)
{
	for (int i = 0; i < size; i++)
		arr1[i] = arr[i];
}

int outputArr(double arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%.2f |", arr[i]);
		
	putchar('\n');
	
	return i;
}
