/*
 * F11_SumMinimal.c
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
#define SIZE 30

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция возвращающая элемент массива с минимальным значением
int minArr(int arr[], int size);
//Функция возвращающая элемент массива с максимальным значением
int maxArr(int arr[], int size);
//Функция печатает индексы двух наименьших элементов массива
void printMin2Arr(int arr[], int size);
/*
 * Функция возвращающая номмер элемента массива равного element
 * (если такого нет вернет -1)
 */
int posArr(int arr[], int element, int size);
/*
 * Функция возвращающая индекс элемента массива равного element
 * (если такого нет вернет -1)
 */
int indexArr(int arr[], int element, int size);
//Фуекция возвращает минимальное из двух значений
int min(int a, int b);
//Фуекция возвращает максимальное из двух значений
int max(int a, int b);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	
	printMin2Arr(arr, SIZE);
	
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

//Функция возвращающая элемент массива с минимальным значением
int minArr(int arr[], int size)
{
	int min =  arr[0];
	
	for (int i = 1; i < size; i++)
	{
		if (min > arr[i])
			min = arr[i];
	}
	
	return min;
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

//Функция печатает индексы двух наименьших элементов массива
void printMin2Arr(int arr[], int size)
{
	int min1 = maxArr(arr, size), min2 = minArr(arr, size);
	int index = indexArr(arr, min2, size), index1 = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (min1 > arr[i] && i != index)
		{
			min1 = arr[i];
			index1 = i;
		}
	}
	
	printf("%d %d\n", min(index1, index), max(index1, index));
}

//Фуекция возвращает максимальное из двух значений
int max(int a, int b)
{
	return a > b ? a : b;
}

//Фуекция возвращает минимальное из двух значений
int min(int a, int b)
{
	return a < b ? a : b;
}

/*
 * Функция возвращающая номмер элемента массива равного element
 * (если такого нет вернет -1)
 */
int posArr(int arr[], int element, int size)
{
	int pos;
	
	for (pos = 0; pos < size; pos++)
	{
		if (element == arr[pos])
		{
			pos++;
			break;
		}
	}
	
	if (pos == size && element != arr[pos - 1])
		return -1;
		
	return pos;
}

/*
 * Функция возвращающая индекс элемента массива равного element
 * (если такого нет вернет -1)
 */
int indexArr(int arr[], int element, int size)
{
	int index = posArr(arr, element, size);
	return  index == -1 ? -1 : index - 1;
}
