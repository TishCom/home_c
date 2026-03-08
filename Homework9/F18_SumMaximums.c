/*
 * F18_SumMaximums.c
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

//Колличество элементов в строке матрици
#define NUMBER_STRING	10
//Размер массива
#define SIZE			NUMBER_STRING * NUMBER_STRING


//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция возвращает суммы максимальных элементов из каждой строки.
int sumMaximum(int arr[], int numberString);
//Функция возвращающая элемент массива с максимальным значением
int maxArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	
	printf("%d\n", sumMaximum(arr, NUMBER_STRING));
	
	return 0;
}

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	return i;
}

//Функция возвращает суммы максимальных элементов из каждой строки.
int sumMaximum(int arr[], int numberString)
{
	int sum = 0;
	
	for (int i = 0; i < numberString; i++)
		sum += maxArr(arr + i * numberString, numberString);
		
	return sum;
}

//Функция возвращающая элемент массива с максимальным значением
int maxArr(int arr[], int size)
{
	int max =  arr[0];
	
	for (int i = 1; i < size; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	
	return max;
}
