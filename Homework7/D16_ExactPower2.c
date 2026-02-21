/*
 * D16_ExactPower2.c
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

//Обертака функции exactPower2
#define isPower2(number)							(exactPower2(number) == 1) 
//Больше ли это число нуля
#define IS_GREATER_ZERO(number)						((number) > 0)
//Основание системы счисления введенного числа
#define BASE_NUMBER									2
//Возвращяет цифру находящуюся в разряде digit числа number
#define RETURN_DIGIT_NUMBER(number, digit)			(((number) / (digit)) % BASE_NUMBER)
//Возвращяет десятичное число number сдвинутое вправо на digit разрядов
#define SHIFT_DIGIT_NUMBER_RIGHT(number, digit)		((number) / ((digit) * BASE_NUMBER))

//Разряды введенного числа
enum Place
{
	UNITS    = 1,
	TENS     = 10,
	HUNDREDS = 100
};

//Функция возвращает колличество 1 в number в бинарном виде
uint32_t exactPower2(uint32_t number);

int main(int argc, char **argv)
{
	uint32_t number = 0;
	
	scanf("%d", &number);
	
	if (isPower2(number))
		printf("YES");
	else
		printf("NO");;
	
	return 0;
}

uint32_t exactPower2(uint32_t number)
{
	uint32_t iterator = 0;
	
	if (IS_GREATER_ZERO(number))
	{
		iterator += exactPower2(SHIFT_DIGIT_NUMBER_RIGHT(number, UNITS));
		
		if (RETURN_DIGIT_NUMBER(number, UNITS))
			iterator++;
	}
		
	return iterator;
}
