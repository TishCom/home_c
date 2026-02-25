/*
 * 13_PowersTwo.c
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

int power2(int number);

int main(int argc, char **argv)
{
	int numbers[8] = {0};
	int u = 0;
	
	for (int i = 1, y = 0; y < 8; i *= 2, y++)
		numbers[y] = i;
		
	do
	{
		printf("%d\n", numbers[u]);
		u++;
	} while (u < 8);
	
	return 0;
}

int power2(int number)
{
	int power = 1;
	
	for (int i = 0; i < number; i++)
		power *= 2;
		
	return power;
}
