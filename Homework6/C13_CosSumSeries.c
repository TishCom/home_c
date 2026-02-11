/*
 * C13_CosSumSeries.c
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
 * cos(x) = 1 - x2/2! + x4/4! - x6/6! + ... (x в радианах)

float cosinus(float x)
 */


#include <stdio.h>
#include <stdint.h>
#include <math.h>

//Функция возвращает число numberIN в степени power
float powerNumber(float numberIN, int32_t power);
//Функция возвращает факторила числа number
uint64_t factorial(uint32_t number);
//Функция переводит градусы в радианы
float convertingDegreesRadians(float degrees);
//Функция возвращает косинус числа введенного в радианах
float cosinus(float radians);

int main(int argc, char **argv)
{
	float x = 0;
	
	scanf("%f", &x);
	
	printf("%.3f\n", cosinus(convertingDegreesRadians(x)));
	
	return 0;
}

//Функция возвращает число numberIN в степени power
float powerNumber(float numberIN, int32_t power)
{
	float numberOUT = 1.0;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}

//Функция возвращает факторила числа number
uint64_t factorial(uint32_t number)
{
	uint64_t result = 1;
	
	for (int i = 1; i <= number; i++)
		result *= i;
		
	return result;
}

//Функция переводит градусы в радианы
float convertingDegreesRadians(float degrees)
{
	return (M_PI * degrees) / 180;
}

//Функция возвращает косинус числа введенного в радианах
float cosinus(float radians)
{
	float result = 1;
	int32_t sign = -1;
	
	for (uint32_t i = 2; i < 10; i += 2)
	{
		result += sign * (powerNumber(radians, i) / factorial(i));
		sign = -sign;
	}
	
	return result;
}

