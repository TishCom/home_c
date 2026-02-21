/*
 * D10_CheckSimplicity.c
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

//Обертака функции isPrimeNumber
#define isPrime(number)								isPrimeNumber(2, number)
//Возвращяет следующее число
#define NEXT_NUMBER(number)							((number) + 1)
//Делятся ли без остатка
#define IS_COMPLETELY_DIVIDED(number1, number2)		((number1) % (number2) == 0)
//Большн ли введенное число 1
#define IS_GERATER_ONE(number)						((number) > 1)

//Функция возвращает 1 если numberUser простое в противном случе возращает 0
uint32_t isPrimeNumber(uint32_t auxiliaryNumber, uint32_t numberUser);

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%d", &number);
	
	if (isPrime(number))
		printf("YES");
	else
		printf("NO");
	
	return 0;
}

uint32_t isPrimeNumber(uint32_t auxiliaryNumber, uint32_t numberUser) 
{
	if(auxiliaryNumber == numberUser)
		return true;
	else if (IS_COMPLETELY_DIVIDED(numberUser, auxiliaryNumber) || !IS_GERATER_ONE(numberUser))
		return false;
	
	return isPrimeNumber(NEXT_NUMBER(auxiliaryNumber), numberUser);
}
