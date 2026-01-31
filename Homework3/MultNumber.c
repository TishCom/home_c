/*
 * MultNumber.c
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

//Если нужна отладка обьявить константу DEBUG
//#define DEBUG	1

//Входит ли введенное число в верхний предел
#define UPPER_LIMIT(number)		(((number / 1000) == 0)? 0 : 1)
//Входит ли введенное число в нижний предел
#define LOWER_LIMIT(number)		((number > 100)? 0 : 1)
//Входит ли введенное число в необходимые пределы
#define NOT_ENTER_LIMIT(number)	(UPPER_LIMIT(number) || LOWER_LIMIT(number))

int main(int argc, char **argv)
{
	unsigned int number = 0, mult = 1;
	
#ifdef DEBUG
	char exit = '\n';
	
	for(;exit == '\n';)
	{
#endif

		scanf("%ud", &number);
		
		if (NOT_ENTER_LIMIT(number))
			return 0;
		
		mult *= number % 10;
		mult *= (number / 10) % 10;
		mult *= (number / 100) % 10;
		
		printf("%ud\n",  mult);
		
#ifdef DEBUG
		mult = 1;
		
		scanf("%c", &exit);
	}
#endif

	return 0;
}
