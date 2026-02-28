/*
 * E19_NumbersInAscendingOrder.c
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

int main(int argc, char **argv)
{
	int number = 0;
	
	scanf("%d", &number);
	
	outputDigitNumber(number);
	
	return 0;
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
