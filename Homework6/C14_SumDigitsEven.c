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

//Разряды введенного числа
enum Place
{
	UNITS    = 1,
	TENS     = 10,
	HUNDREDS = 100
};

uint32_t isEven(uint32_t number);
uint32_t returnDigit(uint32_t number, uint32_t digit);
uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit);
uint32_t shiftDigitNumberLeft(uint32_t number, uint32_t digit);
uint32_t sumDigitsIsEven(uint32_t number);

int main(int argc, char **argv)
{
	uint32_t number = 0;
	
	scanf("%d", &number);
	
	sumDigitsIsEven(number) ? printf("YES\n") : printf("NO\n");
	
	return 0;
}

uint32_t isEven(uint32_t number)
{
	return !(number % 2);
}

uint32_t returnDigit(uint32_t number, uint32_t digit)
{
	return (number / digit) % 10;
}

uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit)
{
	return number / (digit * 10);
}

uint32_t shiftDigitNumberLeft(uint32_t number, uint32_t digit)
{
	return number * (digit * 10);
}

uint32_t sumDigitsIsEven(uint32_t number)
{
	uint32_t sum = 0;
	
	while (number > 0)
	{
		sum += returnDigit(number, UNITS);
		number = shiftDigitNumberRight(number, UNITS);
	}
	
	return isEven(sum);
}
