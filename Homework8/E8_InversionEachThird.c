/*
 * E8_InversionEachThird.c
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
#define SIZE 12

//Функция заполняющая массив значениями введнными пользователем
int inputArr(int arr[], int size);
//Функция выводит значения элементов массива в терминал
int outputArr(int arr[], int size);
//Функция меняет элементы массива местами задом наперед
void inversionArr(int arr[], int size);
//Функция копирует элементы массива arr в arr1 в колличестве size
void copyArr(int arr[], int arr1[], int size);
//Функция выполняет инверсию массива arr по частям равным number
void inversionPartsArr(int arr[], int number, int size);
//Функция выполняет инверсию части number массива arr
void inversionCrushingArr(int arr[], int number, int size);
//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j);

int main(int argc, char **argv)
{
	int arr[SIZE] = {0};
	
	inputArr(arr, SIZE);
	inversionPartsArr(arr, 3, SIZE);
	outputArr(arr, SIZE);
	
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

//Функция выполняет инверсию массива arr по частям равным number
void inversionPartsArr(int arr[], int number, int size)
{
	for (int q = 0; q < number; q++)
		inversionCrushingArr(arr, q, size / number);
}

//Функция выполняет инверсию части number массива arr
void inversionCrushingArr(int arr[], int number, int size)
{
	int arr1[size];
	
	for (int i = 0, y = size * number; i < size; i++, y++)
		arr1[i] = arr[y];
		
	inversionArr(arr1, size);
		
	for (int i = 0; i < size; i++)
		arr[i + size * number] = arr1[i];
}

//Функция копирует элементы массива arr в arr1 в колличестве size
void copyArr(int arr[], int arr1[], int size)
{
	for (int i = 0; i < size; i++)
		arr1[i] = arr[i];
}

//Функция меняет элементы массива местами задом наперед
void inversionArr(int arr[], int size)
{
	for (int i = 0; i < size / 2; i++)
		SwapArr(arr, i, size - i - 1);
}

//Функция выполняет меняет элементы в массиве местами
void SwapArr(int arr[], int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
