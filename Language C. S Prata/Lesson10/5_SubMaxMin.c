/*
 * 5_SubMaxMin.c
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

double find_max_array(int size, double arr[]);
double find_min_array(int size, double arr[]);
double subtractinMaxMin(int size, double arr[]);

int main(int argc, char **argv)
{
	double rain[MONTHS] = {4.3, 4.3, 4.3, 3.0, 2.0, 31.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6};
	
	printf("%.2f\n", subtractinMaxMin(MONTHS, rain));
	
	return 0;
}

double find_max_array(int size, double arr[])
{
	int max =  arr[0];
	
	for (int i = 1; i < size; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	
	return max;
}

double find_min_array(int size, double arr[])
{
	int max =  arr[0];
	
	for (int i = 1; i < size; i++)
	{
		if (max > arr[i])
			max = arr[i];
	}
	
	return max;
}

double subtractinMaxMin(int size, double arr[])
{
	return find_max_array(size, arr) - find_min_array(size, arr);
}
