/*
 * F10_PackString.c
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

#define SIZE 1000

int compression(char a[], char c[], int b[], int sizeA);
//Функция выводит значения элементов массива в терминал
int outputArr(char arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(char arr[], int size);

int main(int argc, char **argv)
{
	char arr[SIZE] = {0}, arr1[SIZE] = {0};
	int arr2[SIZE] = {0};
	int size = inputArr(arr, SIZE);
	int size1 = compression(arr, arr1, arr2, size);
	
	
	for (int i = 0; i < size1; i++)
		printf("%c%d", arr1[i], arr2[i]);
		
	return 0;
}

//Функция выводит значения элементов массива в терминал
int outputArr(char arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%c ", arr[i]);
	
	return i;
}

//Функция заполняющая массив значениями введнными пользователем
int inputArr(char arr[], int size)
{
	int i;
	for (i = 0; i < size && arr[i - 1] != '.'; i++)
		scanf("%c", &arr[i]);
	
	return i - 1;
}

int compression(char a[], char c[], int b[], int sizeA)
{
	int number = 0, sizeB = 0;
	for (int i = 0; i < sizeA; i++)
	{
		if(number && a[i - 1] != a[i])
		{
			b[sizeB] = number;
			c[sizeB++] = a[i - 1];
			number = 0;
		}
		number++;
	}
	
	b[sizeB] = number;
	c[sizeB++] = a[sizeA - 1];
	
	return sizeB;
}
