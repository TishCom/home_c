/*
 * E3_MaximumMinimumTheirNumbers.c
 * 
 * Copyright 2026 Tisha <Tisha@DESKTOP-TSPB5RM>
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

#define SIZE 10

int inputArr(int arr[], int size);
int outputArr(int arr[], int size);
float meanArr(int arr[], int size);
int minArr(int arr[], int size);
int maxArr(int arr[], int size);
int posArr(int arr[], int element, int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	int min = 0, max = 0, posMin = 0, posMax = 0;
	
	inputArr(arr, SIZE);
	
	min = minArr(arr, SIZE);
	max = maxArr(arr, SIZE);
	posMin = posArr(arr, min, SIZE);
	posMax = posArr(arr, max, SIZE);
	
	printf("%d %d %d %d\n", posMax, max, posMin, min);
	
	return 0;
}

int inputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	return i;
}

int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d |", arr[i]);
	
	return i;
}

float meanArr(int arr[], int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++)
		sum += arr[i];
	
	return sum / size;
}

int minArr(int arr[], int size)
{
	int min =  arr[0];
	
	for (int i = 1; i < size; i++)
	{
		if (min > arr[i])
			min = arr[i];
	}
	
	return min;
}

int maxArr(int arr[], int size)
{
	int max =  arr[0];
	
	for (int i = 1; i < size; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	
	return max;
}

int posArr(int arr[], int element, int size)
{
	int pos;
	
	for (pos = 0; pos < size; pos++)
	{
		if (element == arr[pos])
		{
			pos++;
			break;
		}
	}
	
	if (pos == size && element != arr[pos - 1])
		return -1;
		
	return pos;
}
