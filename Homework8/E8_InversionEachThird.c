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
float meanArr(int arr[], int size);
void inversionHalves3Arr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	inversionHalves3Arr(arr, SIZE);
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

float meanArr(int arr[], int size)
{
	float sum = 0;
	for (int i = 0; i < size; i++)
		sum += arr[i];
	
	return sum / size;
}

void inversionHalves3Arr(int arr[], int size)
{
	int arr1[size / 3];
	
	for (int i = 0, y = size / 3 - 1; i < size / 3; i++, y--)
		arr1[i] = arr[y];
		
	for (int i = 0; i < size / 3; i++)
		arr[i] = arr1[i];
		
	for (int i = 0, y = size * 2 / 3 - 1; i < size / 3; i++, y--)
		arr1[i] = arr[y];
		
	for (int i = 0; i < size / 3; i++)
		arr[i + size / 3] = arr1[i];
		
	for (int i = 0, y = size - 1; i < size / 3; i++, y--)
		arr1[i] = arr[y];
		
	for (int i = 0; i < size / 3; i++)
		arr[i + size * 2 / 3] = arr1[i];
}
