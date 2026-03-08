/*
 * F20_EvenOdd.c
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
#include <inttypes.h>

//Размер массива
#define SIZE 10

//Псевдонимы стандартных систем счисления
enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

//Функция заменяет все четные или нечетные числа в массиве исходя из их соотношения
void replaceEvenOddNumberArr(int arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);
/* 
 * Функция возвращает число находящееся в разряде digit числа number.
 * При этом number имеет основание baseNumber.
 */
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber);
/* 
 * Функция возвращает число number сдвинутое на digit разрядов вправо.
 * При этом number имеет основание baseNumber.
 */
uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber);
//Функция заменяет нечетное число на произведение нечетных цифр в его десятичной записи
int multOddDigit(int number);
//Функция заменяет четное число на произведение четных цифр в его десятичной записи
int multEvenDigit(int number);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция заменяет все нечетноые числа в массиве на произведение нечетных цифр в его десятичной записи
void replaceOddNumberArr(int arr[], int size);
//Функция заменяет все четноые числа в массиве на произведение четных цифр в его десятичной записи
void replaceEvenNumberArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	
	replaceEvenOddNumberArr(arr, SIZE);
	
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

//Функция заменяет все четные или нечетные числа в массиве исходя из их соотношения
void replaceEvenOddNumberArr(int arr[], int size)
{
	int even = 0, odd = 0;;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] % 2)
			odd++;
		else
			even++;
	}
	
	if (even > odd)
		replaceOddNumberArr(arr, size);
	else
		replaceEvenNumberArr(arr, size);
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

//Функция заменяет нечетное число на произведение нечетных цифр в его десятичной записи
int multOddDigit(int number)
{
	int mult = 1, digit = 0;
	while (number > 0)
	{
		digit = returnDigit(number, 0, DECIMAL);
		
		if (digit % 2)
			mult *= digit;
			
		number = shiftDigitNumberRight(number, 1, DECIMAL);
	}
	
	return mult;
}

//Функция заменяет четное число на произведение четных цифр в его десятичной записи
int multEvenDigit(int number)
{
	int mult = 1, digit = 0;
	while (number > 0)
	{
		digit = returnDigit(number, 0, DECIMAL);
		
		if (digit % 2 == 0)
			mult *= digit;
			
		number = shiftDigitNumberRight(number, 1, DECIMAL);
	}
	
	return mult;
}

//Функция заменяет все нечетноые числа в массиве на произведение нечетных цифр в его десятичной записи
void replaceOddNumberArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] % 2)
			arr[i] = multOddDigit(arr[i]);
	}
}

//Функция заменяет все четноые числа в массиве на произведение четных цифр в его десятичной записи
void replaceEvenNumberArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr[i] % 2 == 0)
			arr[i] = multEvenDigit(arr[i]);
	}
}
