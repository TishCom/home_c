/*
 * 8_7.c
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
#define OVERTIME_HOUR 	15.0
#define LIM1 			300.0 
#define LIM2 			450.0
#define TAX1 			0.15
#define TAX2 			0.2 
#define TAX3 			0.25
#define TAX_MONEY1 		LIM1 * TAX1
#define TAX_MONEY2 		TAX_MONEY1 + (LIM2 - LIM1) * TAX2

#define SALARY_HOUR1 	8.75 
#define SALARY_HOUR2 	9.33 
#define SALARY_HOUR3 	10.0 
#define SALARY_HOUR4 	11.2 

int main(int argc, char **argv)
{
	int hour = 0, salary = 0;
	float sum = 0, tax = 0, clean = 0, salaryHour = 0;
	
	printf("Enter number 1 - 5: \n");
	printf("1) %.2f$			2) %.2f$\n", SALARY_HOUR1, SALARY_HOUR2);
	printf("3) %.2f$			4) %.2f$\n", SALARY_HOUR3, SALARY_HOUR4);
	printf("5) Exit\n");
	
	scanf("%d", &salary);
	
	switch (salary)
	{
		case 1:
			salaryHour = SALARY_HOUR1;
			break;
		case 2:
			salaryHour = SALARY_HOUR2;
			break;
		case 3:
			salaryHour = SALARY_HOUR3;
			break;
		case 4:
			salaryHour = SALARY_HOUR4;
			break;
		case 5:
			return 0;
		default:
			printf("Enter correct number\n");
	}
	
	
	scanf("%d", &hour);
	
	if (hour > LIMIT_HOUR)
		sum = LIMIT_HOUR * salaryHour + (hour - LIMIT_HOUR) * OVERTIME_HOUR;
	else
		sum = hour * salaryHour;
		
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
