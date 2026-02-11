/*
 * C7_NumberNAnotherSystem.c
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

//Стандартные системы счисления
enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

/*
 * Функция переводит число numberIN из десятичной системы счисления
 * в число с системой счисления по основанию base
*/
uint32_t transformSystem(uint32_t numberIN, uint32_t base);
//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power);

int main(int argc, char **argv)
{
	uint32_t number = 0, base = 0;
	
	scanf("%u%u", &number, &base);
	
	number = transformSystem(number, base);
	
	printf("%u\n", number);
	
	return 0;
}

/*
 * Функция переводит число numberIN из десятичной системы счисления
 * в число с системой счисления по основанию base
*/
uint32_t transformSystem(uint32_t numberIN, uint32_t base)
{
	uint32_t numberOUT = 0, digit  = 0;
	
	while (numberIN > 0)
	{
		numberOUT += (numberIN % base) * powerNumber(DECIMAL, digit);
		numberIN /= base;
		digit ++;
	}
	
	return numberOUT;
}

//Функция возвращает число numberIN в степени power
uint32_t powerNumber(int32_t numberIN, int32_t power)
{
	int32_t numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}
