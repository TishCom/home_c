/*
 * 01_Grant.c
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
#include <ctype.h>

#define ANSWER "grant"
#define SIZE 40

char* sgets(char *str, int size);
void skipString(void);
char* toLower(char *str);

int main(int argc, char **argv)
{
	char try[SIZE];
	
	puts("Qvestion?");
	
	sgets(try, SIZE);
	
	while (strcmp(toLower(try), ANSWER) != 0)
	{
		puts("Try again!");
		sgets(try, SIZE);
	}
	
	puts("OK!!!");
	
	return 0;
}

char* toLower(char *str)
{
	char *retVal = str;
	
	while (*str)
	{
		*str = tolower(*str);
		str++;
	}
	
	return retVal;
}

char* sgets(char *str, int size)
{
	char *retVal;
	int i = 0;
	
	retVal = fgets(str, size, stdin);
	
	if (retVal)
	{
		while (str[i] != '\n' && str[i] != '\0')
			i++;
			
		if (str[i] == '\n')
			str[i] = '\0';
		else
			skipString();
	}
	
	return retVal;
}

void skipString(void)
{
	while (getchar() != '\n')
		continue;
}
