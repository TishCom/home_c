/*
 * 8_StringIn.c
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
#include <string.h>

#define SIZE 40

char* string_in(char *str, char *str1);

int main(int argc, char **argv)
{
	printf("%s\n", string_in("ABCDEFRHDG", "R"));
	return 0;
}

char* string_in(char *str, char *str1)
{
	int size = strlen(str1);
	int size1 = strlen(str);
	
	for (int i = 0; i < size1 - size; i++)
	{
		if (strncmp(str + i, str1, size) == 0)
			return str + i;
	}
	
	return NULL;
}
