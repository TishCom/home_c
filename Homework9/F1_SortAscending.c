/*
 * F1_SortAscending.c
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
#include <stdlib.h>
#include <time.h>

//Размер массива
#define SIZE 	10
//Ограничивает значения в массиве верхним пределом нижний предел 0
#define LIMIT 	200

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция выполняет сортировку массива по возраствнию
void sortAscendingArr(int arr[], int size);
//Функция меняет элементы местами
void swap(int *i, int *y);
//Функция возвращает случайное число от -limit/2 до limit/2
int rsndomNumber(int limit);
//Функция заполняющая массив случайными значениями в диапазоне от -limit/2 до limit/2
int inputRandArr(int arr[], int size, int limit);

int main(int argc, char **argv)
{
	srand(time(NULL));
	
	int arr[SIZE] = {0};
	
	inputRandArr(arr, SIZE, LIMIT);
	outputArr(arr, SIZE);
	printf("\n");
	sortAscendingArr(arr, SIZE);
	outputArr(arr, SIZE);
	
	return 0;
}

//Функция возвращает случайное число от -limit/2 до limit/2
int rsndomNumber(int limit)
{
	return (rand() % limit) - limit / 2;
}


//Функция заполняющая массив случайными значениями
int inputRandArr(int arr[], int size, int limit)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rsndomNumber(limit);
	
	return i;
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
	int sortingFinished;
	
	for (int i = 0; i < size - 1; i++)
	{
		sortingFinished = 1;
		
		for (int y = size - 1; y > i; y--)
		{
			if (arr[y] < arr[y - 1])
			{
				swap(&arr[y], &arr[y - 1]);
				sortingFinished = 0;
			}
		}
		
		if (sortingFinished)
			break;
	}
}

//Функция меняет элементы местами
void swap(int *i, int *y)
{
	int temp = *i;
	*i = *y;
	*y = temp;
}
