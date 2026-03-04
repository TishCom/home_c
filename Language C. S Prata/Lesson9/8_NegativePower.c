/*
 * 8_NegativePower.c
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

double negtivePowerNumber(double numberIN, int power);
double positivePowerNumber(double numberIN, int power);
double powerNumber(double numberIN, int power);
double powerNumber1(double numberIN, int power);

int main(int argc, char **argv)
{
	printf("%.3f\n", powerNumber(5.687, 3));
	printf("%.3f\n", powerNumber(5.687, -3));
	printf("%.3f\n", powerNumber(5.687, 0));
	printf("%.3f\n", powerNumber(0, 0));
	
	printf("%.3f\n", powerNumber1(5.687, 3));
	printf("%.3f\n", powerNumber1(5.687, -3));
	printf("%.3f\n", powerNumber1(5.687, 0));
	printf("%.3f\n", powerNumber1(0, 0));
	
	return 0;
}

double powerNumber(double numberIN, int power)
{
	double numberOUT = 1;
	
	if (power > 0)
		numberOUT = positivePowerNumber(numberIN, power);
	else if (power < 0)
		numberOUT = negtivePowerNumber(numberIN, power);
	
	return numberOUT;
}

double powerNumber1(double numberIN, int power)
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
		
	for (int i = 0; i < power; i++)
	{
		if (sign)
			numberOUT /= numberIN;
		else
			numberOUT *= numberIN;
	}
		
	
	return numberOUT;
}

double positivePowerNumber(double numberIN, int power)
{
	double numberOUT = 1;
	
	for (int i = 0; i < power; i++)
		numberOUT *= numberIN;
	
	return numberOUT;
}

double negtivePowerNumber(double numberIN, int power)
{
	double numberOUT = 1;
	
	for (int i = 0; i < -power; i++)
		numberOUT /= numberIN;
	
	return numberOUT;
}
