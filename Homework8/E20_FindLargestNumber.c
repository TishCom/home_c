/*
 * E20_FindLargestNumber.c
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

//Псевдонимы стандартных систем счисления
enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

/* 
 * Функция возвращает число number сдвинутое на digit разрядов вправо.
 * При этом number имеет основание baseNumber.
 */
uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber);
/* 
 * Функция возвращает число находящееся в разряде digit числа number.
 * При этом number имеет основание baseNumber.
 */
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);
//Функция возвращает колличество разрядов в числе
uint32_t depthNumber(int32_t number);
//Функция заполняет массив arr разрядами числа number
void fillArrNumber(int arr[], int number, int size);
//Функция возвращяет число разряды которого хранятся в массиве arr
int convertArrNumber(int arr[], int size);
//Функция выполняет сортировку массива по возраствнию
void sortAscendingArr(int arr[], int size);
//Функция возвращает максимальное число которое может получится из разрядов number
int maxPosibleNumber(int number);
//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j);

int main(int argc, char **argv)
{
	int number = 0;
	
	scanf("%d", &number);
	
	printf("%d\n", maxPosibleNumber(number));
	
	return 0;
}

//Функция возвращает максимальное число которое может получится из разрядов number
int maxPosibleNumber(int number)
{
	int depth = depthNumber(number);
	int arr[depth];
	
	fillArrNumber(arr, number, depth);
	sortAscendingArr(arr, depth);
	
	return convertArrNumber(arr, depth);
}

//Функция возвращяет число разряды которого хранятся в массиве arr
int convertArrNumber(int arr[], int size)
{
	int number = 0;
	
	for (int i = 0; i < size; i++)
		number += arr[i] * powerNumber(DECIMAL, i);
	
	return number;
}

//Функция заполняет массив arr разрядами числа number
void fillArrNumber(int arr[], int number, int size)
{
	for (int i = 0; i < size; i++)
		arr[i] = returnDigit(number, i , DECIMAL);
}

//Функция выполняет сортировку массива по возраствнию
void sortAscendingArr(int arr[], int size)
{
	int sortingFinished = 1;
	
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (arr[i] > arr[y + 1])
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
 * Функция возвращает число number сдвинутое на digit разрядов вправо.
 * При этом number имеет основание baseNumber.
 */
uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return number / powerNumber(baseNumber, digit);
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

//Функция возвращает колличество разрядов в числе
uint32_t depthNumber(int32_t number)
{
	int32_t depth = 0;
	
	while (number > 0)
	{
		number = shiftDigitNumberRight(number, 1, DECIMAL);
		depth++;
	}
	
	return depth;
}

//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
