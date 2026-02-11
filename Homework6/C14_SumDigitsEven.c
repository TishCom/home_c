/*
 * C14_SumDigitsEven.c
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
#include <stdint.h>

//Стандартные системы счисления
enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

//Функция проверяет является ли число number четным
uint32_t isEven(uint32_t number);
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
/* 
 * Функция возвращает число number сдвинутое на digit разрядов влево.
 * При этом number имеет основание baseNumber.
 */
uint32_t shiftDigitNumberLeft(uint32_t number, uint32_t digit, uint32_t baseNumber);
//Функция проверяет является ли сумма цифр в каждом разряде числа number четным
uint32_t sumDigitsIsEven(uint32_t number);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);
/* 
 * Функция возвращает сумму цифр в каждом разряде числа number
 * При этом number имеет основание baseNumber.
 */
uint32_t sumDigits(uint32_t number, uint32_t baseNumber);

int main(int argc, char **argv)
{
	uint32_t number = 0;
	
	scanf("%d", &number);
	
	if (sumDigitsIsEven(number))
		printf("YES\n");
	else
		printf("NO\n");
	
	return 0;
}

//Функция проверяет является ли число number четным
uint32_t isEven(uint32_t number)
{
	return !(number % 2);
}

/* 
 * Функция возвращает число находящееся в разряде digit числа number.
 * При этом number имеет основание baseNumber.
 */
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return (number / powerNumber(baseNumber, digit)) % baseNumber;
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
 * Функция возвращает число number сдвинутое на digit разрядов влево.
 * При этом number имеет основание baseNumber.
 */
uint32_t shiftDigitNumberLeft(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return number * powerNumber(baseNumber, digit);
}

/* 
 * Функция возвращает сумму цифр в каждом разряде числа number
 * При этом number имеет основание baseNumber.
 */
uint32_t sumDigits(uint32_t number, uint32_t baseNumber)
{
	uint32_t sum = 0;
	
	while (number > 0)
	{
		sum += returnDigit(number, 0, baseNumber);
		number = shiftDigitNumberRight(number, 1, baseNumber);
	}
	
	return sum;
}

//Функция проверяет является ли сумма цифр в каждом разряде числа number четным
uint32_t sumDigitsIsEven(uint32_t number)
{
	return isEven(sumDigits(number, DECIMAL));
}

//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power)
{
	int32_t numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}
