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
#include <inttypes.h>

//Размер массива
#define SIZE 	10

//Возможные действия с частью массива
enum ActionArray
{
	DISCENDING       = 1,
	ASCENDING        = 2,
	INVERSION        = 3,
	SORT_LAST_DIGIT  = 4
};

//Псевдонимы стандартных систем счисления
enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция выполняет сортировку массива (половина возрастающая, половина убывающая)
void sortPartsArr(int arr[], int crushing, int size);
//Функция выполняет сортировку половины массива 
void sortCrushingArr(int arr[], int number, int isAscending, int size);
//Функция выполняет сортировку массива по возраствнию
void sortAscendingArr(int arr[], int size);
//Функция выполняет сортировку массива по убыванию
void sortDescendingArr(int arr[], int size);
//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j);
//Функция меняет элементы массива местами задом наперед
void inversionArr(int arr[], int size);
//Функция выполняет сортировку массива по последней цифре элемента
void sortLastDigitArr(int arr[], int size);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);
/* 
 * Функция возвращает число находящееся в разряде digit числа number.
 * При этом number имеет основание baseNumber.
 */
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	sortPartsArr(arr, 2, SIZE);
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
	int sortingFinished;
	
	for (int i = 0; i < size - 1; i++)
	{
		sortingFinished = 1;
		
		for (int y = size - 1; y > i; y--)
		{
			if (arr[y] < arr[y - 1])
			{
				SwapArr(arr, y, y - 1);
				sortingFinished = 0;
			}
		}
		
		if (sortingFinished)
			break;
	}
}

//Функция выполняет сортировку массива по убыванию
void sortDescendingArr(int arr[], int size)
{
	int sortingFinished;
	
	for (int i = 0; i < size - 1; i++)
	{
		sortingFinished = 1;
		
		for (int y = size - 1; y > i; y--)
		{
			if (arr[y] > arr[y - 1])
			{
				SwapArr(arr, y, y - 1);
				sortingFinished = 0;
			}
		}
		
		if (sortingFinished)
			break;
	}
}

//Функция выполняет сортировку массива по последней цифре элемента
void sortLastDigitArr(int arr[], int size)
{
	int sortingFinished;
	
	for (int i = 0; i < size; i++)
	{
		sortingFinished = 1;
		
		for (int y = size - 1; y > i; y--)
		{
			if (returnDigit(arr[y], 0, DECIMAL) < returnDigit(arr[y - 1], 0, DECIMAL))
			{
				SwapArr(arr, y, y - 1);
				sortingFinished = 0;
			}
		}
		
		if (sortingFinished)
			break;
	}
}

//Функция меняет элементы массива местами задом наперед
void inversionArr(int arr[], int size)
{
	for (int i = 0; i < size / 2; i++)
		SwapArr(arr, i, size - i - 1);
}

//Функция выполняет сортировку массива (половина возрастающая, половина убывающая)
void sortPartsArr(int arr[], int crushing, int size)
{
	int part = 0;
	sortCrushingArr(arr, part++, ASCENDING, size / crushing);
	sortCrushingArr(arr, part, DISCENDING, size / crushing);
}

//Функция выполняет необходимые действия с чстью массива 
void sortCrushingArr(int arr[], int number, int action, int size)
{
	int arr1[size];
	
	for (int i = 0, y = size * number; i < size; i++, y++)
		arr1[i] = arr[y];
		
	switch (action)
	{
		case ASCENDING:
			sortAscendingArr(arr1, size);
			break;
		case DISCENDING:
			sortDescendingArr(arr1, size);
			break;
		case INVERSION:
			inversionArr(arr1, size);;
			break;
		case SORT_LAST_DIGIT:
			sortLastDigitArr(arr1, size);
			break;
	}
	
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

/* 
 * Функция возвращает число находящееся в разряде digit числа number.
 * При этом number имеет основание baseNumber.
 */
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return (number / powerNumber(baseNumber, digit)) % baseNumber;
}

//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power)
{
	int32_t numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}
