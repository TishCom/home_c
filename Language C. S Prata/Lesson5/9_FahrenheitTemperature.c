/*
 * 9_FahrenheitTemperature.c
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

#define DEGREES	248

void temperatures(double tempFar);

int main(int argc, char **argv)
{
	double tempFar = 0;
	
	printf("Enter the Fahrenheit temperature value: ");
	scanf("%lf", &tempFar);
	
	temperatures(tempFar);
	
	return 0;
}

void temperatures(double tempFar)
{
	double tempCels = 5.0 / 9.0 * (tempFar - 32);
	printf("%.2lf %cF = %.2lf %cC = ",tempFar, DEGREES, tempCels, DEGREES);
	printf("%.2lf K.\n", tempCels + 273.16);
}
