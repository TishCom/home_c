/*
 * 16_Deposits.c
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

#define SIMPLE_PERCENT 		10
#define DIFFICULT_PERCENT 	1.05

int main(int argc, char **argv)
{
	float depDaf = 100, defDei = 100;
	int year = 0;
	
	do
	{
		depDaf += SIMPLE_PERCENT;
		defDei *= DIFFICULT_PERCENT;
		year++;
	} while (defDei < depDaf);
	
	printf("Deposit Daf = %.2f$, Deposit Dei = %.2f$, Year = %d",
			depDaf, defDei, year);
	
	return 0;
}

