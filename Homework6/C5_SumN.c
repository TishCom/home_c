/*
 * C5_SumN.c
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

//Функция возвращяет сумму чисел от 1 до введенного числа
uint32_t sumN(int32_t n);

int main(int argc, char **argv)
{
	int32_t number = 0, sumNumber;
	
	scanf("%d", &number);
	
	sumNumber = sumN(number);
	
	printf("%d\n", sumNumber);
	
	return 0;
}

//Функция возвращяет сумму чисел от 1 до введенного числа
uint32_t sumN(int32_t number)
{
	int32_t result = 0;
	
	for (int i = 1; i <= number; i++)
		result += i;
		
	return result;
}
