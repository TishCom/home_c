/*
 * TreeStars.c
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

//Количество линий
#define MAX_LINES 4

//Количество пробелов необходимых для симметрии
#define SPACE_HHOHH ((MAX_LINES) - 3)
#define SPACE_ZZZZZ ((MAX_LINES) - 3)

//Количество звезд в текущей линии
#define CHARACTER_IN_LINE(current_line) ((current_line) * 2 - 1)
//Количество пробелов в текущей линии
#define SPACE_IN_LINE(current_line) ((MAX_LINES) - (current_line))

//Символ для отображения
#define CHARACTER '*'

int main(int argc, char **argv)
{
	for (int current_line = 1; current_line <= MAX_LINES; current_line++)
	{
		for (int space = 0; space < SPACE_IN_LINE(current_line); space++)
			printf(" ");
		
		for (int character = 0; character < CHARACTER_IN_LINE(current_line); character++)
			printf("%c", CHARACTER);
		
		printf("\n");
	}
	
	for (int space = 0; space < SPACE_HHOHH; space++)
		printf(" ");
	printf("HHOHH\n");
	
	for (int space = 0; space < SPACE_ZZZZZ; space++)
		printf(" ");
	printf("ZZZZZ\n");
	
	return 0;
}

