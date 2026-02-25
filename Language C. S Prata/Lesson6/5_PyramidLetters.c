/*
 * 5_PyramidLetters.c
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

int main(int argc, char **argv)
{
	char y = 0;
	
	scanf("%c", &y);
	
	for (int i = 0, x = 'A'; i <= y - 'A'; i++, x = 'A')
	{
		for (int a = y - 'A'; a > i; a--)
			printf(" ");
			
		for (int a = 0; a <= i; a++, x++)
			printf("%c", x);
			
		x -= 2;
			
		for (int a = 0; a < i; a++, x--)
			printf("%c", x);
			
		printf("\n");
	}
	
	return 0;
}

