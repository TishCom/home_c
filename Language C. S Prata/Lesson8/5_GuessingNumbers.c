/*
 * 5_GuessingNumbers.c
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

void waitingEndInput(void);

int main(int argc, char **argv)
{
	int currentGuess = 50, previousGuess = 50, ch = 0, min = 0, max = 100;
	
	printf("Choose number 1 - 100.\n");
	printf("Enter 'y' if I'm right, 'b' if it's greater, and 's' if it's less.\n");
	printf("Is your number %d?\n", currentGuess);
	
	while ((ch = getchar()) != 'y')
	{
		if (ch == 'b')
		{
			min = currentGuess;
			currentGuess = previousGuess + (max - min) /  2;
		}
		else if (ch == 's')
		{
			max = currentGuess;
			currentGuess = previousGuess - (max - min) /  2;
		}
		else
		{
			printf("Enter correct character('y', 'b', 's').\n");
			waitingEndInput();
			continue;
		}
		
		printf("Is your number %d?\n", currentGuess);
		
		waitingEndInput();
		
		previousGuess = currentGuess;
	}
	
	printf("YES!!!\n");
	
	return 0;
}

void waitingEndInput(void)
{
	while (getchar() != '\n')
		continue;
}
