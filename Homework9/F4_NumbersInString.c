/*
 * F4_NumbersInString.c
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

//Размер массива
#define SIZE 	1000

//Функция возвращает максимальное или минимальное число которое может получится из разрядов number
void posibleNumber(char arr[], int size);
//Функция возвращает максимальное или минимальное число которое может получится из разрядов number
void print_digit(char arr[]);
int numberDigitInString(char arr[], int size);

int main(int argc, char **argv)
{
	char stringNumber[SIZE] = {0}, ch = 0;;
	
	for (int i = 0; (ch = getchar()) != '\n'; i++)
		 stringNumber[i] = ch;
	
	print_digit(stringNumber);
	
	return 0;
}

//Функция возвращает максимальное или минимальное число которое может получится из разрядов number
void posibleNumber(char arr[], int size)
{
	int digit[10] = {0};
	
	for (int i = 0; i < size; i++)
		digit[arr[i] - '0']++;
		
	for (int i = 0; i < 10; i++)
	{
		if (digit[i])
			printf("%d %d\n", i, digit[i]);
	}
}

//Функция возвращает максимальное или минимальное число которое может получится из разрядов number
void print_digit(char arr[])
{
	int size = strlen(arr);
	char number[numberDigitInString(arr, size)];
	
	for (int i = 0, y = 0; i < size; i++)
	{
		if (arr[i] >= '0' && arr[i] <= '9')
			number[y++] = arr[i];
	}
	
	posibleNumber(number, strlen(number));
}

int numberDigitInString(char arr[], int size)
{
	int number = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] >= '0' && arr[i] <= '9')
			number++;
	}
	
	return number;
}
