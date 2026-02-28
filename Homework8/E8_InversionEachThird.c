/*
 * E8_InversionEachThird.c
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

#define SIZE 12

int inputArr(int arr[], int size);
int outputArr(int arr[], int size);
void inversionArr(int arr[], int size);
void copyArr(int arr[], int arr1[], int size);
void inversionHalvesArr(int arr[], int number, int size);
void inversionCrushingArr(int arr[], int number, int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	inversionHalvesArr(arr, 3, SIZE);
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

void inversionHalvesArr(int arr[], int number, int size)
{
	for (int q = 0; q < number; q++)
		inversionCrushingArr(arr, q, size / number);
}

void inversionCrushingArr(int arr[], int number, int size)
{
	int arr1[size];
	
	for (int i = 0, y = size * number; i < size; i++, y++)
		arr1[i] = arr[y];
		
	inversionArr(arr1, size);
		
	for (int i = 0; i < size; i++)
		arr[i + size * number] = arr1[i];
}

void copyArr(int arr[], int arr1[], int size)
{
	for (int i = 0; i < size; i++)
		arr1[i] = arr[i];
}

void inversionArr(int arr[], int size)
{
	int temp;
	for (int i = 0; i < size / 2; i++)
	{
		temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}
}
