/*
 * C10_PrimeFactorsNumber.c
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

//Функция проверяет является ли число number простым
uint32_t isPrimeNumber(uint32_t number);
//Функция выводит в терминал все простые множители числа number
void printSimple(uint32_t number);

int main(int argc, char **argv)
{
	uint32_t number = 0;
	
	scanf("%u", &number);
	
	printSimple(number);
	
	return 0;
}

//Функция проверяет является ли число number простым
uint32_t isPrimeNumber(uint32_t number)
{
	int32_t flagPrime = 1;
	
	if (number <= 1)
		flagPrime = 0;
		
	for (int i = 2; i < number; i++)
	{
		if (number % i == 0)
			flagPrime = 0;
	}
	
	return flagPrime;
}

//Функция выводит в терминал все простые множители числа number
void printSimple(uint32_t number)
{
	for (uint32_t i = 2; i <= number; i++)
	{
		if (number % i == 0 && isPrimeNumber(i))
		{
			printf("%u ", i);
			number /= i;
			i--;
		}
	}
}
