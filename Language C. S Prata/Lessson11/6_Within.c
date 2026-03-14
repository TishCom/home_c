/*
 * 6_Within.c
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

int is_within(char arr[], char ch);
void output(int size, const char arr[]);

int main(int argc, char **argv)
{
	char arr[] = "ABCDEFG";
	
	output(7, arr);
	
	for (char i = 'A'; i <= 'H'; i++)
		printf("%d - %c\n", is_within(arr, i), i);
	
	return 0;
}

int is_within(char arr[], char ch)
{
	while (*arr != '\0')
	{
		if (*arr++ == ch)
			return 1;
	}
		
	return 0;
}

void output(int size, const char arr[])
{
	for (int i = 0; i < size; i++)
		putchar(arr[i]);
		
	putchar('\n');
}
