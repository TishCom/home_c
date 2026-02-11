/*
 * C4_FunctionAccordingFormula.c
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
 */


#include <stdio.h>
#include <stdint.h>

//Функция возвращяет f(x)
uint32_t functionAccordingFormula(int32_t x);
//Функция возвращяет наибольшее из введенных чисел
uint32_t maximum(int32_t numberA, int32_t numberB);

int main(int argc, char **argv)
{
	int32_t number = 0, max = 0;
	
	scanf("%d", &number);
	
	while (number != 0)
	{
		max = maximum(max, functionAccordingFormula(number));
		
		scanf("%d", &number);
	}
	
	printf("%d\n", max);
	
	return 0;
}

//Функция возвращяет f(x)
uint32_t functionAccordingFormula(int32_t x)
{
	if (-2 <= x && x < 2)
		x *= x;
	else if (x >= 2)
		x = x * x + 4 * x + 5;
	else
		x = 4;
		
	return x;
}

//Функция возвращяет наибольшее из введенных чисел
uint32_t maximum(int32_t number1, int32_t number2)
{
	return number1 > number2 ? number1 : number2;
}
