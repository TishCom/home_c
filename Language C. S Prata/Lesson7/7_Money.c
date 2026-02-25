/*
 * 7_Money.c
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

#define LIMIT_HOUR 		40
#define SALARY_HOUR 	10.0 
#define OVERTIME_HOUR 	15.0
#define LIM1 			300.0 
#define LIM2 			450.0
#define TAX1 			0.15
#define TAX2 			0.2 
#define TAX3 			0.25
#define TAX_MONEY1 		LIM1 * TAX1
#define TAX_MONEY2 		TAX_MONEY1 + (LIM2 - LIM1) * TAX2

int main(int argc, char **argv)
{
	int hour = 0;
	float sum = 0, tax = 0, clean = 0;
	
	scanf("%d", &hour);
	
	if (hour > LIMIT_HOUR)
		sum = LIMIT_HOUR * SALARY_HOUR + (hour - LIMIT_HOUR) * OVERTIME_HOUR;
	else
		sum = hour * SALARY_HOUR;
		
	if (sum <= LIM1)
		tax = sum * TAX1;
	else if (sum <= LIM2)
		tax = TAX_MONEY1 + (sum - LIM1) * TAX2;
	else
		tax = TAX_MONEY2 + (sum - LIM2) * TAX3;
		
	clean = sum - tax;
	
	printf("sum = %.2f, tax = %.2f, clean = %.2f\n", sum, tax, clean);
	
	return 0;
}

