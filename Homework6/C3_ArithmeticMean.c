/*
 * C3_ArithmeticMean.c
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

//Функция возвращяет среднее арифметическое между numberA и numberB
uint32_t middle(int32_t numberA, int32_t numberB);

int main(int argc, char **argv)
{
	int32_t number1 = 0, number2 = 0, middleNumber = 0;
	
	scanf("%d%d", &number1, &number2);
	
	middleNumber = middle(number1, number2);
	
	printf("%d\n", middleNumber);
	
	return 0;
}

//Функция возвращяет среднее арифметическое между numberA и numberB
uint32_t middle(int32_t numberA, int32_t numberB)
{
	return (numberA + numberB) / 2;
}
