/*
 * E20_FindLargestNumber.c
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
#include <inttypes.h>

enum NumberSystem
{
	BINARY     	= 2,
	OCTAL      	= 8,
	DECIMAL  	= 10,
	HEXADECIMAL = 16
};

uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber);
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber);
uint32_t powerNumber(int32_t numberIN, int32_t power);
void outputDigitNumber(int number);
uint32_t depthNumber(int32_t number);
int outputArr(int arr[], int size);
void fillArrNumber(int arr[], int number, int size);
void sortDescendingArr(int arr[], int size);

int main(int argc, char **argv)
{
	int number = 0, depth = 0;
	
	scanf("%d", &number);
	
	depth = depthNumber(number);
	
	int arr[depth];
	
	fillArrNumber(arr, number, depth);
	sortDescendingArr(arr, depth);
		
	outputArr(arr, depth);
	
	return 0;
}

void fillArrNumber(int arr[], int number, int size)
{
	for (int i = 0; i < size; i++)
		arr[i] = returnDigit(number, i , DECIMAL);
}

int outputArr(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d", arr[i]);
	
	return i;
}

void sortDescendingArr(int arr[], int size)
{
	int temp = 0;
	
	for (int i = 0; i < size - 1; i++)
	{
		for (int y = i; y < size - 1; y++)
		{
			if (arr[i] < arr[y + 1])
			{
				temp = arr[i];
				arr[i] = arr[y + 1];
				arr[y + 1] = temp;
			}
		}
	}
}

void outputDigitNumber(int number)
{
	for (int i = depthNumber(number); i > 0; i--)
		printf("%d ", returnDigit(number, i - 1, DECIMAL));
}

uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return number / powerNumber(baseNumber, digit);
}

uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return (number / powerNumber(baseNumber, digit)) % baseNumber;
}

uint32_t powerNumber(int32_t numberIN, int32_t power)
{
	int32_t numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}

uint32_t depthNumber(int32_t number)
{
	int32_t depth = 0;
	
	while (number > 0)
	{
		number = shiftDigitNumberRight(number, 1, DECIMAL);
		depth++;
	}
	
	return depth;
}
