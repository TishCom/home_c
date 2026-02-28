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

//Размер массива
#define SIZE 	10

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция выполняет сортировку массива (половина возрастающая, половина убывающая)
void sortHalvesArr(int arr[], int crushing, int size);
//Функция выполняет сортировку половины массива 
void sortCrushingArr(int arr[], int number, int isAscending, int size);
//Функция выполняет сортировку массива по возраствнию
void sortAscendingArr(int arr[], int size);
//Функция выполняет сортировку массива по убыванию
void sortDescendingArr(int arr[], int size);
//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	sortHalvesArr(arr, 2, SIZE);
	outputArr(arr, SIZE);
	
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

//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	
	return i;
}

//Функция выполняет сортировку массива по возраствнию
void sortAscendingArr(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (arr[i] > arr[y + 1])
				SwapArr(arr, i, y + 1);
		}
	}
}

//Функция выполняет сортировку массива по убыванию
void sortDescendingArr(int arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (arr[i] < arr[y + 1])
				SwapArr(arr, i, y + 1);
		}
	}
}

//Функция выполняет сортировку массива (половина возрастающая, половина убывающая)
void sortHalvesArr(int arr[], int crushing, int size)
{
	sortCrushingArr(arr, 0, 1, size / crushing);
	sortCrushingArr(arr, 1, 0, size / crushing);
}

//Функция выполняет сортировку половины массива 
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

//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
