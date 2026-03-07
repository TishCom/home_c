/*
 * F19_GreaterAverage.c
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

#define SIZE 25

int averageTraceMatrix(int arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
int numberGreaterAverageTraceMatrix(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[25] = {0};
	
	inputArr(arr, SIZE);
	
	printf("%d\n", numberGreaterAverageTraceMatrix(arr, SIZE));
	
	return 0;
}

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	return i;
}

int averageTraceMatrix(int arr[], int size)
{
	int trace = 0;
	
	for (int i = 0; i < size / 5; i++)
		trace += arr[i * 6];
		
	return trace / 5;
}

int numberGreaterAverageTraceMatrix(int arr[], int size)
{
	int average = averageTraceMatrix(arr, size);
	int greaterNumber = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] > average && arr[i] > 0)
			greaterNumber++;
	}
		
	return greaterNumber;
}
