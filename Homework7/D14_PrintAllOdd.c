/*
 * D14_PrintAllOdd.c
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

//Это число обозночает выход
#define IS_EXIT(number)		((number) == 0)
//Это четное число
#define IS_EVEN(number)		(((number) % 2) == 0)

//Функция печатает все не четные числа до числа 0
void printOdd(void);

int main(int argc, char **argv)
{
	printOdd();
	
	return 0;
}

void printOdd(void)
{
	uint32_t number = 0;
	
	scanf("%d", &number);
	
	if (!IS_EXIT(number))
	{
		if (!IS_EVEN(number))
			printf("%d ", number);
			
		printOdd();
	}
}
