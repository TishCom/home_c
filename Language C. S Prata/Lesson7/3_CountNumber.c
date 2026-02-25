/*
 * 3_CountNumber.c
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
	int number = 0;
	int noEven = 0, even = 0, sumEven = 0, sumNoEven = 0;
	
	scanf("%d", &number);
	
	while (number != 0)
	{
		if (number % 2 == 0)
		{
			even++;
			sumEven += number;
		}
		else
		{
			noEven++;
			sumNoEven += number;
		}
		
		scanf("%d", &number);
	}
	
	printf("even = %d, avEven = %.2f, noEven = %d, avNoEven = %.2f",
			even, (float)sumEven / (float)even, noEven,
			(float)sumNoEven / (float)noEven);
	
	return 0;
}

