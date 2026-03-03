/*
 * 6_Sorting.c
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

double max(double number1, double number2);
double min(double number1, double number2);
void sorting(double *x, double *y, double *z);

int main(int argc, char **argv)
{
	double x = 67.43, y = 105.87, z = 67.43;
	
	printf("%.2f %.2f %.2f\n", x, y, z);
	sorting(&x, &y, &z);
	printf("%.2f %.2f %.2f\n", x, y, z);
	
	return 0;
}

void sorting(double *x, double *y, double *z)
{
	double minNumber = min(*x, min(*y, *z));
	double maxNumber = max(*x, max(*y, *z));
	
	if (*x > minNumber && *x < maxNumber)
		*y = *x;
	else if (*z > minNumber && *z < maxNumber)
		*y = *z;
		
	*x = minNumber;
	*z = maxNumber;
} 

double max(double number1, double number2)
{
	return number1 > number2 ? number1 : number2;
}

double min(double number1, double number2)
{
	return number1 < number2 ? number1 : number2;
}
