/*
 * 0_Menu.c
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

#define EXIT 4

void menu (void);
int getInt(void);
void skipString(void);
int enterLimit(int min, int max);

int main(int argc, char **argv)
{
	int min = getInt(), max = getInt(), number = 0;
	
	menu ();
	
	number = enterLimit(min, max);
	
	if (number == EXIT)
		return 0;
	else
		printf("You Wane!!");
	
	return 0;
}

void menu (void)
{
	printf("Enter operation a - q: \n");
	printf("a) copy		b) muve\n");
	printf("c) delete	d) exit\n");
}

int getInt(void)
{
	int number;
	
	while (scanf("%d", &number) != 1)
		skipString();
	
	return number;
}

void skipString(void)
{
	while (getchar() != '\n')
		continue;
}

int enterLimit(int min, int max)
{
	int number = 0;
	
	if (scanf("%d", &number) != 1)
		return EXIT;
	
	while (number < min || number > max)
	{
		menu();
		
		if (scanf("%d", &number) != 1)
			return EXIT;
	}
	
	return number;
}
