/*
 * 9_InversionString.c
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

#define SIZE 40

void inversionArr(char arr[], int size);
void swap(char *i, char *y);
void input(int size, char arr[]);
char getFirst(void);
void skipString(char ch);

int main(int argc, char **argv)
{
	char arr[SIZE] = "Hello World";
	printf("%s\n", arr);
	inversionArr(arr, strlen(arr));
	printf("%s\n", arr);
	
	for (int i = 0; i < SIZE; i++)
		arr[i] = '\0';
	
	for (int i = 0; i < 5; i++)
	{
		input(6, arr);
		inversionArr(arr, strlen(arr));
		printf("%s\n", arr);
	}
	
	return 0;
}

void inversionArr(char arr[], int size)
{
	for (int i = 0; i < size / 2; i++)
		swap(&arr[i], &arr[size - i - 1]);
}

void swap(char *i, char *y)
{
	int temp = *i;
	*i = *y;
	*y = temp;
}

void input(int size, char arr[])
{
	char ch = getFirst();
	
	for (int i = 0; i < size && !isspace(ch); i++)
	{
		arr[i] = ch;
		ch = getchar();
	}
	
	skipString(ch);
}

char getFirst(void)
{
	int ch = getchar();
	
	while (isspace(ch))
		ch = getchar();
	
	return ch;
}

void skipString(char ch)
{
	if (ch == '\n')
		return;
		
	while (getchar() != '\n')
		continue;
}
