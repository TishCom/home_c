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
#define NUMBER_LINES 4

//Количество пробелов необходимых для симметрии
#define SPACE_HHOHH ((NUMBER_LINES) - 3)
#define SPACE_ZZZZZ ((NUMBER_LINES) - 3)

//Количество звезд в текущей линии
#define STARS_LINE(current_line) (current_line * 2 - 1)

//Символ для отображения
#define SYMBOL '*'

int main(int argc, char **argv)
{
	for (int current_line = 1; current_line <= NUMBER_LINES; current_line++)
	{
		for (int space = 1; space <= NUMBER_LINES - current_line; space++)
			printf(" ");
		
		for (int star = 1; star <= STARS_LINE(current_line); star++)
			printf("%c", SYMBOL);
		
		printf("\n");
	}
	
	for (int space = 1; space <= SPACE_HHOHH; space++)
		printf(" ");
	printf("HHOHH\n");
	
	for (int space = 1; space <= SPACE_ZZZZZ; space++)
		printf(" ");
	printf("ZZZZZ\n");
	
	return 0;
}

