/*
 * E13_SecondLastZero.c
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
int coincidenceElementArr(int arr[], int element, int size);
int selectionCoincidenceArr(int arr[], int arr1[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	int arr1[SIZE] = {0};
	int size = 0;
	
	inputArr(arr, SIZE);
	size = selectionCoincidenceArr(arr, arr1, SIZE);
	outputArr(arr1, size);
	
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

int selectionCoincidenceArr(int arr[], int arr1[], int size)
{
	int y = 0, temp = 0;
	
	for (int i = 0; i < size; i++)
	{
		temp = arr[i];
		
		for (int a = i + 1; a < size; a++)
		{
			if (temp == arr[a] && !coincidenceElementArr(arr1, temp, size)) 
			{
				arr1[y] = arr[i];
				y++;
				break;
			}
		}
	}
	
	return y;
}

int coincidenceElementArr(int arr[], int element, int size)
{
	int coincidence = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == element)
		{
			coincidence = 1;
			break;
		}
	}
	
	return coincidence;
}
