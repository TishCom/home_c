/*
 * 12_Counter.c
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

void countPrintInput(void);
int isWord(char previous, char current);

int main(int argc, char **argv)
{
	countPrintInput();
	return 0;
}

void countPrintInput(void)
{
	char current = 0, previous = 0;
	int countWord = 0, countLower = 0, countUpper = 0, countPunct = 0;
	int countNumber = 0;
	
	while ((current = getchar()) != EOF)
	{
		if (islower(current))
			countLower++;
		else if (isupper(current))
			countUpper++;
		else if (ispunct(current))
			countPunct++;
		else if (isdigit(current))
			countNumber++;
		if (isWord(previous, current))
			countWord++;
			
		previous = current;
	}
	
	printf("countLower = %d\n", countLower);
	printf("countUpper = %d\n", countUpper);
	printf("countPunct = %d\n", countPunct);
	printf("countNumber = %d\n", countNumber);
	printf("countWord = %d\n", countWord);
}

int isWord(char previous, char current)
{
	return (isalnum(previous) && !isalnum(current));
}
