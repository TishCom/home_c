/*
 * 15_Atoi.c
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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int myAtoi(char str[]);
int positivePowerNumber(int numberIN, int power);

int main(int argc, char **argv)
{
	printf("%d\n", atoi("123"));
	printf("%d\n", myAtoi("123K"));
	return 0;
}

int myAtoi(char str[])
{
	int number = 0;
	int size = strlen(str);
	
	for (int i = 0; i < size; i++)
	{
		if (isdigit(str[i]))
			number += (str[i] - '0') * positivePowerNumber(10, size - i - 1);
		else
			return 0;
	}
	
	return number;
}

int positivePowerNumber(int numberIN, int power)
{
	double numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}
