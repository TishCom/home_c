/*
 * C12_SinSumSeries.c
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
 */


#include <stdio.h>
#include <stdint.h>
#include <math.h>

float powerNumber(float numberIN, int32_t power);
uint64_t factorial(uint32_t number);
float convertingDegreesRadians(float degrees);
float mySin(float radians);

int main(int argc, char **argv)
{
	float x = 0;
	
	scanf("%f", &x);
	
	printf("%.3f\n", mySin(convertingDegreesRadians(x)));
	
	return 0;
}

float powerNumber(float numberIN, int32_t power)
{
	double numberOUT = 1.0;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}

uint64_t factorial(uint32_t number)
{
	uint64_t result = 1.0;
	
	if (number < 1 || number > 20)
	{
		printf("1 - 20\n");
		return 1;
	}
	
	for (int i = 1; i <= number; i++)
		result *= i;
		
	return result;
}

float convertingDegreesRadians(float degrees)
{
	return (M_PI * degrees) / 180;
}

float mySin(float radians)
{
	float result = radians;
	int32_t sign = -1;
	
	for (uint32_t i = 1; i < 10; i++)
	{
		result += sign * (powerNumber(radians, i * 2 + 1) / (float)factorial(i * 2 + 1));
		sign = -sign;
	}
	
	return result;
}
