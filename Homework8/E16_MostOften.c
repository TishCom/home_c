/*
 * E16_MostOften.c
 * 
 * Copyright 2026 Tisha <Tisha@DESKTOP-TSPB5RM>
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
#define SIZE 	10

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция возвращает колличетво совпадений в массиве arr элементов element
int numberCoincidenceElementArr(int arr[], int element, int size);
//Функция возвращает элемент массива с которым в массиве больше всего совпадений
int maxCoincidenceElementArr(int arr[], int size);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	
	printf("%d ", maxCoincidenceElementArr(arr, SIZE));
	
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

//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	
	return i;
}

//Функция возвращает элемент массива с которым в массиве больше всего совпадений
int maxCoincidenceElementArr(int arr[], int size)
{
	int out = 0, currentCoincidence = 0, maxCoincidence = 0;
	
	for (int i = 0; i < size; i++)
	{
		currentCoincidence = numberCoincidenceElementArr(arr, arr[i], size);
		
		if (currentCoincidence > maxCoincidence)
		{
			maxCoincidence = currentCoincidence;
			out = arr[i];
		}
	}
	
	return out;
}

//Функция возвращает колличетво совпадений в массиве arr элементов element
int numberCoincidenceElementArr(int arr[], int element, int size)
{
	int coincidence = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == element)
			coincidence++;
	}
	
	return coincidence;
}
