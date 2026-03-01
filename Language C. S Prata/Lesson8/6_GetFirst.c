/*
 * 6_GetFirst.c
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

void waitingEndInput(void);
char get_first(void);
int get_int(void);

int main(int argc, char **argv)
{
	printf("%d\n", get_int());
	
	return 0;
}

char get_first(void)
{
	int ch = getchar();
	
	while (isspace(ch))
		ch = getchar();
	
	waitingEndInput();
	
	return ch;
}

int get_int(void)
{
	int number;
	
	while (scanf("%d", &number) != 1)
		waitingEndInput();
	
	return number;
}

void waitingEndInput(void)
{
	while (getchar() != '\n')
		continue;
}
