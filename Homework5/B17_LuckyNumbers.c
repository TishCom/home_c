/*
 * B17_LuckyNumbers.c
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

//Максималное возможное входное значение
#define MAX_NUMBER									100000
//Минимальное возможное входное значение
#define MIN_NUMBER									0
//Входит ли введенное число в верхний предел
#define UPPER_LIMIT(number)							((number) <= MAX_NUMBER)
//Входит ли введенное число в нижний предел
#define LOWER_LIMIT(number)							((number) >= MIN_NUMBER)
//Входит ли введенное число в необходимые пределы
#define ENTER_LIMIT(number)							(UPPER_LIMIT(number) && LOWER_LIMIT(number))

//Возвращяет цифру находящуюся в разряде digit числа number
#define RETURN_DIGIT_NUMBER(number, digit)			(((number) / (digit)) % 10)
//Возвращяет десятичное число number сдвинутое вправо на digit разрядов
#define SHIFT_DIGIT_NUMBER_RIGHT(number, digit)		((number) / ((digit) * 10))

//Разряды введенного числа
enum Place
{
	UNITS    = 1,
	TENS     = 10,
	HUNDREDS = 100
};

int main(int argc, char **argv)
{
	int32_t number = 0, temporary = 0, sum = 0, mult = 1;
	
	scanf("%d", &number);
	
	if (!(ENTER_LIMIT(number)))
		return 1;
	
	for (int i = 10; i <= number; i++)
	{
		sum = 0;
		temporary = i;
		
		while(temporary > 0)
		{
			sum += RETURN_DIGIT_NUMBER(temporary, UNITS);
			temporary = SHIFT_DIGIT_NUMBER_RIGHT(temporary, UNITS);
		}
		
		mult = 1;
		temporary = i;
		
		while(temporary > 0)
		{
			mult *= RETURN_DIGIT_NUMBER(temporary, UNITS);
			temporary = SHIFT_DIGIT_NUMBER_RIGHT(temporary, UNITS);
		}
		
		if (sum == mult)
			printf("%d ", i);
	}
	
	return 0;
}

