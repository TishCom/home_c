/*
 * 9_Recursive8.c
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

double recurcivePowerNumber(double numberIN, int power);
double recursivePositivePowerNumber(double numberIN, int power);

int main(int argc, char **argv)
{
	printf("%.3f\n", recurcivePowerNumber(5.687, 3));
	printf("%.3f\n", recurcivePowerNumber(5.687, -3));
	printf("%.3f\n", recurcivePowerNumber(5.687, 0));
	printf("%.3f\n", recurcivePowerNumber(0, 0));
	
	return 0;
}

double recurcivePowerNumber(double numberIN, int power)
{
	double numberOUT = 1;
	int sign = 0;
	
	if (power < 0)
	{
		sign = 1;
		power = -power;
	}
	
	if (power == 0 && numberIN == 0)
		printf("TEXT.\n");
		
	if (power == 0)
		return 1;
		
	power--;
	
	if (sign)
	{
		numberOUT /= numberIN;
		return numberOUT * recurcivePowerNumber(numberIN, -power);
	}
	else
	{
		numberOUT *= numberIN;
		return numberOUT * recurcivePowerNumber(numberIN, power);
	}
}

double recursivePositivePowerNumber(double numberIN, int power)
{
	double numberOUT = 1;
		
	if (power == 0)
		return 1;
		
	numberOUT *= numberIN;
		
	power--;
	
	return numberOUT * recursivePositivePowerNumber(numberIN, power);
}
