/*
 * B9_AllNumbersEven.c
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
	char charArray[20] = {0};
	
	int32_t i = 0, flagEven = 0;
	
	for (;charArray[i - 1] != '\n'; i++)
		scanf("%c", &charArray[i]);
		
	for (int a = 0, b = i - 2; b >= 0; b--, a++)
	{
		switch (charArray[a])
		{
			case '0':
			case '2':
			case '4':
			case '6':
			case '8':
				flagEven = 1;
				break;
			default:
				flagEven = 0;
		}
		
		if (flagEven == 0)
			break;
	}
	
	if (flagEven == 1)
		printf("YES\n");
	else if (flagEven == 0)
		printf("NO\n");

	return 0;
}

