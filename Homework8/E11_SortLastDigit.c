/*
 * E11_SortLastDigit.c
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
//Функция выполняет сортировку массива по последней цифре элемента
void sortLastDigitArr(int arr[], int size);
/* 
 * Функция возвращает число находящееся в разряде digit числа number.
 * При этом number имеет основание baseNumber.
 */
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);
//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	sortLastDigitArr(arr, SIZE);
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

//Функция выполняет сортировку массива по последней цифре элемента
void sortLastDigitArr(int arr[], int size)
{
	int sortingFinished = 1;
	
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (returnDigit(arr[i], 0, DECIMAL) > returnDigit(arr[y + 1], 0, DECIMAL))
			{
				SwapArr(arr, i, y + 1);
				sortingFinished = 0;
			}
		}
		
		if (sortingFinished == 1)
			break;
	}
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

//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
