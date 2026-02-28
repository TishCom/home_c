/*
 * E12_AscendingDescending.c
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

#define SIZE 	10

int inputArr(int arr[], int size);
int outputArr(int arr[], int size);
void sortHalvesArr(int arr[], int crushing, int size);
void sortCrushingArr(int arr[], int number, int isAscending, int size);
void sortAscendingArr(int arr[], int size);
void sortDescendingArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	sortHalvesArr(arr, 2, SIZE);
	outputArr(arr, SIZE);
	
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
		printf("%d ", arr[i]);
	
	return i;
}

void sortAscendingArr(int arr[], int size)
{
	int temp = 0;
	
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (arr[i] > arr[y + 1])
			{
				temp = arr[i];
				arr[i] = arr[y + 1];
				arr[y + 1] = temp;
			}
		}
	}
}

void sortDescendingArr(int arr[], int size)
{
	int temp = 0;
	
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (arr[i] < arr[y + 1])
			{
				temp = arr[i];
				arr[i] = arr[y + 1];
				arr[y + 1] = temp;
			}
		}
	}
}

void sortHalvesArr(int arr[], int crushing, int size)
{
	sortCrushingArr(arr, 0, true, size / crushing);
	sortCrushingArr(arr, 1, false, size / crushing);
}

void sortCrushingArr(int arr[], int number, int isAscending, int size)
{
	int arr1[size];
	
	for (int i = 0, y = size * number; i < size; i++, y++)
		arr1[i] = arr[y];
		
	if (isAscending)
		sortAscendingArr(arr1, size);
	else
		sortDescendingArr(arr1, size);
	
	for (int i = 0; i < size; i++)
		arr[i + size * number] = arr1[i];
}
