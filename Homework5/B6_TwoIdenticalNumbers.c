/*
 * B6_TwoIdenticalNumbers.c
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

int main(int argc, char **argv)
{
	int32_t number = 0, oldDigits = 0, currentDigits = 0;
	
	scanf("%d", &number);
	
	if (number < 0)
		return 1;
	
	oldDigits = number % 10;
	
	while(number >= 0)
	{
		number /= 10;
		
		if (number == 0)
		{
			printf("NO\n");
			break;
		}
		
		currentDigits = number % 10;
		
		if (oldDigits == currentDigits)
		{
			printf("YES\n");
			break;
		}
		
		oldDigits = currentDigits;
	}
	
	return 0;
}
