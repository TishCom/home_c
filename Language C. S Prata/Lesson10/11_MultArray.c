/*
 * 11_MultArray.c
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

int outputArr1(int arr[], int size);
int outputArr(int string, int arr[][MONTHS]);
void multArr(int string, int arr[][MONTHS]);

int main(int argc, char **argv)
{
	int rain[YEARS][MONTHS] = 
	{
		{4, 4, 4, 3, 2},
		{8, 8, 1, 1, 2},
		{9, 8, 6, 4, 2}
	};
	
	outputArr(YEARS, rain);
	multArr(YEARS, rain);
	outputArr(YEARS, rain);
	
	return 0;
}

void multArr(int string, int arr[][MONTHS])
{
	for (int i = 0; i < string; i++)
	{
		for (int y = 0; y < MONTHS; y++)
			arr[i][y] *= 2;
	}
}

int outputArr(int string, int arr[][MONTHS])
{
	int i;
	for (i = 0; i < string; i++)
		outputArr1(arr[i], MONTHS);
		
	putchar('\n');
	
	return i;
}

int outputArr1(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d |", arr[i]);
		
	putchar('\n');
	
	return i;
}
