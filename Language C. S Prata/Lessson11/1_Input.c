/*
 * 1_Input.c
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

#define SIZE 40

void input(int size, char arr[]);
void output(int size, char arr[]);

int main(int argc, char **argv)
{
	char arr[SIZE] = {0};
	
	input(SIZE, arr);
	output(SIZE, arr);
	
	return 0;
}

void input(int size, char arr[])
{
	for (int i = 0; i < size; i++)
		arr[i] = getchar();
}

void output(int size, char arr[])
{
	for (int i = 0; i < size; i++)
		putchar(arr[i]);
}
