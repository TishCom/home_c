/*
 * F7_PackArray01.c
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
#include <time.h>

#define SIZE 20

int compression(int a[], int b[], int sizeA);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция заполняющая массив случайными значениями
int inputRandArr(int arr[], int size, int limit);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция возвращает случайное число от -limit/2 до limit/2
int rsndomNumber(int limit);

int main(int argc, char **argv)
{
	srand(time(NULL));
	int a[SIZE] = {0}, b[SIZE] = {0};
	int sizeB = 0;
	inputRandArr(a, SIZE, 2);
	outputArr(a, SIZE);
	printf("\n");
	sizeB = compression(a, b, SIZE);
	printf("%d\n", sizeB);
	outputArr(b, sizeB);
	return 0;
}

//Функция возвращает случайное число от -limit/2 до limit/2
int rsndomNumber(int limit)
{
	return (rand() % limit);
}

//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	
	return i;
}

//Функция заполняющая массив случайными значениями
int inputRandArr(int arr[], int size, int limit)
{
	int i;
	for (i = 0; i < size; i++)
		arr[i] = rsndomNumber(limit);
	
	return i;
}

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	return i;
}

int compression(int a[], int b[], int sizeA)
{
	int number = 0, sizeB = 0;
	for (int i = 0; i < sizeA; i++)
	{
		if((number && a[i - 1] != a[i]) || i == 0)
		{
			b[sizeB++] = number;
			number = 0;
		}
		number++;
	}
	b[sizeB++] = number;
	
	return sizeB;
}
