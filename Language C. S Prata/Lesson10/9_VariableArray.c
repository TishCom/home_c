/*
 * 9_VariableArray.c
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

#define MONTHS		5
#define YEARS		3

void copyArr(int column, int string, double arr[string][column], double arr1[string][column]);
int outputArr1(double arr[], int size);
void copyArr1(double arr[], double arr1[], int size);
int outputArr(int column, int string, double arr[string][column]);

int main(int argc, char **argv)
{
	double rain[YEARS][MONTHS] = 
	{
		{4.3, 4.3, 4.3, 3.0, 2.0},
		{8.5, 8.2, 1.2, 1.6, 2.4},
		{9.1, 8.5, 6.7, 4.3, 2.1}
	};
	double rain1[YEARS][MONTHS] = {0};
	
	outputArr(MONTHS, YEARS, rain1);
	
	copyArr(MONTHS, YEARS, rain, rain1);
	
	putchar('\n');
	
	outputArr(MONTHS, YEARS, rain);
		
	putchar('\n');
	
	outputArr(MONTHS, YEARS, rain1);
		
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

int outputArr(int column, int string, double arr[string][column])
{
	int i;
	for (i = 0; i < string; i++)
		outputArr1(arr[i], column);
		
	putchar('\n');
	
	return i;
}

int outputArr1(double arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%.2f |", arr[i]);
		
	putchar('\n');
	
	return i;
}
