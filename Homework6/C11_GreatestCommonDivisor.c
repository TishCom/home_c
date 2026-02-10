/*
 * C11_GreatestCommonDivisor.c
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

uint32_t greatestCommonDivisor(uint32_t number1, uint32_t number2);

int main(int argc, char **argv)
{
	uint32_t number1 = 0, number2 = 0;
	
	scanf("%u%u", &number1, &number2);
	
	printf("%u\n", greatestCommonDivisor(number1, number2));
	
	return 0;
}

uint32_t greatestCommonDivisor(uint32_t number1, uint32_t number2)
{
	while (number1 != number2)
	{
		if (number1 > number2)
			number1 -= number2;
		else
			number2 -= number1;
	}
	
	return number1;
}
