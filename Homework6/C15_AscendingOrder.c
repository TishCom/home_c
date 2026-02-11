/*
 * C15_AscendingOrder.c
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
#include <stdint.h>

//Стандартные системы счисления
enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

//Функция проверяет больше ли сcheckNumber чем verificater
uint32_t isMore(uint32_t checkNumber, uint32_t verificater);
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
/* 
 * Функция проверяет действительно ли что цифры в каждом
 * разряде числа number расположенны по возрастанию.
 */
uint32_t isAscendingOrder(uint32_t number);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);

int main(int argc, char **argv)
{
	uint32_t number = 0;
	
	scanf("%d", &number);
	
	if (isAscendingOrder(number))
		printf("YES\n");
	else
		printf("NO\n");
	
	return 0;
}

//Функция проверяет больше ли сcheckNumber чем verificater
uint32_t isMore(uint32_t checkNumber, uint32_t verificater)
{
	if (checkNumber > verificater)
		return 1;
	else
		return 0;
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
 * Функция проверяет действительно ли что цифры в каждом
 * разряде числа number расположенны по возрастанию.
 */
uint32_t isAscendingOrder(uint32_t number)
{
	uint32_t oldDigit = returnDigit(number, 0, DECIMAL), curentDigit = 0;
	uint32_t flagAscending = 1;
	
	while (number > 0)
	{
		number = shiftDigitNumberRight(number, 1, DECIMAL);
		
		curentDigit = returnDigit(number, 0, DECIMAL);
		
		if (isMore(oldDigit, curentDigit))
		{
			flagAscending = 1;
		}
		else
		{
			flagAscending = 0;
			break;
		}
		
		oldDigit = curentDigit;
	}
	
	return flagAscending;
}

//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power)
{
	int32_t numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}
