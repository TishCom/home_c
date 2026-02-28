/*
 * E17_OnlyOnce.c
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
int coincidenceElementArr(int arr[], int element, int size);
void selectionCoincidenceArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	
	selectionCoincidenceArr(arr, SIZE);
	
	return 0;
}

int inputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	return i;
}

void selectionCoincidenceArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (coincidenceElementArr(arr, arr[i], size) == 1)
			printf("%d ", arr[i]);
	}
}

int coincidenceElementArr(int arr[], int element, int size)
{
	int coincidence = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == element)
			coincidence++;
	}
	
	return coincidence;
}
