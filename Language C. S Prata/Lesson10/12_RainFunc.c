/*
 * 12_RainFunc.c
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

#define MONTHS		12
#define YEARS		5
#define START_YEAR	2010

void func1(int column, int string, double arr[string][column]);
void func2(int column, int string, double arr[string][column]);

int main(int argc, char **argv)
{
	double rain[YEARS][MONTHS] = 
	{
		{4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6},
		{8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3},
		{9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4},
		{7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2},
		{7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 0.0, 1.3, 2.6, 5.2}
	};
	
	func1(MONTHS, YEARS, rain);
	func2(MONTHS, YEARS, rain);
	
	return 0;
}

void func1(int column, int string, double arr[string][column])
{
	int year, month;
	float subtot, total;
	
	printf(" Year            Rain\n");
	
	for (year = 0, total = 0; year < string; year++)
	{
		for (month = 0, subtot = 0; month < column; month++)
			subtot += arr[year][month];
			
		printf("%5d %15.1f\n", START_YEAR + year, subtot);
		
		total += subtot;
	}
	
	printf("Average rain = %.1f\n", total / string);
}

void func2(int column, int string, double arr[string][column])
{
	int year;
	float subtot;
	
	printf("Average rain in month:\n");
	
	for (int month = 0; month < column; month++)
	{
		for (year = 0, subtot = 0; year < string; year++)
			subtot += arr[year][month];
		
		printf("%4.1f", subtot / string);
	}
	
	printf("\n");
}
