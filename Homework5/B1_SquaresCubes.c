/*
 * B1_SquaresCubes.c
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
#define UPPER_LIMIT(number)		((number) <= 100)
//Входит ли введенное число в нижний предел
#define LOWER_LIMIT(number)		((number) >= 1)
//Входит ли введенное число в необходимые пределы
#define ENTER_LIMIT(number)		(UPPER_LIMIT(number) && LOWER_LIMIT(number))

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%d", &number);
	
	if(!(ENTER_LIMIT(number)))
		return 1;
		
	for (int i = 1; i <= number; i++)
		printf("%d %d %d\n", i, i * i, i * i * i);
	
	return 0;
}

