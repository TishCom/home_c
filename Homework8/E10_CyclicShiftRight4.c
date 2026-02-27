/*
 * E10_CyclicShiftRight4.c
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

#define SIZE 	12
#define SHIFT 	4

int inputArr(int arr[], int size);
int outputArr(int arr[], int size);
float meanArr(int arr[], int size);
void ciclicShiftRightArr(int arr[], int size);
void ciclicShiftLeftArr(int arr[], int size);
void ciclicShiftRightNumberArr(int arr[], int number, int size);
void ciclicShiftLeftNumberArr(int arr[], int number, int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	ciclicShiftRightNumberArr(arr, SHIFT, SIZE);
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

void ciclicShiftRightArr(int arr[], int size)
{
	int element = arr[size - 1];
	
	for (int i = size - 1; i > 0; i--)
		arr[i] = arr[i - 1];
		
	arr[0] = element;
}

void ciclicShiftLeftArr(int arr[], int size)
{
	int element = arr[0];
	
	for (int i = 0; i < size - 1; i++)
		arr[i] = arr[i + 1];
		
	arr[size - 1] = element;
}

void ciclicShiftRightNumberArr(int arr[], int number, int size)
{
	int arr1[number];
	
	for (int i = size - 1, y = number - 1; i > size - number - 1; i--, y--)
		arr1[y] = arr[i];
	
	for (int i = 0; i < number; i++)
	{
		for (int y = size - 1; y > 0; y--)
			arr[y] = arr[y - 1];
	}
	
	for (int i = 0; i < number; i++)
		arr[i] = arr1[i];
	
}

void ciclicShiftLeftNumberArr(int arr[], int number, int size)
{
	int arr1[number];
	
	for (int i = 0; i < number; i++)
		arr1[i] = arr[i];
	
	for (int i = 0; i < number; i++)
	{
		for (int i = 0; i < size - 1; i++)
			arr[i] = arr[i + 1];
	}
	
	for (int i = size - number, y = 0; i < size; i++, y++)
		arr[i] = arr1[y];
	
}
