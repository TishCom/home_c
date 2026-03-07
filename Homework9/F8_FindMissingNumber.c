/*
 * F8_FindMissingNumber.c
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

#define SIZE 1000

//Функция возвращающая элемент массива с максимальным значением
int maxArr(int arr[], int size);
//Функция возвращающая элемент массива с минимальным значением
int minArr(int arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
int missingNumber(int arr[], int size);
//Функция возвращает колличетво совпадений в массиве arr элементов element
int numberCoincidenceElementArr(int arr[], int element, int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	int sizeArr = inputArr(arr, SIZE);
	
	printf("%d\n", missingNumber(arr, sizeArr));
	
	return 0;
}

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size && arr[i - 1] != 0; i++)
		scanf("%d", &arr[i]);
	
	return i - 1;
}

//Функция возвращающая элемент массива с минимальным значением
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

int missingNumber(int arr[], int size)
{
	for (int j = minArr(arr, size); j <= maxArr(arr, size); j++)
	{
		if (!numberCoincidenceElementArr(arr, j, size))
			return j;
	}
	
	return -1;
}

//Функция возвращает колличетво совпадений в массиве arr элементов element
int numberCoincidenceElementArr(int arr[], int element, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == element)
			return 1;
	}
	
	return 0;
}
