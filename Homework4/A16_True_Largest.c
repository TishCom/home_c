/*
 * A16_True_Largest.c
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

//Возвращяет максимальное из двух введенных чисел
#define MAX(operand1, operand2)		((operand1) >= (operand2) ? (operand1) : (operand2))
//Возвращяет минимальное из двух введенных чисел
#define MIN(operand1, operand2)		((operand1) <= (operand2) ? (operand1) : (operand2))

int main(int argc, char **argv)
{
	int32_t number1, number2, number3, max, min;
	
	scanf("%d%d%d", &number1, &number2, &number3);
	
	max = MAX(number1, number2);
	max = MAX(max, number3);
	
	min = MIN(number1, number2);
	min = MIN(min, number3);
	
	if(number1 == min && number3 == max && min != max)
		printf("YES");
	else
		printf("NO");

	return 0;
}

