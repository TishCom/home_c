/*
 * 14_13Variable.c
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

#define COLUMNS		5
#define STRINGS		3

void inputArr(int string, int columns, double arr[string][columns]);
void outputArr(int string, int columns, double arr[string][columns]);
double averageStringArr(int size, double arr[]);
double averageArr(int string, int columns, double arr[string][columns]);
double maxArr(int string, int columns, double arr[string][columns]);

int main(int argc, char **argv)
{
	double arr[STRINGS][COLUMNS] = 
	{
		{4.3, 4.3, 4.3, 3.0, 2.0},
		{8.5, 8.2, 1.2, 1.6, 2.4},
		{9.1, 8.5, 6.7, 4.3, 2.1}
	};
	
	outputArr(STRINGS, COLUMNS, arr);
	
	inputArr(STRINGS, COLUMNS, arr);
	
	outputArr(STRINGS, COLUMNS, arr);
		
	for (int i = 0; i < STRINGS; i++)
		printf("Average %d string = %.2f.\n", i, averageStringArr(COLUMNS, arr[i]));
		
	printf("Average = %.2f.\n", averageArr(STRINGS, COLUMNS, arr));
	
	printf("Max = %.2f.\n", maxArr(STRINGS, COLUMNS, arr));
	
	return 0;
}


void inputArr(int string, int columns, double arr[string][columns])
{
	for (int i = 0; i < string; i++)
	{
		printf("Enter 5 double - %d string.\n", i);
		for (int y = 0; y < columns; y++)
			scanf("%lf", &arr[i][y]);
	}	
}

void outputArr(int string, int columns, double arr[string][columns])
{
	for (int i = 0; i < string; i++)
	{
		for (int y = 0; y < columns; y++)
			printf("%.2f |", arr[i][y]);
			
		putchar('\n');
	}	
	putchar('\n');
}

double averageStringArr(int size, double arr[])
{
	double average = 0;
	for (int i = 0; i < size; i++)
		average += arr[i];
	
	return average / size;
}

double averageArr(int string, int columns, double arr[string][columns])
{
	double average = 0;
	for (int i = 0; i < string; i++)
	{
		for (int y = 0; y < columns; y++)
			average += arr[i][y];
	}
	
	return average / (string * columns);
}

double maxArr(int string, int columns, double arr[string][columns])
{
	double max = arr[0][0];
	for (int i = 0; i < string; i++)
	{
		for (int y = 0; y < columns; y++)
			if (max < arr[i][y])
				max = arr[i][y];
	}
	
	return max;
}
