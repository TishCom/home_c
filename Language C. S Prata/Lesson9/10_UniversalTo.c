/*
 * 10_UniversalTo.c
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

void toBinary(unsigned long number);
void toBaseN(int number, int base);

int main(int argc, char **argv)
{
	toBinary(255);
	putchar('\n');
	toBaseN(255, 10);
	
	return 0;
}

void toBinary(unsigned long number)
{
	int r = number % 2;
	
	if (number >= 2)
		toBinary(number / 2);
		
	putchar(r == 0 ? '0' : '1');
}

void toBaseN(int number, int base)
{
	int r = number % base;
	
	if (number >= base)
		toBaseN(number / base, base);
		
	putchar(r + '0');
}
