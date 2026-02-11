/*
 * C17_HappyNumber.c
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

uint32_t sumDigitNumber(uint32_t number);
uint32_t multDigitNumber(uint32_t number);
uint32_t isEqual(uint32_t number1, uint32_t number2);
uint32_t isHappyNumber(uint32_t number);
uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber);
uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber);
uint32_t shiftDigitNumberLeft(uint32_t number, uint32_t digit, uint32_t baseNumber);
uint32_t powerNumber(int32_t numberIN, int32_t power);

int main(int argc, char **argv)
{
	int32_t number = 0;
	
	scanf("%u", &number);
	
	if (isHappyNumber(number))
		printf("YES\n");
	else
		printf("NO\n");
	
	return 0;
}

uint32_t sumDigitNumber(uint32_t number)
{
	uint32_t sum = 0;
	
	while (number > 0)
	{
		sum += returnDigit(number, 0, 10);
		number = shiftDigitNumberRight(number, 1, 10);
	}
	
	return sum;
}

uint32_t multDigitNumber(uint32_t number)
{
	uint32_t mult = 1;
	
	while (number > 0)
	{
		mult *= returnDigit(number, 0, 10);
		number = shiftDigitNumberRight(number, 1, 10);
	}
	
	return mult;
}

uint32_t isEqual(uint32_t number1, uint32_t number2)
{
	if (number1 == number2)
		return 1;
	else
		return 0;
}

uint32_t isHappyNumber(uint32_t number)
{
	return isEqual(multDigitNumber(number), sumDigitNumber(number));
}

uint32_t returnDigit(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return (number / powerNumber(baseNumber, digit)) % baseNumber;
}

uint32_t shiftDigitNumberRight(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return number / powerNumber(baseNumber, digit);
}

uint32_t shiftDigitNumberLeft(uint32_t number, uint32_t digit, uint32_t baseNumber)
{
	return number * powerNumber(baseNumber, digit);
}

uint32_t powerNumber(int32_t numberIN, int32_t power)
{
	int32_t numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}
