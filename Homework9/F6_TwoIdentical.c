/*
 * F6_TwoIdentical.c
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

//Размер массива
#define SIZE 	10
//Максимальное значение элемента массива
#define LIM		20

//Функция сообщает существует ли в данном массиве два одинаковых элемента
int is_two_same(int size, int arr[]);
//Функция заполняющая массив случайными значениями
int inputRandArr(int arr[], int size, int limit);
//Функция возвращает случайное число от -limit/2 до limit/2
int rsndomNumber(int limit);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);


int main(int argc, char **argv)
{
	srand(time(NULL));
	int arr[SIZE] = {0};
	
	inputRandArr(arr, SIZE, LIM);
	outputArr(arr, SIZE);
	printf("\n");
	
	if(is_two_same(SIZE, arr))
		printf("YES\n");
	else
		printf("NO\n");
	
	return 0;
}

//Функция возвращает случайное число от -limit/2 до limit/2
int rsndomNumber(int limit)
{
	return (rand() % limit) - limit / 2;
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

//Функция сообщает существует ли в данном массиве два одинаковых элемента
int is_two_same(int size, int arr[])
{
	int temp = 0;
	
	for (int i = 0; i < size; i++)
	{
		temp = arr[i];
		
		for (int a = i + 1; a < size; a++)
		{
			if (temp == arr[a]) 
				return 1;
		}
	}
	
	return 0;
}
