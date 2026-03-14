/*
 * 10_DeletSpace.c
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
#include <string.h>

#define SIZE 40

void deleteSpace(char *arr);
void ciclicShiftLeftArr(char arr[], int size);
void input(int size, char arr[]);
void skipString(char ch);

int main(int argc, char **argv)
{
	char arr[SIZE] = "H e l l o\tW o r l\nd ! ! !";
	printf("%s\n", arr);
	deleteSpace(arr);
	printf("%s\n", arr);
	
	input(SIZE, arr);
	while (strlen(arr))
	{
		printf("%s\n", arr);
		deleteSpace(arr);
		printf("%s\n", arr);
		input(SIZE, arr);
	}
	
	return 0;
}

void input(int size, char arr[])
{
	for (int i = 0; i < size; i++)
		arr[i] = '\0';
	
	char ch = getchar();
	for (int i = 0; i < size - 1 && ch != '\n'; i++)
	{
		arr[i] = ch;
		ch = getchar();
	}
	arr[size - 1] = '\0';
	
	skipString(ch);
}

void deleteSpace(char *arr)
{
	while (*arr)
	{
		if (isspace(*arr))
			ciclicShiftLeftArr(arr, strlen(arr));
		if(!isspace(*arr))	
			arr++;
	}
}

void ciclicShiftLeftArr(char arr[], int size)
{
	for (int i = 0; i < size - 1; i++)
		arr[i] = arr[i + 1];
		
	arr[size - 1] = '\0';
}

void skipString(char ch)
{
	if (ch == '\n')
		return;
		
	while (getchar() != '\n')
		continue;
}
