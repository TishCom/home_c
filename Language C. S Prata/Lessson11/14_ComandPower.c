/*
 * 14_ComandPower.c
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
#include <stdlib.h>

double powerNumber(double numberIN, int power);
double positivePowerNumber(double numberIN, int power);
double negtivePowerNumber(double numberIN, int power);

int main(int argc, char **argv)
{
	printf("%.2f\n", powerNumber(atof(argv[1]), atoi(argv[2])));
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
