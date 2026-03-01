/*
 * 4_Average.c
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
#include <ctype.h>

int main(int argc, char **argv)
{
	int currentChar = 0, previousChar = 0, countLater = 0, countWord = 0;
	
	while ((currentChar = getchar()) != EOF)
	{
		if (isalnum(currentChar))
			countLater++;
		else if (isalnum(previousChar) && (isspace(currentChar) || ispunct(currentChar)))
			countWord++;
			
		previousChar = currentChar;
	}
	
	printf("Average later in word equal %.2f", (float)countLater / (float)countWord);
		
	return 0;
}

