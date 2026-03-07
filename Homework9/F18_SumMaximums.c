/*
 * F18_SumMaximums.c
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

#define SIZE 			100
#define LENGTH_STRING 	10

int traceMatrix(int arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
int sumMaximum(int arr[], int size);
//Функция возвращающая элемент массива с максимальным значением
int maxArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};//{1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
	
	inputArr(arr, SIZE);
	
	printf("%d\n", sumMaximum(arr, SIZE));
	
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

int traceMatrix(int arr[], int size)
{
	int trace = 0;
	
	for (int i = 0; i < size / 5; i++)
		trace += arr[i * 6];
		
	return trace;
}

int sumMaximum(int arr[], int size)
{
	int sum = 0;
	
	for (int i = 0; i < size / LENGTH_STRING; i++)
		sum += maxArr(arr + i * LENGTH_STRING, LENGTH_STRING);
		
	return sum;
}

//Функция возвращающая элемент массива с максимальным значением
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
