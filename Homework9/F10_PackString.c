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

//Размер массива
#define SIZE 1000

//Функция сжатия
int compression(int a[], int b[], int sizeA);
//Функция выводит значения элементов массива в терминал
int outputArr(char arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0}, arr1[SIZE] = {0};
	int size = inputArr(arr, SIZE);
	int size1 = compression(arr, arr1, size);
	
	
	for (int i = 0; i < size1; i += 2)
		printf("%c%d", arr1[i], arr1[i + 1]);
		
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
int inputArr(int arr[], int size)
{
	int i, ch = 0;
	for (i = 0; i < size && (ch = getchar()) != '.'; i++)
		arr[i] = ch;
	
	return i;
}

//Функция сжатия
int compression(int a[], int b[], int sizeA)
{
	int number = 0, sizeB = 0;
	for (int i = 0; i < sizeA; i++)
	{
		if(number && a[i - 1] != a[i])
		{
			b[sizeB++] = a[i - 1];
			b[sizeB++] = number;
			number = 0;
		}
		number++;
	}
	
	b[sizeB++] = a[sizeA - 1];
	b[sizeB++] = number;
	
	return sizeB;
}

