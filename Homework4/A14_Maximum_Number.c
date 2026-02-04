/*
 * A14_Maximum_Number.c
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

//Входит ли введенное число в верхний предел
#define UPPER_LIMIT(number)		(((number) / 1000) == 0)
//Входит ли введенное число в нижний предел
#define LOWER_LIMIT(number)		((number) > 0)
//Входит ли введенное число в необходимые пределы
#define ENTER_LIMIT(number)		(UPPER_LIMIT(number) && LOWER_LIMIT(number))

//Возвращяет максимальное из двух введенных чисел
#define MAX(operand1, operand2)					((operand1) >= (operand2) ? (operand1) : (operand2))

//Возвращяет цифру находящуюся в разряде digit числа number
#define RETURN_DIGIT_NUMBER(number, digit)		(((number) / (1 * (digit))) % 10)

int main(int argc, char **argv)
{
	int32_t base = 0, number1 = 0, number2 = 0, number3 = 0, max;
	
	scanf("%d", &base);
	
	if (!(ENTER_LIMIT(base)))
			return 1;
			
	number1 = RETURN_DIGIT_NUMBER(base, 1);
	number2 = RETURN_DIGIT_NUMBER(base, 10);
	number3 = RETURN_DIGIT_NUMBER(base, 100);
	
	max = MAX(number1, number2);
	max = MAX(max, number3);
	
	printf("%d", max);
			
	return 0;
}
