/*
 * B15_NumberEvenNumbers.c
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

//Проверка числа на четность
#define IS_EVEN(number)								(!((number) % 2))

int main(int argc, char **argv)
{
	int32_t number = 0, countEven = 0;
	
	do
	{
		if (IS_EVEN(number))
			countEven++;
			
		scanf("%d", &number);
	}while (number != 0);
	
	printf("%d\n", countEven - 1); 

	return 0;
}
