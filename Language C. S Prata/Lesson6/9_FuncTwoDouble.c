/*
 * 9_FuncTwoDouble.c
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

double funcDouble(double number1, double number2);

int main(int argc, char **argv)
{
	double number1 = 0, number2 = 0;
	
	while (scanf("%lf%lf", &number1, &number2) == 2)
		printf("%lf\n", funcDouble(number1, number2));
			
	return 0;
}

double funcDouble(double number1, double number2)
{
	return (number1 - number2) / (number1 * number2);
}
