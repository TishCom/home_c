/*
 * D9_SumDigits.c
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

//Больше ли это число нуля
#define IS_GREATER_ZERO(number)						((number) > 0)
//Основание системы счисления введенного числа
#define BASE_NUMBER									10
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

//Функция возвращает число равно сумме всех разрядов числа number
int32_t sumDigits(int32_t number);

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%d", &number);
	
	printf("%d", sumDigits(number));
	
	return 0;
}

int32_t sumDigits(int32_t number)
{
	if (IS_GREATER_ZERO(number))
		return RETURN_DIGIT_NUMBER(number, UNITS) + sumDigits(SHIFT_DIGIT_NUMBER_RIGHT(number, UNITS));
		
	return 0;
}
