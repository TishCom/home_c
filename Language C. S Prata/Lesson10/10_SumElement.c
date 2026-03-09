/*
 * 10_SumElement.c
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

#define SIZE		5

void sumElement(int arr[], int arr1[], int arr2[], int size);
int outputArr(int arr[], int size);

int main(int argc, char **argv)
{
	int num1[SIZE] = {1, 2, 5, 7, 3};
	int num2[SIZE] = {14, 12, 58, 70, 13};
	int num3[SIZE] = {0};
	
	outputArr(num3, SIZE);
	sumElement(num1, num2, num3, SIZE);
	outputArr(num3, SIZE);
	
	return 0;
}

void sumElement(int arr[], int arr1[], int arr2[], int size)
{
	for (int i = 0; i < size; i++)
		arr2[i] = arr[i] + arr1[i];
}

int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d |", arr[i]);
		
	putchar('\n');
	
	return i;
}
